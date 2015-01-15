/** @file sched_i.h
 * 
 * @brief Internal header -- runqueue and tcb maintainence routines.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-21
 */

#ifndef _SCHED_I_H_
#define _SCHED_I_H_

#include <sched.h>


void dispatch_init(tcb_t* idle);
void runqueue_init(void);

void ctx_switch_full(volatile void* next_ctx, volatile void* cur_ctx);
void ctx_switch_half(volatile void* next_ctx) __attribute__((noreturn));

/** A list of every TCB+kernel stack that can exist on this system.
 * Note -- this list is not ordered by anything.
 */
extern tcb_t system_tcb[OS_MAX_TASKS];

#endif /* _SCHED_I_H_ */
