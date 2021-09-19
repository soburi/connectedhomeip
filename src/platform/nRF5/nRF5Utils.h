/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *    Copyright (c) 2019 Google LLC
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

/**
 *    @file
 *          Utilities for working with the Nordic nRF5 SDK.
 */

#pragma once

namespace chip {
namespace DeviceLayer {
namespace Internal {

void RegisterNRFErrorFormatter(void);
bool FormatNRFError(char * buf, uint16_t bufSize, CHIP_ERROR err);
inline CHIP_ERROR NRFErrorToCHIP_ERROR(ret_code_t err) { return CHIP_ERROR(CHIP_ERROR::Range::kPlatform, err); }

} // namespace Internal
} // namespace DeviceLayer
} // namespace chip
