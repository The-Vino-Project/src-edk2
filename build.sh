#!/bin/sh
#
# Copyright (c) 2026, pinrip, rixel, et al.
#
# Abstract:
#       Top-level build driver
# Author:
#       Chloe Pinrip
#

MAKE=make

#
# Check if a list of deps are installed
#
# $@:  List of deps to check
#
check_deps() {
    for dep in $@
    do
        printf "Checking if $dep is installed... "
        which $dep &>/dev/null
        if [ $? -ne 0 ]
        then
            echo "no"
            echo "Please install '$dep'!"
            exit 1
        fi

        echo "yes"
    done
}

#
# <$1>: Build target
# <$2>: Build message
#
make_build() {
    echo -e "[*] $2"
    pushd $1;   \
        $MAKE
    popd
}

#
# Begin the build process
#
build() {
    mkdir -p artifacts/

    if [ -z "${NT_BUILD_SOURCED}" ]
    then
        echo -e "fatal: Please run '. service/dev/build.env' first!"
        exit 1
    fi

    make_build          \
        service/boot/   \
        "Building bootloader..."

    echo "[*] Generating image..."
    ./tools/gen-img.sh
}

# Verify all deps
check_deps  \
    clang   \
    mtools  \
    rsync   \
    git

# Begin the build process
build
