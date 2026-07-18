#!/bin/sh
#
# Copyright (c) 2026, Chloe Pinrip, Rixel, et al.
# Provided under the BSD-3 clause
#
# Abstract:
#       NT loader build script
# Author:
#       Chloe Pinrip
#

sync_sdk() {
    mkdir -p app/bootmgr/head/sdk/
    rsync -avr $NT_PROJECT_ROOT/sdk/head/* \
        app/bootmgr/head/sdk
}

build_edk2() {
    git clone https://github.com/tianocore/edk2.git
    export WORKSPACE=$PWD/edk2

    pushd edk2/;
        export EDK_TOOLS_PATH=$PWD/BaseTools
        git submodule update --init
        make -C BaseTools
    popd

    export PACKAGES_PATH="$WORKSPACE:$PWD/app"

    if [ -z "${EDK_SOURCED}" ];
    then
        cd edk2
        source ./edksetup.sh
        cd ../
        export EDK_SOURCED=1
    fi

    build -a X64 -t GCC -p bootmgr/ntldr.dsc
    cp edk2/Build/MdeModule/DEBUG_GCC/X64/bootmgr.efi \
        $NT_PROJECT_ROOT/artifacts/BOOTX64.EFI
}

sync_sdk
build_edk2
