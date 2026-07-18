/*
 * Copyright (c) 2026, pinrip, rixel, et al.
 *
 * Abstract:
 *      Boot HAL MMU interface
 * Author:
 *      Chloe Pinrip
 */

#ifndef _HAL_MMU_H_
#define _HAL_MMU_H_ 1

#include <boot/bootlib.h>
#include <machine/vas.h>
#include <sdk/ntdef.h>

#define PAGE_READ   0x00
#define PAGE_WRITE  BIT(0)
#define PAGE_EXEC   BIT(1)

/*
 * Read the virtual address space
 *
 * @Vas:  Virtual address space is written here
 */
VOID HalMmuReadVas(OUT MMU_VAS *Vas);

/*
 * Write a new virtual address space
 *
 * @Vas: Virtual address space is written from here
 */
VOID HalMmuWriteVas(IN MMU_VAS *Vas);

/*
 * Map a single page of memory
 *
 * @Vas:            Virtual address space to map within
 * @VirtualBase:    Virtual base to map
 * @PhysicalBase:   Physical base to map to
 * @Prot:           Protection flags
 *
 * XXX: This should not be called after ExitBootSerivces()
 */
EFI_STATUS HalMmuMapPage(
    IN MMU_VAS *Vas, IN UINT64 VirtualBase,
    IN UINT64 PhysicalBase, IN USHORT Prot
);

#endif  /* !_HAL_MMU_H_ */
