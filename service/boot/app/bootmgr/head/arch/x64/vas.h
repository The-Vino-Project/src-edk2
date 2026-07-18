/*
 * Copyright (c) 2026, pinrip, rixel, et al.
 *
 * Abstract:
 *      Virtual address space structure
 * Author:
 *      Chloe Pinrip
 */

#ifndef _MACHINE_VAS_H_
#define _MACHINE_VAS_H_ 1

#include <boot/bootlib.h>

/*
 * AMD64 virtual address space
 *
 * @Cr3:  CR3 register value
 */
typedef struct {
    UINT64 Cr3;
} MMU_VAS;

#endif  /* !_MACHINE_VAS_H_ */
