/**
 * @file  timer.c
 *
 * timer setup:
 * Set ICMR to remove mask on OSMR0 interrupt, then set OSMR0 to first time interval. 
 * After that, set OIER, enable a OSMR0 match to generate an interrupt, then set OSCR to zero.
 *
 * @author Huacong Cai <hcai@andrew.cmu.edu>
 * @author Qinyu Tong <qtong@andrew.cmu.edu>
 *
 * @date   2014-11-24
 */

#include <arm/timer.h>
#include <arm/interrupt.h>
#include <arm/reg.h>
#include <exports.h>
#include <config.h>

extern volatile unsigned tick_counter;

uint32_t icmr;
uint32_t osmr0;

void init_timer(void)
{
    /*save ICMR*/
    icmr = reg_read(INT_ICMR_ADDR);
    
    /*set ICMR to remove mask on OSMR0 interrupt*/
	reg_write(INT_ICMR_ADDR, 1 << INT_OSTMR_0);

	/*ICLR does not need to set since its default is IRQ-enabled*/
	
    /*save OSMR0*/
    osmr0 = reg_read(OSTMR_OSMR_ADDR(0));
	/*set OSMR0 to time interval*/
	reg_write(OSTMR_OSMR_ADDR(0), OSMR_INTERVAL);

	/*set OIER, enable a OSMR0 match to generate an interrupt*/
	reg_set(OSTMR_OIER_ADDR, OSTMR_OIER_E0);

	/*set OSCR to zero*/
	reg_write(OSTMR_OSCR_ADDR, 0);
	
	tick_counter = 0;
}

void destroy_timer(void)
{
    /*restore ICMR*/
    reg_write(INT_ICMR_ADDR, icmr);
    
    /*restore OSMR0*/
    reg_write(OSTMR_OSMR_ADDR(0), osmr0);
    
    /*disable OIER*/
    reg_clear(OSTMR_OIER_ADDR, OSTMR_OIER_E0);
}
