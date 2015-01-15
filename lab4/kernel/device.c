/**
 * @file device.c
 *
 * @brief Implements simulated devices.
 *
 * @author Huacong Cai <hcai@andrew.cmu.edu>
 * @author Qinyu Tong <qtong@andrew.cmu.edu>
 *
 * @date   2014-11-24
 */

#include <types.h>
#include <assert.h>

#include <task.h>
#include <sched.h>
#include <device.h>
#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>

/**
 * @brief Fake device maintainence structure.
 * Since our tasks are periodic, we can represent 
 * tasks with logical devices. 
 * These logical devices should be signalled periodically 
 * so that you can instantiate a new job every time period.
 * Devices are signaled by calling dev_update 
 * on every timer interrupt. In dev_update check if it is 
 * time to create a tasks new job. If so, make the task runnable.
 * There is a wait queue for every device which contains the tcbs of
 * all tasks waiting on the device event to occur.
 */

struct dev
{
	tcb_t* sleep_queue;
	unsigned long   next_match;
};
typedef struct dev dev_t;

/* devices will be periodically signaled at the following frequencies */
const unsigned long dev_freq[NUM_DEVICES] = {100, 200, 500, 50};
static dev_t devices[NUM_DEVICES];
volatile bool_e dev_int_on; //turn on/off device interrupts (dev_update)

/**
 * @brief Initialize the sleep queues and match values for all devices.
 */
void dev_init(void)
{
   /* the following line is to get rid of the warning and should not be needed */	
    int i;
    for (i = 0; i < NUM_DEVICES; i++) {
        devices[i].sleep_queue = NULL;
        devices[i].next_match = dev_freq[i];
    }
}


/**
 * @brief Puts a task to sleep on the sleep queue until the next
 * event is signalled for the device.
 *
 * @param dev  Device number.
 */
void dev_wait(unsigned int dev __attribute__((unused)))
{
    tcb_t* cur_tcb;
    
    disable_device_interrupts();
    
    cur_tcb = get_cur_tcb();
    
    //insert current task in sleep queue
    cur_tcb->sleep_queue = devices[dev].sleep_queue;
    devices[dev].sleep_queue = cur_tcb;
    
	enable_device_interrupts();

    dispatch_sleep(); //goto sleep state to wait device
}


/**
 * @brief Signals the occurrence of an event on all applicable devices. 
 * This function should be called on timer interrupts to determine that 
 * the interrupt corresponds to the event frequency of a device. If the 
 * interrupt corresponded to the interrupt frequency of a device, this 
 * function should ensure that the task is made ready to run 
 */
void dev_update(unsigned long millis __attribute__((unused)))
{
    tcb_t* temp_tcb;
    int i;
    
    disable_device_interrupts();
    
    for (i = 0; i < NUM_DEVICES; i++) {
        if (devices[i].next_match <= millis) {  //if frequency match device's frequncy
            devices[i].next_match += dev_freq[i];   //update device's next match
            while (devices[i].sleep_queue != NULL) {
                /*make tasks ready to run*/
                temp_tcb = devices[i].sleep_queue;
                devices[i].sleep_queue = devices[i].sleep_queue->sleep_queue;
                temp_tcb->sleep_queue = NULL;
                runqueue_add(temp_tcb, temp_tcb->cur_prio);
            }
        }
    }
    enable_device_interrupts();
    
    dispatch_save();
    
}

/**
 * @brief clear old device sleep queues.
 */
void dev_clear(void)
{
    int i;
    
    disable_device_interrupts();
    
    for (i = 0; i < NUM_DEVICES; i++) {
        devices[i].sleep_queue = NULL;
    }
    
    enable_device_interrupts();
}

