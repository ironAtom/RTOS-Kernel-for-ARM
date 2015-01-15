/**
 * @file   types.h
 * 
 * @brief  Standard Integer Types and Limits
 *         Corresponds to ANSI C99 stdint.h, stddef.h and limits.h
 *
 * @note   Other standard foo that needs to be defined are defined here.
 */

#ifndef _BITS_TYPES_H_
#define _BITS_TYPES_H_


#ifndef ASSEMBLER

#define offsetof(type, member)  ((size_t)(&(((type *)0)->member)))

typedef unsigned long       size_t;
typedef long                ssize_t;

/* --- Guaranteed length --- */

typedef char                int8_t;
typedef short               int16_t;
typedef int                 int32_t;
typedef long long           int64_t;

typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;

/* --- Pointer length --- */

typedef int32_t             intptr_t;
typedef uint32_t            uintptr_t;

#endif /* ASSEMBLER */

/* --- Sizes --- */

#define UINT8_MAX     0xff
#define UINT16_MAX    0xffff
#define UINT32_MAX    0xffffffff
#define UINT64_MAX    0xffffffffffffffff

#define INT8_MAX      0x7f
#define INT16_MAX     0x7fff
#define INT32_MAX     0x7fffffff
#define INT64_MAX     0x7fffffffffffffff
#define INT8_MIN      (-INT8_MAX -1)
#define INT16_MIN     (-INT16_MAX -1)
#define INT32_MIN     (-INT32_MAX -1)
#define INT64_MIN     (-INT64_MAX -1)

#define SIZE_MAX     UINT32_MAX
#define SSIZE_MAX    INT32_MAX
#define SSIZE_MIN    INT32_MIN

#define CHAR_BIT     8

#define UCHAR_MAX    UINT8_MAX
#define USHRT_MAX    UINT16_MAX
#define UINT_MAX     UINT32_MAX
#define ULONG_MAX    UINT32_MAX
#define ULLONG_MAX   UINT64_MAX

#define SCHAR_MAX    INT8_MAX
#define CHAR_MAX     SCHAR_MAX
#define SHRT_MAX     INT16_MAX
#define INT_MAX      INT32_MAX
#define LONG_MAX     INT32_MAX
#define LLONG_MAX    INT64_MAX
#define SCHAR_MIN    INT8_MIN
#define CHAR_MIN     SCHAR_MIN
#define SHRT_MIN     INT16_MIN
#define INT_MIN      INT32_MIN
#define LONG_MIN     INT32_MIN
#define LLONG_MIN    INT64_MIN


#endif /* _BITS_TYPES_H_ */
