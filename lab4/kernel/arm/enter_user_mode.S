/*
 * @ init_user_mode.S: User mode initialize routine
 *
 * @ Author: Huacong Cai <hcai@andrew.cmu.edu>
 *           Qinyu Tong  <qtong@andrew.cmu.edu>
 * @ Date:   2014-11-24
 */

#include <asm.h>
#include <bits/swi.h>
#include <arm/psr.h>
#include <config.h>

#define SWI_BASE 0x900000
#define EXIT_SWI  (SWI_BASE + 1)

	.file	"enter_user_mode.S"

    .extern old_sp

FUNC(enter_user_mode)
    @save state
    stmfd sp!, {r1-r12, lr} @store r1 to r12 and lr

    @save sp
    ldr r2, =old_sp
    str sp, [r2]            @save kernal's sp

    @set cpsr
    mrs r2, cpsr            @load cpsr

    @clear i and mode
    bic r2, r2, #PSR_MODE
    bic r2, r2, #PSR_IRQ

    @set iFt_USER
    orr r2, r2, #PSR_MODE_USR
    orr r2, r2, #PSR_FIQ

    msr cpsr, r2

    @set user stack
    ldr sp, =USR_STACK @set the bottom of user stack

    @loop for copying argv[i]
    mov r2, r0
    add r1, r1, r0, LSL #2

LC1:
    sub r1, r1, #4          @push all addresses of strings reference by argv into stack
    ldr r3, [r1]
    str r3, [sp, #-4]!

    sub r2, r2, #1
    cmp r2, #0
    bgt LC1

    str r0, [sp, #-4]!      @push argc into stack

    @jump to user program
    ldr r2, =USR_START_ADDR
    blx r2                  @jump to user program

    swi EXIT_SWI
    
