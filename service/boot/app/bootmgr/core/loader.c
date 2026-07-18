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
#include <hal/mmu.h>

EFI_STATUS
BootLoadKernel(VOID)
{
    PPE32_HEADER PeHeader;
    PPE32P_SECTION_HEADER SectionHeaderBase;
    PPE32P_SECTION_HEADER SectionHeader;
    PPE32P_OPT_HEADER OptHeader;
    UINT32 *PeHeaderOff;
    USHORT SectionIdx, NumberOfSections;
    UINTN MapSize, ZeroFillSize;
    UINTN MapOff;
    UINT8 *Source, *Dest;
    MMU_VAS Vas;
    EFI_STATUS Status;

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

    HalMmuReadVas(&Vas);

    /* Iterate every section header */
#define SECTION_HEADER(IDX) \
    PTR_OFFSET(SectionHeaderBase, (IDX) * sizeof(PE32P_SECTION_HEADER))
    NumberOfSections = PeHeader->NumberOfSections;
    for (SectionIdx = 0; SectionIdx < NumberOfSections; ++SectionIdx) {
        SectionHeader = SECTION_HEADER(SectionIdx);
        MapSize = ALIGN_UP(SectionHeader->SizeOfRawData, PAGESIZE);
        Dest = PTR_OFFSET(gKernelImage, SectionHeader->VirtualAddress);

        for (MapOff = 0; MapOff < MapSize; MapOff += PAGESIZE) {
            /* TODO: Dynamically assign protection flags */
            Status = HalMmuMapPage(
                &Vas,
                (UPTR)Dest + MapOff,
                (UPTR)Dest + MapOff,
                PAGE_READ | PAGE_WRITE | PAGE_EXEC
            );

            if (EFI_ERROR(Status)) {
                Print(L"Failed to map %p\r\n", (UPTR)Dest + MapOff);
                return Status;
            }
        }

        /* Copy the data */
        if (SectionHeader->SizeOfRawData > 0) {
            Source = PTR_OFFSET(gKernelImage, SectionHeader->PointerToRawData);
            CopyMem(Dest, Source, SectionHeader->SizeOfRawData);
        }

        /* Zero fill uninitialized data */
        if (SectionHeader->VirtualSize > SectionHeader->SizeOfRawData) {
            ZeroFillSize = SectionHeader->VirtualSize - SectionHeader->SizeOfRawData;
            Dest = PTR_OFFSET(Dest, SectionHeader->SizeOfRawData);
            ZeroMem(Dest, ZeroFillSize);
        }
    }
#undef SECTION_HEADER

    Print(L"Image loaded OK\r\n");
    return EFI_SUCCESS;
}
