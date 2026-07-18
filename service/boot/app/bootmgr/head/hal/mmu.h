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

#endif  /* !_HAL_MMU_H_ */
