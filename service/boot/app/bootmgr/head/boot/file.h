/*
 * Copyright (c) 2026, pinrip, rixel, et al.
 *
 * Abstract:
 *      UEFI file interface wrapper
 * Author:
 *      Chloe Pinrip
 */

#ifndef _BOOT_FILE_H_
#define _BOOT_FILE_H_ 1

#include <boot/bootlib.h>

/*
 * Obtain the boot volume so that files may be loaded
 *
 * @FileHandle: Boot volume handle is written here
 */
EFI_STATUS GetBootVolume(OUT EFI_FILE_HANDLE *FileHandle);

#endif  /* !_BOOT_FILE_H_ */
