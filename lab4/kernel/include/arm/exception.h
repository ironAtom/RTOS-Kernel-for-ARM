/**
 * @file exception.h
 *
 * @brief Definitions for ARM exception vectoring.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 *
 * @date 2008-07-23
 */

#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#define EX_RESET        0
#define EX_UD           1
#define EX_SWI          2
#define EX_FABRT        3
#define EX_DABRT        4
#define EX_IRQ          6
#define EX_FIQ          7
#define NUM_EXCEPTIONS  8

#ifndef ASSEMBLER

#include <inline.h>
#include <types.h>
#include <arm/psr.h>

/* Register context. */
struct ex_context
{
	uint32_t r0;
	uint32_t r1;
	uint32_t r2;
	uint32_t r3;
	uint32_t r4;
	uint32_t r5;
	uint32_t r6;
	uint32_t r7;
	uint32_t r8;
	uint32_t r9;
	uint32_t r10;
	uint32_t r11;
	uint32_t r12;
};
typedef struct ex_context ex_context_t;


void init_exception(void);
void destroy_exception(void);
void install_exception_handler(unsigned int exn_num, void (*handler)(void))
	__attribute__((nonnull));

INLINE void enable_interrupts(void)
{
	uint32_t cpsr;
	asm volatile ("mrs %0, cpsr" : "=r" (cpsr));
	cpsr &= ~(PSR_IRQ | PSR_FIQ);
	asm volatile ("msr cpsr_c, %0" : : "r" (cpsr) : "memory", "cc");
}

INLINE void disable_interrupts(void)
{
	uint32_t cpsr;
	asm volatile ("mrs %0, cpsr" : "=r" (cpsr));
	cpsr |= PSR_IRQ | PSR_FIQ;
	asm volatile ("msr cpsr_c, %0" : : "r" (cpsr) : "memory", "cc");
}

#endif /* ASSEMBLER */

#endif /* _EXCEPTION_H_ */
