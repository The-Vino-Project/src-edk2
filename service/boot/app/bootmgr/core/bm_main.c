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

/* Fallback path if not found in BCD */
#define KERNEL_FALLBACK_PATH L"ntoskrnl.sys"

/* Private globals */
static EFI_FILE_HANDLE KernelImageHandle;

/* Globals */
EFI_FILE_HANDLE gBootVolume;
VOID *gKernelImage;

/*
 * Read the kernel image, caller should halt and catch fire
 * on failure.
 */
static EFI_STATUS
ReadKernelImage(VOID)
{
    EFI_STATUS Status;
    UINTN FileSize;

    /* TODO: Read from BCD */
    Status = gBootVolume->Open(
        gBootVolume,
        &KernelImageHandle,
        KERNEL_FALLBACK_PATH,
        EFI_FILE_MODE_READ,
        EFI_FILE_READ_ONLY | EFI_FILE_HIDDEN | EFI_FILE_SYSTEM
    );

    if (EFI_ERROR(Status)) {
        Print(L"Failed to open kernel image file\r\n");
        return Status;
    }

    /* Seek to the end to get the file size */
    Status = KernelImageHandle->SetPosition(
        KernelImageHandle,
        0xFFFFFFFFFFFFFFFF
    );

    if (EFI_ERROR(Status)) {
        Print(L"Seek to end of kernel image failed\r\n");
        return Status;
    }

    /* Get the kernel image size */
    Status = KernelImageHandle->GetPosition(
        KernelImageHandle,
        &FileSize
    );

    if (EFI_ERROR(Status)) {
        Print(L"Failed to get kernel image size\r\n");
        return Status;
    }

    /* Reset the file position */
    Status = KernelImageHandle->SetPosition(
        KernelImageHandle,
        0
    );

    if (EFI_ERROR(Status)) {
        Print(L"Seek to start of kernel image failed\r\n");
        return Status;
    }

    Status = gBS->AllocatePool(
        EfiLoaderData,
        FileSize,
        (VOID **)&gKernelImage
    );

    if (EFI_ERROR(Status)) {
        Print(L"Failed to allocate memory for kernel image\r\n");
        return Status;
    }

    Status = KernelImageHandle->Read(
        KernelImageHandle,
        &FileSize,
        gKernelImage
    );

    if (EFI_ERROR(Status)) {
        Print(L"Failed to read kernel image\r\n");
        return Status;
    }

    Print(L"Consumed %d bytes from kernel image\r\n", FileSize);
    return EFI_SUCCESS;
}

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

    Status = ReadKernelImage();
    if (EFI_ERROR(Status)) {
        BootHcf();
    }

    Status = BootLoadKernel();
    if (EFI_ERROR(Status)) {
        BootHcf();
    }

    for (;;);
}
