/**
 * @file  interrupt.c
 *
 * @brief interrupt related routines
 *
 * @author Huacong Cai <hcai@andrew.cmu.edu>
 * @author Qinyu Tong <qtong@andrew.cmu.edu>
 *
 * @date   2014-11-24
 */

#include <arm/exception.h>
#include <arm/interrupt.h>
#include <arm/reg.h>
#include <arm/timer.h>
#include <config.h>
#include <device.h>
#include <types.h>

#include "arm_i.h"

#define IRQ_VEC 0x18

uint32_t old_irq_instruction1;
uint32_t old_irq_instruction2;
uint32_t *old_irq_location;

extern volatile unsigned tick_counter;

void init_interrupt(void)
{

    install_handler(IRQ_VEC, (uint32_t *)&irq_handler, &old_irq_location,
                    &old_irq_instruction1, &old_irq_instruction2);
    
    dev_int_on = TRUE; //turn on device interrupts
}

void destroy_interrupt(void)
{
    //disable interrupt
    disable_interrupts();
    
    //restore irq handler
    restore_handler(old_irq_location, old_irq_instruction1, old_irq_instruction2);
}

void c_irq_handler (void)
{
    volatile unsigned int osmr;
    
    /*increase the tick counter*/
    tick_counter++;
    
    if (dev_int_on == TRUE) {
        dev_update(tick_counter * OS_TIMER_RESOLUTION);
    }
    
    /*increase OSMR a time interval*/
    osmr = reg_read(OSTMR_OSMR_ADDR(0));
    osmr += OSMR_INTERVAL;
    reg_write(OSTMR_OSMR_ADDR(0), osmr);
    
    reg_set(OSTMR_OSSR_ADDR, OSTMR_OSSR_M0); /*acknowledge IRQ*/
}
