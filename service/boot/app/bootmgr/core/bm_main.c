/*
 * Copyright (c) 2026, pinrip, rixel, et al.
 *
 * Abstract:
 *      Boot manager entry
 * Author:
 *      Chloe Pinrip
 */

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>

EFI_STATUS
EFIAPI
BmEntry(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE* SystemTable)
{
    for (;;);
}
