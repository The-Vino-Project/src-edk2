/*
 * Copyright (c) 2026, pinrip, rixel, et al.
 *
 * Abstract:
 *      Boot library defs
 * Author:
 *      Chloe Pinrip
 */

#ifndef _BOOTLIB_H_
#define _BOOTLIB_H_ 1

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/LoadedImage.h>

/* Externs */
extern EFI_FILE_HANDLE gBootVolume;

/*
 * Halt and catch fire if something goes wrong
 */
VOID BootHcf(VOID);

#endif  /* !_BOOTLIB_H_ */
