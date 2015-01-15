/** @file task.h
 *
 * @brief Declares task maintainence structures.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date   2008-11-19
 */

#ifndef TASK_H
#define TASK_H

#include <types.h>
#include <config.h>

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


/**
 * Register context for the scheduler.
 *
 * No caller saved registers are present.  Scratch register is not present.
 */
struct sched_context
{
	uint32_t r4;
	uint32_t r5;
	uint32_t r6;
	uint32_t r7;
	uint32_t r8;
	uint32_t r9;
	uint32_t r10;
	uint32_t r11;
	void*    sp;
	void*    lr;
};
typedef volatile struct sched_context sched_context_t;


struct tcb
{
	uint8_t          native_prio;        /**< The native priority of the task without escalation */
	uint8_t          cur_prio;           /**< The current priority of the task after priority inheritance */
	sched_context_t  context;            /**< The task's serialized context -- if not running */
	int              holds_lock;         /**< 1 if the task is currently owning a lock */
	volatile struct tcb* sleep_queue;    /**< If this task is asleep, this is its sleep queue link */
	/** Embed the kernel stack here -- AAPCS wants 8 byte alignment */
	uint32_t         kstack[OS_KSTACK_SIZE/sizeof(uint32_t)] 
	                     __attribute__((aligned(8)));
	uint32_t         kstack_high[0];
};
typedef volatile struct tcb tcb_t;


#endif /* TASK_H */
