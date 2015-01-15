/** @file proc.c
 * 
 * @brief Implementation of `process' syscalls
 *
 * @author Huacong Cai <hcai@andrew.cmu.edu>
 * @author Qinyu Tong <qtong@andrew.cmu.edu>
 * @date   2014-11-24
 */

#include <exports.h>
#include <bits/errno.h>
#include <config.h>
#include <kernel.h>
#include <syscall.h>
#include <sched.h>

#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/physmem.h>
#include <device.h>

/**
 * @ task create takes a set of tasks, verifies that they are schedulable,
 *   and then begins to schedule them.
 * @ Argument tasks: An array of task descriptors that qualify the tasks to create
 *   Argument num_tasks: The number of elements in the array.
 * @ return value: Upon success, this function does not return, error number returned
 *   when failed.
 **/
int task_create(task_t* tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{
    task_t tmp_tcb;
    unsigned int i, j;
    if (num_tasks > OS_MAX_TASKS) {
        return -EINVAL;
    }
    
    if (!valid_addr(tasks, num_tasks, USR_START_ADDR, USR_END_ADDR)) {
        return -EFAULT;
    }
    
    for (i = 0; i< num_tasks; i++) {
        if (tasks[i].C > tasks[i].T) {
            return -ESCHED;
        }
    }

    /*sort tasks*/
    for (i = 0; i < num_tasks; i++) {
        for (j = i+1; j < num_tasks; j++) {
            if (tasks[i].T > tasks[j].T) {
                tmp_tcb = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = tmp_tcb;
            }
        }
    }
    
    dev_clear(); //clear old device sleep queue
    allocate_tasks(&tasks,num_tasks);
    sched_init(NULL);
    return 0; //to avoid warning
}

/**
 * @ wait next event is singnalled for the device
 * @ param dev Device number. A valid device number – 0, 1, 2 or 3.
 * @ returnReturn int
 *     A zero is returned upon the successful acquisition of the mutex. Upon failure,
 *an error code may be returned.
 *  EINVAL The provided device identifier is invalid.
 */
int event_wait(unsigned int dev  __attribute__((unused)))
{
    if (dev > NUM_DEVICES - 1) { // invalid device number
        return -EINVAL;
    }
    
    dev_wait(dev);
    return 0;
}


/* An invalid syscall causes the kernel to exit. */
void invalid_syscall(unsigned int call_num  __attribute__((unused)))
{
	printf("Kernel panic: invalid syscall -- 0x%08x\n", call_num);

	disable_interrupts();
	while(1);
}
