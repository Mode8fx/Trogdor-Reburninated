export RGTOOLCHAIN=/usr/local/rg35xx/arm-buildroot-linux-gnueabihf_sdk-buildroot
rm -r build_rg35xx
mkdir build_rg35xx
cd build_rg35xx
cmake ../ -DCMAKE_TOOLCHAIN_FILE=$RGTOOLCHAIN/share/buildroot/toolchainfile.cmake -DRG35XX=ON
make