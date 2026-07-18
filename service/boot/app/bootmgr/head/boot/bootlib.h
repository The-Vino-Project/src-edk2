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
#include <Library/BaseMemoryLib.h>
#include <Protocol/LoadedImage.h>

/* Externs */
extern EFI_FILE_HANDLE gBootVolume;
extern VOID *gKernelImage;

/*
 * Halt and catch fire if something goes wrong
 */
VOID BootHcf(VOID);

/*
 * Load the kernel image into memory
 *
 * @EntryPoint:  Entry point is written here
 */
EFI_STATUS BootLoadKernel(OUT UINT64 *EntryPoint);

#endif  /* !_BOOTLIB_H_ */
