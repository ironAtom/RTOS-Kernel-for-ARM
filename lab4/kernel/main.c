/** @file main.c
 *
 * @brief kernel main
 *
 * @author Huacong Cai <hcai@andrew.cmu.edu>
 * @author Qinyu Tong <qtong@andrew.cmu.edu>
 *
 * @date   2014-11-24
 */
 
#include <kernel.h>
#include <task.h>
#include <sched.h>
#include <device.h>
#include <assert.h>
#include <lock.h>

uint32_t global_data;
volatile unsigned tick_counter;
uint32_t old_sp; //save kernel's sp

int kmain(int argc __attribute__((unused)), char** argv  __attribute__((unused)), uint32_t table)
{
	int ret;
	
	//app_startup();
    
    //save uboot api table
    global_data = table;
    
    //initialize
    init_swi();
    init_interrupt();
    init_timer();
    mutex_init();
    dev_init();
    
    //run user program
    ret = enter_user_mode(argc, argv);
    
    //restore
    destroy_swi();
    destroy_interrupt();
    destroy_timer();
    
    return ret;
		
	assert(0);        /* should never get here */
}
