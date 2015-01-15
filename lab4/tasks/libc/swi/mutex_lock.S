/** @file mutex_lock.S
 *
 * @brief acquire mutex sycall wrapper
 * 
 * @author  Qinyu Tong <qtong@andrew.cmu.edu>
 *          HuaCong Cai <hcai@andrew.cmu.edu>
 * 
 * @date    Tue Nov 25 15:23:08 EST 2014
 */

#include <asm.h>
#include <bits/swi.h>
	.file "mutex_lock.S"

FUNC(mutex_lock)
    swi MUTEX_LOCK

    cmp r0, #0
    bge	return
    rsb	r0, r0, #0	@r0 = -r0
    ldr	r1, =errno
	str	r0, [r1]	@set errno = r0
	mov	r0, #-1		@return -1

return:
	mov	pc, lr
