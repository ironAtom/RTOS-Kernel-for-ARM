/** @file sched.c
 * 
 * @brief Top level implementation of the scheduler.
 *
 * @author  Qinyu Tong <qtong@andrew.cmu.edu>
 *          HuaCong Cai <hcai@andrew.cmu.edu>
 *
 * @date    Tue Nov 25 15:23:08 EST 2014
 */

#include <types.h>
#include <assert.h>

#include <kernel.h>
#include <config.h>
#include <device.h>
#include "sched_i.h"

#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/physmem.h>
#include <exports.h>

tcb_t system_tcb[OS_MAX_TASKS]; /*allocate memory for system TCBs */

void sched_init(task_t* main_task  __attribute__((unused)))
{
    dispatch_nosave();
}

/**
 * @brief This is the idle task that the system runs when no other task is runnable
 */
 
static void __attribute__((unused)) idle(void)
{
	enable_interrupts();
	while(1);
}

/**
 * @brief Allocate user-stacks and initializes the kernel contexts of the
 * given threads.
 *
 * This function assumes that:
 * - num_tasks < number of tasks allowed on the system.
 * - the tasks have already been deemed schedulable and have been appropriately
 *   scheduled.  In particular, this means that the task list is sorted in order
 *   of priority -- higher priority tasks come first.
 *
 * @param tasks  A list of scheduled task descriptors.
 * @param size   The number of tasks is the list.
 */
void allocate_tasks(task_t** tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{
    unsigned i;
    disable_device_interrupts();
    
    runqueue_init();
    
    for (i = 1; i <= num_tasks; i++){ //i=0 reserve for the special priority task
        system_tcb[i].native_prio = i;
        system_tcb[i].cur_prio = i;
        system_tcb[i].context.r4 = (uint32_t)(*tasks)[i-1].lambda; //task entry point
        system_tcb[i].context.r5 = (uint32_t)(*tasks)[i-1].data;
        system_tcb[i].context.r6 = (uint32_t)(*tasks)[i-1].stack_pos; //user_mode stack
        system_tcb[i].context.r8 = global_data;
        system_tcb[i].context.sp = (void *)system_tcb[i].kstack_high; //swi supervisor mode stack
        system_tcb[i].context.lr = (void *)launch_task;
        
        system_tcb[i].holds_lock = 0;
        system_tcb[i].sleep_queue = NULL;
        
        runqueue_add(&(system_tcb[i]), i); //add to run queue
    }
    //allocate idle task
    system_tcb[IDLE_PRIO].native_prio = IDLE_PRIO;
    system_tcb[IDLE_PRIO].cur_prio = IDLE_PRIO;
    
    system_tcb[IDLE_PRIO].context.r4 = (uint32_t)idle; //task entry point
    system_tcb[IDLE_PRIO].context.r5 = 0;
    system_tcb[IDLE_PRIO].context.r6 = (uint32_t)system_tcb[IDLE_PRIO].kstack_high;
    system_tcb[IDLE_PRIO].context.r8 = global_data;
    system_tcb[IDLE_PRIO].context.sp = (void *)system_tcb[IDLE_PRIO].kstack_high;
    system_tcb[IDLE_PRIO].context.lr = (void *)launch_task;
    
    system_tcb[IDLE_PRIO].holds_lock = 0;
    system_tcb[IDLE_PRIO].sleep_queue = NULL;
    
    runqueue_add(&(system_tcb[IDLE_PRIO]), IDLE_PRIO);
	
    enable_device_interrupts();
}

