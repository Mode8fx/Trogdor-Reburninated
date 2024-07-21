@echo off

:: Manual sleep amounts (because `start /wait` doesn't work...)
set SLEEP_COMPILE=45
set SLEEP_CLEAN=2

:: Path: repo (the folder that contains /src)
set REPO=D:/GitHub/Trogdor-Reburninated/Trogdor-Reburninated
set REPO_DKP=/d/GitHub/Trogdor-Reburninated/Trogdor-Reburninated
set REPO_WSL=/mnt%REPO_DKP%

:: Path: devkitPro
set DEVKITPRO=C:/devkitPro/msys2/mingw64.exe

:: Path (MSYS2): Makefile directory
set MAKEFILES_DKP=%REPO_DKP%/Makefiles
set MAKEFILES_WSL=/mnt%MAKEFILES_DKP%



:: Makefile: Linux
set MAKEFILE_DKP_LINUX=%MAKEFILES_DKP%/Makefile_linux
set MAKEFILE_WSL_LINUX=%MAKEFILES_WSL%/Makefile_linux

:: Makefile: Gamecube
set MAKEFILE_DKP_GC=%MAKEFILES_DKP%/Makefile_gc
set MAKEFILE_WSL_GC=%MAKEFILES_WSL%/Makefile_gc

:: Makefile: Wii
set MAKEFILE_DKP_WII=%MAKEFILES_DKP%/Makefile_wii
set MAKEFILE_WSL_WII=%MAKEFILES_WSL%/Makefile_wii

:: Makefile: Wii U
set MAKEFILE_DKP_WII_U=%MAKEFILES_DKP%/make_wii_u.sh
set MAKEFILE_WSL_WII_U=%MAKEFILES_WSL%/make_wii_u.sh

:: Makefile: Switch
set MAKEFILE_DKP_SWITCH=%MAKEFILES_DKP%/Makefile_switch
set MAKEFILE_WSL_SWITCH=%MAKEFILES_WSL%/Makefile_switch

:: Makefile: 3DS
set MAKEFILE_DKP_3DS=%MAKEFILES_DKP%/Makefile_3ds
set MAKEFILE_WSL_3DS=%MAKEFILES_WSL%/Makefile_3ds

:: Makefile: PSP
set MAKEFILE_DKP_PSP=%MAKEFILES_DKP%/Makefile_psp
set MAKEFILE_WSL_PSP=%MAKEFILES_WSL%/Makefile_psp

:: Makefile: Vita
set MAKEFILE_DKP_VITA=%MAKEFILES_DKP%/make_vita.sh
set MAKEFILE_WSL_VITA=%MAKEFILES_WSL%/make_vita.sh

:: Makefile: Xbox (original)
set MAKEFILE_DKP_XBOX=%MAKEFILES_DKP%/Makefile_xbox
set MAKEFILE_WSL_XBOX=%MAKEFILES_WSL%/Makefile_xbox

:: Makefile: RG35XX
set MAKEFILE_DKP_RG35XX=%MAKEFILES_DKP%/make_rg35xx.sh
set MAKEFILE_WSL_RG35XX=%MAKEFILES_WSL%/make_rg35xx.sh



:: Command: (WSL) Compile for Linux
echo Linux: Compiling with WSL...
wsl -e sh -c "cd %REPO_WSL% && make -f %MAKEFILE_WSL_LINUX%"
echo Linux: Moving compiled binary to /dist/Trogdor-Reburninated-linux...
mv %REPO%/trogdorrb %REPO%/dist/Trogdor-Reburninated-linux
echo Linux: Cleaning up...
wsl -e sh -c "cd %REPO_WSL% && make clean -f %MAKEFILE_WSL_LINUX%"

:: Command: (devkitPro) Compile for Gamecube
echo Gamecube: Compiling with devkitPro...
:: make is run twice to get around a makefile issue
start /wait "" %DEVKITPRO% /usr/bin/bash -lc "cd %REPO_DKP%; make -f %MAKEFILE_DKP_GC%; make -f %MAKEFILE_DKP_GC%"
sleep %SLEEP_COMPILE%
echo Gamecube: Moving compiled dol to /dist/boot-gc.dol...
mv %REPO%/boot.dol %REPO%/dist/boot-gc.dol
echo Gamecube: Cleaning up...
start /wait "" %DEVKITPRO% /usr/bin/bash -lc "cd %REPO_DKP%; make clean -f %MAKEFILE_DKP_GC%"
sleep %SLEEP_CLEAN%

:: Command: (devkitPro) Compile for Wii
echo Wii: Compiling with devkitPro...
:: make is run twice to get around a makefile issue
start /wait "" %DEVKITPRO% /usr/bin/bash -lc "cd %REPO_DKP%; make -f %MAKEFILE_DKP_WII%; make -f %MAKEFILE_DKP_WII%"
sleep %SLEEP_COMPILE%
echo Wii: Moving compiled dol to /dist/boot-wii.dol...
mv %REPO%/boot.dol %REPO%/dist/boot-wii.dol
echo Wii: Cleaning up...
start /wait "" %DEVKITPRO% /usr/bin/bash -lc "cd %REPO_DKP%; make clean -f %MAKEFILE_DKP_WII%"
sleep %SLEEP_CLEAN%

:: Command: (devkitPro) Compile for Wii U
echo Wii U: Compiling with WSL...
start /wait "" %DEVKITPRO% /usr/bin/bash -lc "cd %REPO_DKP%; sh %MAKEFILE_DKP_WII_U%"
sleep %SLEEP_COMPILE%
echo Wii U: Moving compiled rpx to /dist/Trogdor-Reburninated.rpx...
mv %REPO%/build_wii_u/trogdorrb.rpx %REPO%/dist/Trogdor-Reburninated.rpx
echo Wii U: Cleaning up...
rm -r %REPO%/build_wii_u
sleep %SLEEP_CLEAN%
echo Wii U: Didn't make WHUB... use WHUB Packager for that.

:: Command: (devkitPro) Compile for Switch
echo Switch: Compiling with devkitPro...
start /wait "" %DEVKITPRO% /usr/bin/bash -lc "cd %REPO_DKP%; make -f %MAKEFILE_DKP_SWITCH%"
sleep %SLEEP_COMPILE%
echo Switch: Moving compiled nro to /dist/Trogdor-Reburninated.nro...
mv %REPO%/Trogdor-Reburninated.nro %REPO%/dist/Trogdor-Reburninated.nro
echo Switch: Cleaning up...
start /wait "" %DEVKITPRO% /usr/bin/bash -lc "cd %REPO_DKP%; make clean -f %MAKEFILE_DKP_SWITCH%"
sleep %SLEEP_CLEAN%

:: Command: (devkitPro) Compile for 3DS
echo 3DS: Compiling with devkitPro...
start /wait "" %DEVKITPRO% /usr/bin/bash -lc "cd %REPO_DKP%; make -f %MAKEFILE_DKP_3DS%"
sleep %SLEEP_COMPILE%
echo 3DS: Moving compiled 3dsx to /dist/Trogdor-Reburninated.3dsx...
mv %REPO%/Trogdor-Reburninated.3dsx %REPO%/dist/Trogdor-Reburninated.3dsx
echo 3DS: Moving compiled elf to /dist/Trogdor-Reburninated-3ds.elf...
mv %REPO%/Trogdor-Reburninated.elf %REPO%/dist/Trogdor-Reburninated-3ds.elf
echo 3DS: Cleaning up...
start /wait "" %DEVKITPRO% /usr/bin/bash -lc "cd %REPO_DKP%; make clean -f %MAKEFILE_DKP_3DS%"
sleep %SLEEP_CLEAN%
echo 3DS: Didn't make CIA... use makerom and bannertool for that.

:: Command: (WSL) Compile for Vita
echo Vita: Compiling with WSL...
wsl -e sh -c "cd %REPO_WSL% && sh %MAKEFILE_WSL_VITA%"
echo Vita: Moving compiled vpk to /dist/Trogdor-Reburninated.vpk...
mv %REPO%/build_vita/trogdorrb.vpk %REPO%/dist/Trogdor-Reburninated.vpk
echo Vita: Cleaning up...
rm -r %REPO%/build_vita

:: Command: (WSL) Compile for RG35XX
echo RG35XX: Compiling with WSL...
wsl -e sh -c "cd %REPO_WSL% && sh %MAKEFILE_WSL_RG35XX%"
echo RG35XX: Moving compiled binary to /dist/trogdorrb-rg35xx...
mv %REPO%/build_rg35xx/trogdorrb %REPO%/dist/trogdorrb-rg35xx
echo RG35XX: Cleaning up...
rm -r %REPO%/build_rg35xx

rem :: Command: (WSL) Compile for PSP (TODO: This doesn't work for some reason)
rem echo PSP: Compiling with WSL...
rem wsl -e sh -c "cd %REPO_WSL% && make -f %MAKEFILE_WSL_PSP%"
rem echo PSP: Moving compiled binary to /dist/Trogdor-Reburninated-linux...
rem mv %REPO%/trogdorrb %REPO%/dist/Trogdor-Reburninated-linux
rem echo PSP: Cleaning up...
rem wsl -e sh -c "cd %REPO_WSL% && make clean -f %MAKEFILE_WSL_PSP%"

rem :: Command: (WSL) Compile for Xbox (original) (this doesn't work since ./activate breaks out of script)
rem echo Xbox: Compiling with WSL...
rem wsl -e sh -c "cd ~/nxdk/bin && ./activate && cd %REPO_WSL% && make -f %MAKEFILE_WSL_XBOX%"
rem echo Xbox: Moving compiled binary to /dist/trogdorrb-xbox...
rem mv %REPO%/build_xbox/trogdorrb %REPO%/dist/trogdorrb-xbox

echo Done.