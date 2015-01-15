/** @file read.S
 *
 * @brief read sycall wrapper
 *
 * Author:  Huacong Cai <hcai@andrew.cmu.edu>
 *          Qingyu Tong <qtong@andrew.cmu.edu>
 *
 * Date:    2014-11-08
 */

#include <asm.h>
#include <bits/swi.h>

	.file "read.S"
    
    .extern	errno

FUNC(read)
	swi	READ_SWI	@args already in r0, r1, r2

	cmp	r0, #0		@check return value
	bge	return
	rsb	r0, r0, #0	@r0 = -r0
	ldr	r1, =errno
	str	r0, [r1]	@set errno = r0
	mov	r0, #-1		@return -1

return:
	mov	pc, lr
