/*
 * Copyright (c) 2026, pinrip, rixel, et al.
 *
 * Abstract:
 *      UEFI file interface wrapper
 * Author:
 *      Chloe Pinrip
 */

#include <boot/file.h>

EFI_STATUS
GetBootVolume(OUT EFI_FILE_HANDLE *FileHandle)
{
    EFI_GUID FileSystemGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    EFI_GUID LipGuid = EFI_LOADED_IMAGE_PROTOCOL_GUID;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *IoVolume;
    EFI_LOADED_IMAGE *LoadedImage = NULL;
    EFI_STATUS Status;

    if (FileHandle == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    Status = gBS->HandleProtocol(
        gImageHandle,
        &LipGuid,
        (VOID **)&LoadedImage
    );

    if (EFI_ERROR(Status)) {
        return Status;
    }

    Status = gBS->HandleProtocol(
        LoadedImage->DeviceHandle,
        &FileSystemGuid,
        (VOID *)&IoVolume
    );

    if (EFI_ERROR(Status)) {
        return Status;
    }

    return IoVolume->OpenVolume(
        IoVolume,
        FileHandle
    );
}
