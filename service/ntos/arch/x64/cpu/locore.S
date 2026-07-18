/*
 * Copyright (c) 2026, pinrip, rixel, et al.
 *
 * Abstract:
 *      X64 processor entrypoint
 * Author:
 *      Chloe Pinrip
 */

    .text
    .globl BspStart
    .extern NtP1Init
BspStart:
    cli
    cld
    xor %rbp, %rbp
    call NtP1Init
    mfence
1:  cli
    hlt
    jmp 1b
