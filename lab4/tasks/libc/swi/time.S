/** @file time.S
 *
 * @brief time sycall wrapper
 *
 * Author:  Huacong Cai <hcai@andrew.cmu.edu>
 *          Qingyu Tong <qtong@andrew.cmu.edu>
 *
 * Date:    2014-11-08
 */

#include <asm.h>
#include <bits/swi.h>

	.file "time.S"

FUNC(time)
	swi	TIME_SWI    @return value already in r0

return:
	mov	pc, lr
