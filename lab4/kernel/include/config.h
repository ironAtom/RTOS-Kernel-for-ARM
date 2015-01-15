/** @file config.h
 *
 * @brief A set of common OS configuration flags.  This is to control overall
 * OS behavior and not behavior of a particular modules.
 *
 * @author Huacong Cai <hcai@andrew.cmu.edu>
 * @author Qinyu Tong <qtong@andrew.cmu.edu>
 * @date   2014-11-24
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

#define OS_TICKS_PER_SEC        100    /* Set the number of ticks in one second */
#define OS_TIMER_RESOLUTION     (1000/OS_TICKS_PER_SEC)  /* Timer resolution in ms */
#define OSMR_INTERVAL           (3250000/OS_TICKS_PER_SEC) /* Value of OSMR increases every tick */

#define LOAD_ADDR  0xa0000000
#define USR_STACK  0xa3000000

#define USR_START_ADDR        0xa0000000
#define USR_END_ADDR          0xa3000000

#define OS_KSTACK_SIZE        4096
#define OS_USTACK_ALIGN       1024
#define OS_IRQ_STACK_SIZE     128

/* OS_MAX_TASKS must be atleast 8 and must be atmost 64 */
#define IDLE_PRIO             63
#define OS_MAX_TASKS          64
#define OS_AVAIL_TASKS        63

/* OS_NUM_MUTEX must be at lease 32 */
#define OS_NUM_MUTEX	32

#endif /* _CONFIG_H_ */
