/*
 * Copyright (c) 2026, pinrip, rixel, et al.
 *
 * Abstract:
 *      Boot MMU interface
 * Author:
 *      Chloe Pinrip
 */

#include <hal/mmu.h>

VOID
HalMmuReadVas(OUT MMU_VAS *Vas)
{
    asm volatile(
        "mov %%cr3, %0"
        : "=r" (Vas->Cr3)
        :
        : "memory"
    );
}

VOID
HalMmuWriteVas(IN MMU_VAS *Vas)
{
    asm volatile(
        "mov %0, %%cr3"
        :
        : "r" (Vas->Cr3)
        : "memory"
    );
}
