/** @file sleep.S
 *
 * @brief sleep sycall wrapper
 *
 * Author:  Huacong Cai <hcai@andrew.cmu.edu>
 *          Qingyu Tong <qtong@andrew.cmu.edu>
 *
 * Date:    2014-11-08
 */

#include <asm.h>
#include <bits/swi.h>

	.file "sleep.S"

FUNC(sleep)
	swi	SLEEP_SWI    @args already in r0

return:
	mov	pc, lr
