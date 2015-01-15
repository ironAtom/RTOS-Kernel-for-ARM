/**
 * @file asm.h
 *
 * @brief Common macros for asm routines.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 */

#ifndef _ASM_H_
#define _ASM_H_

#define ARG0    r0
#define ARG1    r1
#define ARG2    r2
#define ARG3    r3

#define ARG4    [sp, #0]
#define ARG5    [sp, #4]
#define ARG6    [sp, #8]
#define ARG7    [sp, #8]


#define ALIGN        .align 2
#define ALIGN8       .align 3
#define GLOBAL(x)    .global x; x ## :

#define FUNCSYM(x)   .type    x,%function
#define DATASYM(x)   .type    x,%object
#define SIZE(x,s)    .size    x, s

#define FUNC(x)      .text ; ALIGN ; FUNCSYM(x) ; GLOBAL(x)
#define	DATA(x,s)    .data ; ALIGN ; DATASYM(x) ; SIZE(x,s) ; GLOBAL(x)

#define BSS_WORD32(x)    .comm x, 4, 4

#define CRASH(x, r)  ldr r, =x; ldr r, [r];

#endif /* _ASM_H_ */
