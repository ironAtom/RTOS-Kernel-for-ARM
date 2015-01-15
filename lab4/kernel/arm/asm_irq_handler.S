/** @file asm_irq_handle.S
 *
 * @brief Assembly assistance functions to handle interrupts.
 *
 * We handle interrupts in SVC mode with interrupts disabled.  Hence we perform
 * this elaborate waltz to transplant ourselves onto the svc stack, regardless
 * of the source of the IRQ.
 *
 *@ Author: Huacong Cai <hcai@andrew.cmu.edu>
 *          Qinyu Tong  <qtong@andrew.cmu.edu>
 *
 *@ Date:   Sun, 19 Oct 2014
 */

#include <asm.h>
#include <arm/psr.h>

    .file	"asm_irq_handler.S"

    .extern c_irq_handler

/*
 * Code to take an IRQ.
 */
FUNC(irq_handler)
	/* lr starts off pointing at next instruction + 4 -- fix this. */
	sub      lr, lr, #4

	/* No nesting -- this is a temporary stack. */
	ldr      sp, =irq_stack_hi
	stmfd    sp!, {r0,r1}

	/* Move special regs into r0, r1. */
	mrs      r0, spsr
	mov      r1, lr

	/* Switch to supervisor mode */
	msr      cpsr_c, #(PSR_MODE_SVC | PSR_IRQ)

	/* Diq the spsr_svc because svc-mode (SWI) entry code saves it with IRQ 
	 * disabled.  I feel so dirty doing this.  
	 * We need to diq spsr because we need atomic reload of pc and cpsr
	 * during the return sequence in case we came in from user mode.
	 */
	msr      spsr, r0

	/* Save lr, pop of r0, r1 from irq stack, and then put them all on the 
	 * svc stack along with other caller-save registers.
	 * The stack will look like:
	 * {r0-r3, r8, ip, lr, pc} of source
	 */
	stmfd    sp!, {r1}
	ldr      r1, =irq_stack_lo
	ldm      r1, {r0, r1}
	stmfd    sp!, {r0-r3, r8, ip, lr}

	/* Recover user registers and save */
	mrs      r0, spsr
	stmfd    sp, {r0, sp, lr}^
	add      sp, sp, #-12

	/* Set up r8 correctly with u-boot dispatch table. */
	ldr      ip, =global_data
	ldr      r8, [ip]
	
	/* Call the IRQ handler in C. */
	bl        c_irq_handler
	@mov      r0, sp
	@mov      r1, #128
	@bl       hexdump

	/* Restore registers.  Also restore CPSR. */
	ldmfd    sp, {r0, sp, lr}^
	add      sp, sp, #12
	msr      spsr, r0
	ldmfd    sp!, {r0-r3, r8, ip, lr, pc}^

/*
 * We have exactly one IRQ save area.  This is shared across all tasks.  When an
 * IRQ is taken, this region is used as a temporary area to shuffle values across
 * the the SVC stack.  We don't want a full block IRQ stack, let alone an IRQ stack
 * per task.
 */
	.bss
	ALIGN8
GLOBAL(irq_stack_lo)
	.space 8
GLOBAL(irq_stack_hi)

