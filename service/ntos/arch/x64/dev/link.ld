/*
 * Copyright (c) 2026, pinrip, rixel, et al.
 *
 * Abstract:
 *      X64 kernel linker script
 * Author:
 *      Chloe Pinrip
 */

ENTRY(BspStart)

SECTIONS {
    /*
     * The kernel is to physically be loaded at around 1 meg of the
     * address space. It is to relocate itself to -2GiB later on in
     * the execution.
     */
    . = 1M;
    __PeStart = .;
    . += SIZEOF_HEADERS;

    .text : ALIGN(4K) {
        *(.text .text.*)
    }

    . += CONSTANT(MAXPAGESIZE);

    .data : ALIGN(4K) {
        *(.data .data.*)
    }

    . += CONSTANT(MAXPAGESIZE);

    .rdata : ALIGN(4K) {
        *(.rdata .rdata.*)
    }

    . += CONSTANT(MAXPAGESIZE);

    .bss : ALIGN(4K) {
        *(COMMON)
        *(.bss .bss.*)
    }

    . += CONSTANT(MAXPAGESIZE);

    .reloc : {
        KEEP(*(.reloc .reloc.*));
    }
}
