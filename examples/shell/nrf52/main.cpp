/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include <platform/CHIPDeviceConfig.h>
#include <platform/CHIPDeviceLayer.h>

#include <lib/shell/streamer.h>
#include <lib/shell/Engine.h>

#include <lib/core/CHIPCore.h>
#include <lib/support/Base64.h>
#include <lib/support/CHIPArgParser.hpp>
#include <lib/support/CodeUtils.h>
#include <lib/support/RandUtils.h>
#include <support/logging/CHIPLogging.h>

#include <ChipShellCollection.h>

#include "nrf_log.h"

#ifdef SOFTDEVICE_PRESENT
#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#include "nrf_sdh_soc.h"
#endif //#ifdef SOFTDEVICE_PRESENT

#if CHIP_ENABLE_OPENTHREAD
extern "C" {
#include "multiprotocol_802154_config.h"
#include "nrf_802154.h"
#include "nrf_cc310_platform_abort.h"
#include "nrf_cc310_platform_mutex.h"
#include <openthread/platform/platform-softdevice.h>
}
#endif // CHIP_ENABLE_OPENTHREAD

#if CHIP_ENABLE_OPENTHREAD
#include <mbedtls/platform.h>
#include <openthread/cli.h>
#include <openthread/dataset.h>
#include <openthread/error.h>
#include <openthread/heap.h>
#include <openthread/icmp6.h>
#include <openthread/instance.h>
#include <openthread/link.h>
#include <openthread/platform/openthread-system.h>
#include <openthread/tasklet.h>
#include <openthread/thread.h>
#endif // CHIP_ENABLE_OPENTHREAD

using namespace chip;
using namespace chip::Shell;
using namespace chip::DeviceLayer;

// TODO: Move softdevice initialization behind platform interface.
static void OnSoCEvent(uint32_t sys_evt, void * p_context)
{
#if CHIP_ENABLE_OPENTHREAD
    otSysSoftdeviceSocEvtHandler(sys_evt);
#endif
    UNUSED_PARAMETER(p_context);
}

CHIP_ERROR soft_device_init()
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    err = nrf_sdh_enable_request();
    SuccessOrExit(err);

    while (!nrf_sdh_is_enabled())
    {
    }

    // Register a handler for SOC events.
    NRF_SDH_SOC_OBSERVER(m_soc_observer, NRF_SDH_SOC_STACK_OBSERVER_PRIO, OnSoCEvent, NULL);

    {
        uint32_t appRAMStart = 0;

        // Configure the BLE stack using the default settings.
        // Fetch the start address of the application RAM.
        err = nrf_sdh_ble_default_cfg_set(CHIP_DEVICE_LAYER_BLE_CONN_CFG_TAG, &appRAMStart);
        SuccessOrExit(err);

        // Enable BLE stack.
        err = nrf_sdh_ble_enable(&appRAMStart);
        SuccessOrExit(err);
    }

exit:
    return err;
}

static void shell_task(void * args)
{
    Engine::Root().RunMainLoop();
}

ret_code_t ChipInit()
{
    ret_code_t ret = CHIP_NO_ERROR;

    NRF_LOG_INFO("Init CHIP stack");
    ret = chip::Platform::MemoryInit();
    if (ret != CHIP_NO_ERROR)
    {
        NRF_LOG_INFO("PlatformMgr().InitChipStack() failed");
        APP_ERROR_HANDLER(ret);
    }

    ret = PlatformMgr().InitChipStack();
    if (ret != CHIP_NO_ERROR)
    {
        NRF_LOG_INFO("PlatformMgr().InitChipStack() failed");
        APP_ERROR_HANDLER(ret);
    }

#if CHIP_ENABLE_OPENTHREAD
    NRF_LOG_INFO("Initializing OpenThread stack");

    nrf_cc310_platform_abort_init();
    nrf_cc310_platform_mutex_init();
    mbedtls_platform_setup(NULL);

    otSysInit(0, NULL);
    NRF_LOG_INFO("Initializing OpenThread stack");

    // Configure multiprotocol to work with BLE.
    {
        uint32_t retval = multiprotocol_802154_mode_set(MULTIPROTOCOL_802154_MODE_FAST_SWITCHING_TIMES);

        if (retval != NRF_SUCCESS)
        {
            NRF_LOG_INFO("multiprotocol 15.4 failed");
            APP_ERROR_HANDLER(CHIP_ERROR_INTERNAL);
        }
    }

    ret = ThreadStackMgr().InitThreadStack();
    if (ret != CHIP_NO_ERROR)
    {
        NRF_LOG_INFO("ThreadStackMgr().InitThreadStack() failed");
        APP_ERROR_HANDLER(ret);
    }

    ret = ConnectivityMgr().SetThreadDeviceType(ConnectivityManager::kThreadDeviceType_Router);
    if (ret != CHIP_NO_ERROR)
    {
        NRF_LOG_INFO("ConnectivityMgr().SetThreadDeviceType() failed");
        APP_ERROR_HANDLER(ret);
    }
#endif // CHIP_ENABLE_OPENTHREAD

    NRF_LOG_INFO("Starting CHIP task");
    ret = PlatformMgr().StartEventLoopTask();
    if (ret != CHIP_NO_ERROR)
    {
        NRF_LOG_INFO("PlatformMgr().StartEventLoopTask() failed");
        APP_ERROR_HANDLER(ret);
    }

#if CHIP_ENABLE_OPENTHREAD
    NRF_LOG_INFO("Starting OpenThread task");

    // Start OpenThread task
    ret = ThreadStackMgrImpl().StartThreadTask();
    if (ret != CHIP_NO_ERROR)
    {
        NRF_LOG_INFO("ThreadStackMgr().StartThreadTask() failed");
        APP_ERROR_HANDLER(ret);
    }
#endif // CHIP_ENABLE_OPENTHREAD

    return ret;
}

int main()
{
    soft_device_init();

    // Initialize the default streamer that was linked.
    const int rc = streamer_init(streamer_get());

    if (rc != 0)
    {
        ChipLogError(Shell, "Streamer initialization failed: %d", rc);
        return rc;
    }

    cmd_misc_init();
    //cmd_base64_init();
    //cmd_device_init();
    //cmd_btp_init();
    cmd_otcli_init();

    shell_task(nullptr);
    return 0;
}
