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
BspStart:
    cli
    hlt
    jmp BspStart
