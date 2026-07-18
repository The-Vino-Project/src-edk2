/*
 * Copyright (c) 2026, pinrip, rixel, et al.
 *
 * Abstract:
 *      MI memory map services
 * Author:
 *      Chloe Pinrip
 */

#include <boot/bootlib.h>
#include <boot/memsv.h>

EFI_STATUS
GetMemoryMap(OUT PMEMORY_SNAPSHOT Result)
{
    EFI_STATUS Status;
    UINTN Idx;

    if (Result == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    /* Zero initialize the result */
    Result->MapSize = 0;
    Result->MemoryMap = NULL;
    Result->MapKey = 0;
    Result->DescriptorSize = 0;
    Result->DescriptorVersion = 0;

    /* First call, get the memory map size */
    Status = gBS->GetMemoryMap(
        &Result->MapSize,
        Result->MemoryMap,
        &Result->MapKey,
        &Result->DescriptorSize,
        &Result->DescriptorVersion
    );

    /* We should expect this error */
    if (Status != EFI_BUFFER_TOO_SMALL) {
        return Status;
    }

    Status = gBS->AllocatePool(
        EfiLoaderData,
        Result->MapSize,
        (VOID **)&Result->MemoryMap
    );

    if (EFI_ERROR(Status)) {
        return Status;
    }

    /*
     * The action of allocating a pool like we did beforehand may
     * alter the memory map in ways that require us to call this
     * twice depending on the firmware.
     */
    for (Idx = 0; Idx < 2; ++Idx) {
        Status = gBS->GetMemoryMap(
            &Result->MapSize,
            Result->MemoryMap,
            &Result->MapKey,
            &Result->DescriptorSize,
            &Result->DescriptorVersion
        );

        /* If we succeeded before the second call, take it */
        if (!EFI_ERROR(Status)) {
            break;
        }
    }

    if (EFI_ERROR(Status)) {
        gBS->FreePool(Result->MemoryMap);
        Result->MemoryMap = NULL;
        return Status;
    }

    return EFI_SUCCESS;
}
