/**
 * @file psr.h
 *
 * @brief Definitions for ARM program state registers (CPSR and SPSRs).
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 *
 * @date 2008-08-13
 */

#ifndef _PSR_H_
#define _PSR_H_

#define PSR_NEG        0x80000000
#define PSR_ZERO       0x40000000
#define PSR_CARRY      0x20000000
#define PSR_OFLW       0x10000000
#define PSR_IRQ        0x00000080
#define PSR_FIQ        0x00000040
#define PSR_MODE       0x0000001f

#define PSR_MODE_USR   0x10
#define PSR_MODE_FIQ   0x11
#define PSR_MODE_IRQ   0x12
#define PSR_MODE_SVC   0x13
#define PSR_MODE_ABT   0x17
#define PSR_MODE_UND   0x1b
#define PSR_MODE_SYS   0x1b

#ifndef ASSEMBLER

#include <inline.h>

INLINE uint32_t read_cpsr(void)
{
	uint32_t cpsr;
	asm volatile ("mrs %0, cpsr" : "=r" (cpsr));
	return cpsr;
}

#endif /* ASSEMBLER */
#endif /* _EXCEPTION_H_ */
