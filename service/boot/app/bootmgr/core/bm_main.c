/*
 * Copyright (c) 2026, pinrip, rixel, et al.
 *
 * Abstract:
 *      Boot manager entry
 * Author:
 *      Chloe Pinrip
 */

#include <boot/bootlib.h>
#include <boot/file.h>

/* Globals */
EFI_FILE_HANDLE gBootVolume;

EFI_STATUS
EFIAPI
BmEntry(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS Status;

    gBS = SystemTable->BootServices;
    gST = SystemTable;
    gImageHandle = gImageHandle;

    /*
     * First we should ensure the watchdog timer is disabled so the system doesn't
     * suddenly restart. This should not happen after we exit boot services but it
     * is good to be careful.
     */
    gBS->SetWatchdogTimer(
        0,
        0,
        0,
        NULL
    );

    /* Reset the console */
    gST->ConOut->Reset(
        gST->ConOut,
        TRUE
    );

    /* Obtain the boot volume */
    Status = GetBootVolume(&gBootVolume);
    if (EFI_ERROR(Status)) {
        Print(L"Failed to obtain boot volume\n");
        BootHcf();
    }

    for (;;);
}
