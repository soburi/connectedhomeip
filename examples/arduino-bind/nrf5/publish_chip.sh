mkdir -p dist/cores/nRF5/nordic/external/openthread/include

mkdir -p dist/cores/nRF5/nordic/external/connectedhomeip/gen/
mkdir -p dist/cores/nRF5/nordic/external/connectedhomeip/lib/
mkdir -p dist/cores/nRF5/nordic/external/connectedhomeip/examples/platform/
mkdir -p dist/cores/nRF5/nordic/external/connectedhomeip/examples/lock-app/


cp `find out/release/obj/third_party/connectedhomeip/src -name '*.a'` dist/cores/nRF5/nordic/external/connectedhomeip/lib/
cp -rfp out/release/gen/include dist/cores/nRF5/nordic/external/connectedhomeip/gen/

mv dist/cores/nRF5/nordic/external/connectedhomeip/gen/include/openthread*.h dist/cores/nRF5/nordic/external/openthread/include/
cp third_party/connectedhomeip/.* dist/cores/nRF5/nordic/external/connectedhomeip/
cp -r third_party/connectedhomeip/.github dist/cores/nRF5/nordic/external/connectedhomeip/
cp -r third_party/connectedhomeip/.devcontainer dist/cores/nRF5/nordic/external/connectedhomeip/
cp third_party/connectedhomeip/* dist/cores/nRF5/nordic/external/connectedhomeip/

find third_party/connectedhomeip/src/ -type f | egrep -v '\.(c|cpp)$' | sed 's/^third_party\/connectedhomeip\///'> /tmp/list.T
#find src/ -name '*.hpp' >> /tmp/list.T
tar cf /tmp/hoge.tar -C third_party/connectedhomeip/ -T /tmp/list.T 
tar xf /tmp/hoge.tar -C dist/cores/nRF5/nordic/external/connectedhomeip/

cp -r third_party/connectedhomeip/.devcontainer dist/cores/nRF5/nordic/external/connectedhomeip/
cp -r third_party/connectedhomeip/.github dist/cores/nRF5/nordic/external/connectedhomeip/
cp -rfp  third_party/connectedhomeip/examples/platform/nrf5 dist/cores/nRF5/nordic/external/connectedhomeip/examples/platform/
cp -rfp  third_party/connectedhomeip/examples/lock-app/lock-common dist/cores/nRF5/nordic/external/connectedhomeip/examples/lock-app/

rm -r dist/cores/nRF5/nordic/external/connectedhomeip/src/platform/Darwin
rm -r dist/cores/nRF5/nordic/external/connectedhomeip/src/platform/EFR32
rm -r dist/cores/nRF5/nordic/external/connectedhomeip/src/platform/ESP32
rm -r dist/cores/nRF5/nordic/external/connectedhomeip/src/platform/K32W
rm -r dist/cores/nRF5/nordic/external/connectedhomeip/src/platform/Linux
rm -r dist/cores/nRF5/nordic/external/connectedhomeip/src/platform/Zephyr
rm -r dist/cores/nRF5/nordic/external/connectedhomeip/src/platform/cc13x2_26x2
rm -r dist/cores/nRF5/nordic/external/connectedhomeip/src/platform/mbed
rm -r dist/cores/nRF5/nordic/external/connectedhomeip/src/platform/nrfconnect
rm -r dist/cores/nRF5/nordic/external/connectedhomeip/src/platform/qpg
rm -r dist/cores/nRF5/nordic/external/connectedhomeip/src/platform/telink
rm -r dist/cores/nRF5/nordic/external/connectedhomeip/src/test_driver

mkdir -p dist/cores/nRF5/nordic/external/nrf_security/include/
mkdir -p dist/cores/nRF5/nordic/external/nrf_security/config/nrf52840/config
mkdir -p dist/cores/nRF5/nordic/external/nrf_security/lib/
cp -rfp third_party/connectedhomeip/third_party/openthread/ot-nrf528xx/third_party/NordicSemiconductor/libraries/nrf_security/include/ dist/cores/nRF5/nordic/external/nrf_security/
cp -rfp third_party/connectedhomeip/third_party/openthread/ot-nrf528xx/third_party/NordicSemiconductor/libraries/nrf_security/config/nrf52840/config/nrf-config.h dist/cores/nRF5/nordic/external/nrf_security/config/nrf52840/config/
cp -rfp third_party/connectedhomeip/third_party/openthread/ot-nrf528xx/third_party/NordicSemiconductor/libraries/nrf_security/mbedtls_plat_config/  dist/cores/nRF5/nordic/external/nrf_security/
cp -rfp third_party/connectedhomeip/third_party/openthread/ot-nrf528xx/third_party/NordicSemiconductor/libraries/nrf_security/nrf_cc310_platform/  dist/cores/nRF5/nordic/external/
rm dist/cores/nRF5/nordic/external/nrf_cc310_platform/src/*zephyr*
cp -rfp third_party/connectedhomeip/third_party/openthread/ot-nrf528xx/third_party/NordicSemiconductor/libraries/nrf_security/lib/ dist/cores/nRF5/nordic/external/nrf_security/









mkdir -p dist/cores/nRF5/nordic/external/openthread/include/openthread/platform/utils/
mkdir -p dist/cores/nRF5/nordic/external/openthread/include/spinel
mkdir -p dist/cores/nRF5/nordic/external/openthread/lib/nrf52840/gcc/
cp -rfp third_party/connectedhomeip/third_party/openthread/repo/include/openthread/ dist/cores/nRF5/nordic/external/openthread/include/
cp -rfp third_party/connectedhomeip/third_party/openthread/ot-nrf528xx/src/src/*.h dist/cores/nRF5/nordic/external/openthread/include/openthread/platform/
cp -rfp third_party/connectedhomeip/third_party/openthread/ot-nrf528xx/openthread/src/core/config/ dist/cores/nRF5/nordic/external/openthread/include/
cp -rfp third_party/connectedhomeip/third_party/openthread/ot-nrf528xx/openthread/examples/platforms/utils/*.h dist/cores/nRF5/nordic/external/openthread/include/openthread/platform/utils/
cp -rfp third_party/connectedhomeip/third_party/openthread/ot-nrf528xx/openthread/examples/platforms/openthread-system.h dist/cores/nRF5/nordic/external/openthread/include/openthread/platform/
cp -rfp third_party/connectedhomeip/third_party/openthread/ot-nrf528xx/openthread/doc/ot_api_doc.h dist/cores/nRF5/nordic/external/openthread/include/openthread/
cp -rfp third_party/connectedhomeip/third_party/openthread/repo/src/lib/spinel/*.h dist/cores/nRF5/nordic/external/openthread/include/spinel/
cp -rfp third_party/connectedhomeip/third_party/openthread/ot-nrf528xx/openthread/src/core/openthread-core-config.h dist/cores/nRF5/nordic/external/openthread/include/
cp `find out/release -name 'libopenthread*.a'` dist/cores/nRF5/nordic/external/openthread/lib/nrf52840/gcc/
cp `find out/release -name 'libnordic*.a'` dist/cores/nRF5/nordic/external/openthread/lib/nrf52840/gcc/
