/* @ swi_handler.S: SWI handler routine
 *
 * it first store registers and spsr and enable irq.
 * Then call c_swi_handler. After c_swi_handler returns, restores registers and spsr.
 *
 * @ Author: Huacong Cai <hcai@andrew.cmu.edu>
 *           Qinyu Tong  <qtong@andrew.cmu.edu>
 *
 * Date:     2014-11-24
 */

#include <asm.h>
#include <arm/psr.h>

	.file	"swi_handler.S"
    
    .extern global_data
    .extern swi_dispatch
    
FUNC(swi_handler)        
	sub  sp, sp, #4         @leave room on stack for SPSR
	stmfd sp!, {r0-r12, lr} @store user's gpregisters
	
	mrs r2, spsr            @get SPSR into gpregisters
	str r2, [sp, #14*4]     @store SPSR above gpregisters

    stmfd sp, {sp, lr}^
    add sp, sp, #-8

	@enable irq as soon as possible
   	mrs r2, cpsr
    bic r2, r2, #PSR_IRQ
    msr cpsr, r2

	add r1, sp, #8          @pointer to parameters on stack
	ldr r0, [lr, #-4]       @extract the SWI number
	bic r0, r0, #0xff000000 @get SWI # by bit-masking

    @restore r8
    ldr r2, =global_data
    ldr r8, [r2]

	bl swi_dispatch         @goto handler

    ldmfd sp, {sp, lr}^
    add sp, sp, #8
    
	ldr r2, [sp, #14*4]     @restore SPSR
	msr spsr, r2            @restore SPSR from r2
	ldmfd sp!, {r0-r12, lr} @unstackuser's registers
	add sp, sp, #4          @remove space used to store SPSR
	
	movs pc, lr             @return from handler
