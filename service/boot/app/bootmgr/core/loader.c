/*
 * Copyright (c) 2026, pinrip, rixel, et al.
 *
 * Abstract:
 *      Kernel image loader
 * Author:
 *      Chloe Pinrip
 */

#define _BOOT_SOURCE
#include <boot/bootlib.h>
#include <sdk/exe/pe.h>
#include <sdk/ntdef.h>

EFI_STATUS
BootLoadKernel(VOID)
{
    PPE32_HEADER PeHeader;
    UINT32 *PeHeaderOff;

    PeHeaderOff = PTR_OFFSET(gKernelImage, PE_E_LFANEW_OFF);
    PeHeader = PTR_OFFSET(gKernelImage, *PeHeaderOff);
    if (PeHeader->Magic != PE_HEADER_MAGIC) {
        Print(L"Bad kernel image magic\r\n");
        return EFI_LOAD_ERROR;
    }

    return EFI_SUCCESS;
}
