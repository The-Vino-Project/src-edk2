/*
 * Copyright (c) 2026, pinrip, rixel, et al.
 *
 * Abstract:
 *      Defines basic NT definitions
 * Author:
 *    Chloe Pinrip
 */

#ifndef _SDK_NTDEF_H_
#define _SDK_NTDEF_H_ 1

/*
 * Paramater decorators
 */

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef OPTIONAL
#define OPTIONAL
#endif

/*
 * Keyword aliases
 */

#define CONST  const

/*
 * Basic types
 */

#if defined(_NT_TYPES)
/* Basic types */
typedef void VOID;
typedef _Bool BOOLEAN;

/* Basic signed types */
typedef char CHAR;
typedef short SHORT;
typedef int LONG;
typedef long long LONGLONG;
typedef LONGLONG SSIZE;

/* Basic unsigned types */
typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef unsigned int ULONG;
typedef unsigned long long ULONGLONG;
typedef ULONGLONG USIZE;
typedef ULONGLONG UPTR;

/* Basic pointer types */
typedef VOID      *PVOID;
typedef CHAR      *PCHAR;
typedef SHORT     *PSHORT;
typedef LONG      *PLONG;
typedef LONGLONG  *PLONGLONG;
typedef UCHAR     *PUCHAR;
typedef USHORT    *PUSHORT;
typedef ULONG     *PULONG;
typedef ULONGLONG *PULONGLONG;
typedef LOGICAL   *PLOGICAL;
typedef BOOLEAN   *PBOOLEAN;
#endif  /* !_NT_TYPES */

/*
 * Convenience macros
 */

/* Pointer offset macros */
#define PTR_OFFSET(p, off) ((PVOID)(PCHAR)(p) + (off))
#define PTR_NOFFSET(p, off) ((PVOID)(PCHAR)(p) - (off))

/* Bit related macros */
#define BIT(n) (1ULL << (n))
#define ISSET(v, f)  ((v) & (f))

/* Align up/down a value */
#define ALIGN_DOWN(value, align)      ((value) & ~((align)-1))
#define ALIGN_UP(value, align)        (((value) + (align)-1) & ~((align)-1))

/* Bitmap helper macros */
#define SETBIT(a, b) ((a)[(b) >> 3] |= BIT(b % 8))
#define CLRBIT(a, b) ((a)[(b) >> 3] &= ~BIT(b % 8))
#define TESTBIT(a, b) (ISSET((a)[(b) >> 3], BIT(b % 8)))

/* Min/max macros */
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

/* Get number of array elements */
#define NELEM(a) (sizeof(a) / sizeof(a[0]))

#endif  /* !_SDK_NTDEF_H_ */
