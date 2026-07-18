#
# Copyright (c) 2026, pinrip, rixel, et al.
#
# Abstract:
# 	    Generate an image from the boot files
# Author:
# 	    Chloe Pinrip
#

EFI_BOOT=artifacts/BOOTX64.EFI
IMG_NAME=artifacts/winvino.img

dd if=/dev/zero of=$IMG_NAME bs=1k count=1440
mformat -i $IMG_NAME -f 1440 ::
mmd -i $IMG_NAME ::/EFI
mmd -i $IMG_NAME ::/EFI/BOOT
mcopy -i $IMG_NAME $EFI_BOOT ::/EFI/BOOT
