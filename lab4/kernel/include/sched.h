/** @file sched.h
 *
 * @brief Declares core scheduler and task management routines.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date   2008-11-21
 */

#ifndef SCHED_H
#define SCHED_H

#include <task.h>
#include <types.h>

void sched_init(task_t* main_task);

/* Scheduler invocations */
void dispatch_save(void);
void dispatch_nosave(void);
void dispatch_sleep(void);

/* Entry assist */
void launch_task(void); /* takes lambda and argument in r4, r5 */

/* Task initialization */
void allocate_tasks(task_t** tasks, size_t num_tasks);
int assign_schedule(task_t** tasks, size_t num_tasks);

/* Current task state */
uint8_t get_cur_prio(void);
tcb_t* get_cur_tcb(void);

/* Run-queue/priority management */
void runqueue_add(tcb_t* tcb, uint8_t prio);
tcb_t* runqueue_remove(uint8_t prio);
uint8_t highest_prio(void);

#endif /* SCHED_H */
