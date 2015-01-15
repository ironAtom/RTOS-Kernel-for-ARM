/**
 * @file  swi.c
 *
 * @brief swi related routines
 *
 * @author Huacong Cai <hcai@andrew.cmu.edu>
 * @author Qinyu Tong <qtong@andrew.cmu.edu>
 *
 * @date   2014-11-24
 */

#include <arm/swi.h>
#include <bits/swi.h>
#include <syscall.h>
#include <exports.h>
#include <lock.h>

#include "arm_i.h"

#define SWI_VEC 0x08

uint32_t old_swi_instruction1;
uint32_t old_swi_instruction2;
uint32_t *old_swi_location;

void swi_exit(int status);

void init_swi(void)
{
    install_handler(SWI_VEC, (uint32_t *)&swi_handler, &old_swi_location,
                    &old_swi_instruction1, &old_swi_instruction2);
}

void destroy_swi(void)
{
    //restore swi
    restore_handler(old_swi_location, old_swi_instruction1, old_swi_instruction2);
}

//Handle swi according to swi number
void swi_dispatch(unsigned swi_num, struct ex_context* regs)
{
    switch (swi_num)
    {
        case READ_SWI:
            (regs->r0) = read_syscall((int)(regs->r0), (char *)(regs->r1), (size_t)(regs->r2));
            break;
            
        case WRITE_SWI:
            (regs->r0) = write_syscall((int)(regs->r0), (const char *)(regs->r1), (size_t)(regs->r2));
            break;
            
        case TIME_SWI:
            (regs->r0) = time_syscall();
            break;
            
        case SLEEP_SWI:
            sleep_syscall((unsigned long)(regs->r0));
            break;
            
        case CREATE_SWI:
            (regs->r0) = task_create((task_t*)(regs->r0), (size_t)(regs->r1));
            break;
            
        case MUTEX_CREATE:
            (regs->r0) = mutex_create();
            break;
            
        case MUTEX_LOCK:
            (regs->r0) = mutex_lock((int)(regs->r0));
            break;
            
        case MUTEX_UNLOCK:
            (regs->r0) = mutex_unlock((int)(regs->r0));
            break;
            
        case EVENT_WAIT:
            (regs->r0) = event_wait((unsigned)(regs->r0));
            break;
            
        default:
            printf("SWI number is unrecognized\n");
            invalid_syscall(swi_num);
            break;
    }
}

