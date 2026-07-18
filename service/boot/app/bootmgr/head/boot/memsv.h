/*
 * Copyright (c) 2026, pinrip, rixel, et al.
 *
 * Abstract:
 *      MI memory related services
 * Author:
 *      Chloe Pinrip
 */

#ifndef _BOOT_MEMSV_H_
#define _BOOT_MEMSV_H_ 1

#include <boot/bootlib.h>

/*
 * A memory snapshot describes the memory map
 * provided by platform firmware.
 *
 * @MapSize:            Size of the memory map in bytes
 * @MemoryMap:          Memory map itself
 * @MapKey:             Used to exit boot services
 * @DescriptorSize:     Memory map descriptor size
 * @DescriptorVersion:  Memory map descriptor version
 */
typedef struct {
    UINTN MapSize;
    EFI_MEMORY_DESCRIPTOR *MemoryMap;
    UINTN MapKey;
    UINTN DescriptorSize;
    UINT32 DescriptorVersion;
} MEMORY_SNAPSHOT, *PMEMORY_SNAPSHOT;

/*
 * Obtain the platform memory map in the form of a memory
 * snapshot.
 *
 * @Result: Result is written here
 */
EFI_STATUS GetMemoryMap(OUT PMEMORY_SNAPSHOT Result);

#endif  /* !_BOOT_MEMSV_H_ */
