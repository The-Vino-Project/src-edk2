/*
 * Copyright (c) 2026, pinrip, rixel, et al.
 *
 * Abstract:
 *      Boot manager entry
 * Author:
 *      Chloe Pinrip
 */

#include <boot/bootlib.h>

EFI_STATUS
EFIAPI
BmEntry(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
    gBS = SystemTable->BootServices;
    gST = SystemTable;
    gImageHandle = gImageHandle;

    for (;;);
}
