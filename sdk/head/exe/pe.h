/*
 * Copyright (c) 2026, pinrip, rixel, et al.
 *
 * Abstract:
 *      PE executable format defs
 * Author:
 *      Chloe Pinrip
 */

#ifndef _EXE_PE_H_
#define _EXE_PE_H_ 1

#include <ntdef.h>

/*
 * Describes the portable executable header
 */
typedef struct {
    ULONG Magic;
    USHORT Machine;
    USHORT NumberOfSections;
    ULONG TimeDateStamp;
    ULONG PointerToSymbolTable;
    ULONG NumberOfSymbols;
    USHORT SizeOfOptionalHeader;
    USHORT Characteristics;
} PE32_HEADER, *PPE32_HEADER;

/*
 * Describes the portable executable optional header
 */
typedef struct {
    USHORT Magic;
    UCHAR MajorLinkerVersion;
    UCHAR MinorLinkerVersion;
    ULONG SizeOfCode;
    ULONG SizeOfInitializedData;
    ULONG SizeOfUninitializedData;
    ULONG BaseOfCode;
    ULONGLONG ImageBase;
    ULONG SectionAlignment;
    ULONG FileAlignment;
    USHORT MajorOperatingSystemVersion;
    USHORT MinorOperatingSystemVersion;
    USHORT MajorImageVersion;
    USHORT MinorImageVersion;
    USHORT MajorSubsystemVersion;
    USHORT MinorSubsystemVersion;
    ULONG Win32VersionValue;
    ULONG SizeOfImage;
    ULONG SizeOfHeaders;
    ULONG CheckSum;
    USHORT Subsystem;
    USHORT DllCharacteristics;
    ULONGLONG SizeOfStackReserve;
    ULONGLONG SizeOfStackCommit;
    ULONGLONG SizeOfHeapReserve;
    ULONGLONG SizeOfHeapCommit;
    ULONG LoaderFlags;
    ULONG NumberOfRvaAndSizes;
} PE32P_OPT_HEADER, *PPE32P_OPT_HEADER;

/* "PE\0\0" */
#define PE_HEADER_MAGIC 0x00004550

/* PE32+ optional header magic */
#define PE_OHEADER_MAGIC 0x020B

#endif  /* !_EXE_PE_H_ */
