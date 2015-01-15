/** @file time.c
 *
 * @brief Kernel timer based syscall implementations
 *
 * @author Huacong Cai <hcai@andrew.cmu.edu>
 * @author Qinyu Tong <qtong@andrew.cmu.edu>
 * @date   2014-11-24
 */

#include <types.h>
#include <config.h>
#include <bits/errno.h>
#include <arm/timer.h>
#include <syscall.h>
#include <exports.h>

extern volatile unsigned tick_counter;

unsigned long time_syscall(void)
{
    //since return system time is unsigned, the max value is 4,294,967,295
    //the return value will overflow if the system run continuously 16 months
    return tick_counter * OS_TIMER_RESOLUTION;
}



/** 
 * @brief Waits in a tight loop for atleast the given number of milliseconds.
 *
 * @param millis  The number of milliseconds to sleep.
 *
 */
void sleep_syscall(unsigned long millis  __attribute__((unused)))
{
    //end_tick is round up
    unsigned end_tick;
    
    if (millis != 0)
        end_tick = tick_counter + ((millis-1)/OS_TIMER_RESOLUTION + 1);
    else
        return;
    
    while (tick_counter < end_tick);
}
