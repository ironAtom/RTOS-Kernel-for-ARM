/**
 * @file mutex.c
 *
 * @brief Implements mutices.
 *
 * @author  Qinyu Tong <qtong@andrew.cmu.edu>
 *          HuaCong Cai <hcai@andrew.cmu.edu>
 * 
 * @date    Tue Nov 25 15:23:08 EST 2014
 */

//#define DEBUG_MUTEX

#include <lock.h>
#include <task.h>
#include <sched.h>
#include <bits/errno.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <device.h>
#ifdef DEBUG_MUTEX
#include <exports.h> // temp
#endif

mutex_t gtMutex[OS_NUM_MUTEX];

void mutex_init()
{
    int i;
    for (i = 0 ; i < OS_NUM_MUTEX; i++) {
        gtMutex[i].bAvailable = TRUE;
        gtMutex[i].pHolding_Tcb = NULL;
        gtMutex[i].bLock = FALSE;
        gtMutex[i].pSleep_queue = NULL;
    }
}

int mutex_create(void) //find the first avaliable mutex, then return.
{
    int i;
    disable_device_interrupts();
    
    for (i = 0 ; i < OS_NUM_MUTEX; i++) {
        if (gtMutex[i].bAvailable) {
            gtMutex[i].bAvailable = FALSE;
            enable_device_interrupts();
            return i;
        }
    }
    
    if (i == OS_NUM_MUTEX) {    //no availiable mutex, return -ENOMEM to indicate error
        enable_device_interrupts();
        return -ENOMEM;
    }
    return -ENOMEM;
}

int mutex_lock(int mutex  __attribute__((unused)))
{
    tcb_t* pSleep_tcb;
    tcb_t* cur_tcb;
    mutex_t* pMutex;
    
    disable_device_interrupts();
    
    if (mutex < 0 || mutex > OS_NUM_MUTEX - 1) { //invalid mutex id
        enable_device_interrupts();
        return -EINVAL;
    }
    
    pMutex = &gtMutex[mutex]; //using local variable to avoid unnecessary reference gtMutex[mutex]
    
    if(pMutex->bAvailable){ // mutex has not been created yet
        enable_device_interrupts();
        return -EINVAL;
    }
    
    cur_tcb = get_cur_tcb(); //get current tcb
    
    if (pMutex->pHolding_Tcb == cur_tcb) {//current task already hold the mutex
        enable_device_interrupts();
        return -EDEADLOCK;
    }
 
    if (pMutex->bLock) { //the mutex has been hold by other task
        
        pSleep_tcb = pMutex->pSleep_queue;
        if (pSleep_tcb == NULL) { //sleep queue empty, the tcb became the first node of sleep queue
            pMutex->pSleep_queue = cur_tcb;
            cur_tcb->sleep_queue = NULL;    //Doesn't actually needed, just incase
        }
        else{ //sleep queue not empty, append cur_tcb to the queue
            while (pSleep_tcb->sleep_queue != NULL){ // find the last node in the queue
                pSleep_tcb = pSleep_tcb->sleep_queue;
            }
            
            pSleep_tcb->sleep_queue = cur_tcb;
            cur_tcb->sleep_queue = NULL; //doesn't actually needed
        }
		enable_device_interrupts();
        dispatch_sleep(); //can't acquire lock, go to sleep
    }
    else{ //mutex is free
        pMutex->pHolding_Tcb = cur_tcb;
        pMutex->bLock = TRUE;
        pMutex->pSleep_queue = NULL;
		enable_device_interrupts();
    }
    
    return 0;
}

int mutex_unlock(int mutex  __attribute__((unused)))
{
    tcb_t* pSleep_tcb;
    tcb_t* cur_tcb;
    mutex_t* pMutex;
    
    disable_device_interrupts();
    cur_tcb = get_cur_tcb();
    
    if (mutex < 0 || mutex > OS_NUM_MUTEX - 1) { //invalid mutex id
        enable_device_interrupts();
        return -EINVAL;
    }
    
    pMutex = &gtMutex[mutex]; //using local variable to avoid unnessary reference gtMutex[mutex]
    
    if(pMutex->bAvailable){ // mutex has not been created yet
        enable_device_interrupts();
        return -EINVAL;
    }
    
    if ( pMutex->pHolding_Tcb != cur_tcb ) {//current task does not hold the mutex
        enable_device_interrupts();
        return -EPERM;
    }
    
    if (pMutex->pSleep_queue == NULL) { //no task wait for this mutex, release the lock
        pMutex->pHolding_Tcb = NULL;
        pMutex->bLock = FALSE;
    }
    else{ //wake first waiting task, handed over mutex to first waiting task
        //remove the first sleep task from queue
        pSleep_tcb = pMutex->pSleep_queue;
        pMutex->pHolding_Tcb = pSleep_tcb;
        pMutex->pSleep_queue = pSleep_tcb->sleep_queue; //Mutex's sleep queue point to next sleep task;
        pSleep_tcb->sleep_queue = NULL; //clear sleep queue of the first waiting task
        
        runqueue_add(pSleep_tcb,pSleep_tcb->cur_prio);
    }
    
    enable_device_interrupts();
    
    dispatch_save(); //maybe the waiting task has the highest priority
    
    return 0;
}

