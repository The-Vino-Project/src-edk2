/*
 * Copyright (c) 2026, pinrip, rixel, et al.
 *
 * Abstract:
 *      Boot MMU interface
 * Author:
 *      Chloe Pinrip
 */

#include <hal/mmu.h>
#include <boot/bootlib.h>

/*
 * Page-Table Entry (PTE) flags
 *
 * See Intel SDM Vol 3A, Section 4.5, Table 4-19
 */
#define PTE_ADDR_MASK   0x000FFFFFFFFFF000
#define PTE_P           BIT(0)        /* Present */
#define PTE_RW          BIT(1)        /* Writable */
#define PTE_US          BIT(2)        /* User r/w allowed */
#define PTE_PWT         BIT(3)        /* Page-level write-through */
#define PTE_PCD         BIT(4)        /* Page-level cache disable */
#define PTE_ACC         BIT(5)        /* Accessed */
#define PTE_DIRTY       BIT(6)        /* Dirty (written-to page) */
#define PTE_PS          BIT(7)        /* Page size */
#define PTE_GLOBAL      BIT(8)        /* Global; sticky */
#define PTE_NX          BIT(63)       /* Execute-disable */

/*
 * Valid paging structure levels
 */
typedef enum {
    PAGEMAP_PML1,
    PAGEMAP_PML2,
    PAGEMAP_PML3,
    PAGEMAP_PML4
} PAGEMAP_LEVEL;

/*
 * Flush a single virtual address from the translation
 * lookaside buffer.
 *
 * @VirtualBase:  Virtual address to flush
 */
static inline VOID
MmuTlbFlushSingle(UINT64 VirtualBase)
{
    VirtualBase = ALIGN_DOWN(VirtualBase, 4096);
    asm volatile(
        "invlpg %0"
        :
        : "r" (VirtualBase)
        : "memory"
    );
}

/*
 * Extract a pagemap index from a virtual address for a given
 * level.
 *
 * @VirtualBase: Virtual base address to use as key
 * @Level:       Pagemap level to get index of
 */
static inline USHORT
MmuPageMapIndex(IN UPTR VirtualBase, IN PAGEMAP_LEVEL Level)
{
    switch (Level) {
    case PAGEMAP_PML1:  return (VirtualBase >> 12) & 0x1FF;
    case PAGEMAP_PML2:  return (VirtualBase >> 21) & 0x1FF;
    case PAGEMAP_PML3:  return (VirtualBase >> 30) & 0x1FF;
    case PAGEMAP_PML4:  return (VirtualBase >> 39) & 0x1FF;
    }

    Print(L"Bad MMU level index\n");
    BootHcf();
    __builtin_unreachable();
}

/*
 * Obtain PTE flags from MI page protection
 * flags
 *
 * @Prot:  Protection flags to convert
 */
static UINTN
MmuProtToPte(IN USHORT Prot)
{
    UINTN PteFlags = PTE_P | PTE_NX;

    if (ISSET(Prot, PAGE_WRITE))
        PteFlags |= PTE_RW;
    if (ISSET(Prot, PAGE_EXEC))
        PteFlags &= ~PTE_NX;

    return PteFlags;
}

/*
 * Extract a pagemap at a specific level
 *
 * @Vas:            Virtual address space to translate from
 * @VirtualBase:    Virtual base address
 * @Level:          Level to extract
 * @Alloc:          If true, allocate new level
 *
 * Returns the pogemap level base on success, otherwise NULL
 * on failure.
 */
static UINT64 *
MmuPageMapExtract(
    IN MMU_VAS *Vas, IN UINT64 VirtualBase,
    IN PAGEMAP_LEVEL Level, BOOLEAN Alloc)
{
    UINT64 *PageMap;
    PAGEMAP_LEVEL CurrentLevel;
    EFI_PHYSICAL_ADDRESS PhysicalBase;
    UINTN Index;
    EFI_STATUS Status;

    if (Vas == NULL) {
        return NULL;
    }

    /* Get the top-level */
    CurrentLevel = PAGEMAP_PML4;
    PageMap = (VOID *)(Vas->Cr3 & PTE_ADDR_MASK);

    /* Iterate each level */
    while (CurrentLevel > Level) {
        Index = MmuPageMapIndex(VirtualBase, CurrentLevel);

        if (ISSET(PageMap[Index], PTE_P)) {
            PageMap = (VOID *)(PageMap[Index] & PTE_ADDR_MASK);
            --CurrentLevel;
            continue;
        }

        if (!Alloc) {
            return NULL;
        }

        Status = gBS->AllocatePages(
            AllocateAnyPages,
            EfiLoaderData,
            1,
            &PhysicalBase
        );

        if (EFI_ERROR(Status)) {
            return NULL;
        }

        ZeroMem((VOID *)PhysicalBase, 4096);
        PageMap[Index] = PhysicalBase | PTE_P | PTE_RW;
        PageMap = (VOID *)PhysicalBase;
        --CurrentLevel;
    }

    return PageMap;
}


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

EFI_STATUS HalMmuMapPage(
    IN MMU_VAS *Vas, IN UINT64 VirtualBase,
    IN UINT64 PhysicalBase, IN USHORT Prot)
{
    UINT64 *PageTable;
    UINTN PageTableIndex, PteFlags;

    if (Vas == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    PageTable = MmuPageMapExtract(
        Vas,
        VirtualBase,
        PAGEMAP_PML1,
        TRUE
    );

    if (PageTable == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    PageTableIndex = MmuPageMapIndex(VirtualBase, PAGEMAP_PML1);
    PteFlags = MmuProtToPte(Prot);

    PageTable[PageTableIndex] = PhysicalBase | PteFlags;
    MmuTlbFlushSingle(VirtualBase);
    return EFI_SUCCESS;
}
