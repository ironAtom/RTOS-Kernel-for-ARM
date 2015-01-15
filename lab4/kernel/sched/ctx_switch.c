/** @file ctx_switch.c
 * 
 * @brief C wrappers around assembly context switch routines.
 *
 * @author  Qinyu Tong <qtong@andrew.cmu.edu>
 *          HuaCong Cai <hcai@andrew.cmu.edu>
 *
 * @date    Tue Nov 25 15:23:08 EST 2014
 */
 

#include <types.h>
#include <assert.h>

#include <config.h>
#include <kernel.h>
#include <device.h>
#include "sched_i.h"

#ifdef DEBUG_MUTEX
#include <exports.h>
#endif

static __attribute__((unused)) tcb_t* cur_tcb; /* use this if needed */

/**
 * @brief Initialize the current TCB and priority.
 *
 * Set the initialization thread's priority to IDLE so that anything
 * will preempt it when dispatching the first task.
 */
void dispatch_init(tcb_t* idle __attribute__((unused)))
{
    disable_device_interrupts();
    cur_tcb = idle;
    enable_device_interrupts();
}


/**
 * @brief Context switch to the highest priority task while saving off the 
 * current task state.
 *
 * This function needs to be externally synchronized.
 * We could be switching from the idle task.  The priority searcher has been tuned
 * to return IDLE_PRIO for a completely empty run_queue case.
 */
void dispatch_save(void)
{
    tcb_t* targ_tcb;
    sched_context_t* cur_ctx;
    sched_context_t* targ_ctx;
    
    disable_device_interrupts(); //before modify kernel data structure, disable interrupt, becasue kernel is preemptive
    
    runqueue_add(cur_tcb, cur_tcb->cur_prio);   //add current task to run queue
    targ_tcb = runqueue_remove(highest_prio()); //get the highest priority task in run queue
    
    if (targ_tcb == cur_tcb){   //if target task already is current task, don't need to change context
		enable_device_interrupts();	
        return;
    }
    
    cur_ctx = &(cur_tcb->context);  //get current context
    targ_ctx = &(targ_tcb->context);    //get target context address
    
    cur_tcb = targ_tcb; //change cur_tcb to targ_tcb

	enable_device_interrupts();	

    ctx_switch_full(targ_ctx, cur_ctx); //context switch from current to target
    
    //enable_device_interrupts(); // this enable is executed by newly runned target task
}

/**
 * @brief Context switch to the highest priority task that is not this task -- 
 * don't save the current task state.
 *
 * There is always an idle task to switch to.
 */
void dispatch_nosave(void)
{
    tcb_t* targ_tcb;
    sched_context_t* targ_ctx;
    
    disable_device_interrupts();

    targ_tcb = runqueue_remove(highest_prio()); //get the highest priority task in run queue
    targ_ctx = &(targ_tcb->context);    //get target context address
    cur_tcb = targ_tcb;

	enable_device_interrupts();

    ctx_switch_half(targ_ctx);
 
    //enable_device_interrupts();

}


/**
 * @brief Context switch to the highest priority task that is not this task -- 
 * and save the current task but don't mark is runnable.
 *
 * There is always an idle task to switch to.
 */
void dispatch_sleep(void)
{
    tcb_t* targ_tcb;
    sched_context_t* cur_ctx;
    sched_context_t* targ_ctx;
    
    disable_device_interrupts();
    
    targ_tcb = runqueue_remove(highest_prio()); //get the highest priority task in run queue
    
 	targ_ctx = &(targ_tcb->context);    //get target context address
    cur_ctx = &(cur_tcb->context);  //get current context
   
	
    cur_tcb = targ_tcb; //change cur_tcb to targ_tcb

	enable_device_interrupts();

    ctx_switch_full(targ_ctx, cur_ctx); //context switch from current to target
    //enable_device_interrupts();
}

/**
 * @brief Returns the priority value of the current task.
 */
uint8_t get_cur_prio(void)
{
	return cur_tcb->cur_prio;
}

/**
 * @brief Returns the TCB of the current task.
 */
tcb_t* get_cur_tcb(void)
{
	return cur_tcb;
}
