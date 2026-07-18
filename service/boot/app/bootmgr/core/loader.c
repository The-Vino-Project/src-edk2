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
    PPE32P_SECTION_HEADER SectionHeaderBase;
    PPE32P_SECTION_HEADER SectionHeader;
    PPE32P_OPT_HEADER OptHeader;
    UINT32 *PeHeaderOff;
    USHORT SectionIdx, NumberOfSections;

    PeHeaderOff = PTR_OFFSET(gKernelImage, PE_E_LFANEW_OFF);
    PeHeader = PTR_OFFSET(gKernelImage, *PeHeaderOff);
    if (PeHeader->Magic != PE_HEADER_MAGIC) {
        Print(L"Bad kernel image magic\r\n");
        return EFI_LOAD_ERROR;
    }

    /* Get the optional header and base of section headers */
    OptHeader = PTR_OFFSET(PeHeader, sizeof(PE32_HEADER));
    SectionHeaderBase = PTR_OFFSET(
        OptHeader,
        PeHeader->SizeOfOptionalHeader
    );

    /* Iterate every section header */
#define SECTION_HEADER(IDX) \
    PTR_OFFSET(SectionHeaderBase, (IDX) * sizeof(PE32P_SECTION_HEADER))
    NumberOfSections = PeHeader->NumberOfSections;
    for (SectionIdx = 0; SectionIdx < NumberOfSections; ++SectionIdx) {
        SectionHeader = SECTION_HEADER(SectionIdx);
        Print(L"Section name : %a\r\n", SectionHeader->Name);
        Print(L"Section RVA : %p\r\n", SectionHeader->VirtualAddress);
        Print(L"Section VSIZE : %d\r\n", SectionHeader->VirtualSize);
    }
#undef SECTION_HEADER
    return EFI_SUCCESS;
}
