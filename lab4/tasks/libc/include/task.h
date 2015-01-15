/** @file task.h
 *
 * @brief Declares task creation interface
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date   2008-11-21
 */

#ifndef TASK_H
#define TASK_H

#include <bits/types.h>

/**
 * A task takes an arbitrary parameter and begins execution.
 * Task function are not allowed to exit or crash under any circumstance.
 */
typedef void (*task_fun_t)(void*);

struct task
{
	task_fun_t    lambda;      /**< The root function of this task */
	void*         data;        /**< Argument to the root function */
	void*         stack_pos;   /**< The starting position of the task's sp */
	unsigned long C;           /**< The worst-case computation time */
	unsigned long T;           /**< The task's period */
};
typedef struct task task_t;


int task_create(task_t* tasks, size_t num_tasks);


#endif /* TASK_H */
