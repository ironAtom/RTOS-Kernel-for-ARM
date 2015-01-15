/** @file crt0.S
 *
 * @brief Execution startup routine
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 07 Oct 2007 01:51:29 -0400
 */

#include <asm.h>

	.file "crt0.S"

FUNC(_start)
	ldr	r0, [sp]		@argc
	add r1, sp, #4		@argv

	bl	main			@call main

L1:
    b   L1              @dead loop

