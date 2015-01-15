/** @file mutex_chaser.c
 *
 * @brief A test to aggresively acquire/release the maximum number of mutexes.
 * Each mutex has a corresponding number and each task performs a certain operation on a mutex's 
 * number after it acquires a lock on it. After each task has acquire/release a mutex, simple 
 * check if the number is consistent with the correct value.  
 * The mutex they are implementing is more like a conditional variable that has a FIFO sleep queue.
 *
 * Purpose of the test:
 * 1.Ensure mutex is releasing task in FCFS order.
 * 2.Make sure rate monotonic scheduling is preserved.
 *
 *
 * @author Kevin Chang(kevincha)
 * @data 2010-12-01
 **/ 
#include <stdio.h>
#include <unistd.h>
#include <task.h>
#include <lock.h>
#include <bits/errno.h>
#include <errno.h>

#define MUTEX_NUM 32
#define YES_STR "\033[32;1mYes!\033[0m\n"
#define NO_STR  "\033[31;1mNo!\033[0m\n"
#define TEST_DONE "\033[32;1mTEST PASSED SUCCESSFULLY!\033[0m\n"

//order of operations: ((init_val+3)*11-7)*13=61
static int fun1_opval=3;
static int fun2_opval=11;
static int fun3_opval=7;
static int fun4_opval=13;
static int init_val=2;
static int result_val=0;

int mutex_val[MUTEX_NUM];

void panic(const char* str)
{
	puts(str);
	while(1);
}
//dev3
void fun1(void* str)
{
    int cur_mutex=1;
 	str = str;   
	while(cur_mutex<MUTEX_NUM){
        putchar((int)str);
        printf(">>mutex %d\n",cur_mutex);
		if(mutex_lock(cur_mutex))
            panic("Failed to acquire mutex");
	    mutex_val[cur_mutex]=mutex_val[cur_mutex]+fun1_opval;	
		if(mutex_unlock(cur_mutex))
        {
            if(errno==EINVAL)
                puts("EINVAL");
            if(errno==EPERM)
                puts("EPERM");
            panic("Failed to release mutex");
        }
        cur_mutex++;
        if (event_wait(3) < 0)
            panic("Dev 3 failed");
	}
    while(1)
        if (event_wait(3) < 0)
            panic("Dev 3 failed");
}
//dev0
void fun2(void* str)
{
    int cur_mutex=1;
    
 	str = str;   
	while(cur_mutex<MUTEX_NUM){
        putchar((int)str);
        printf(">>mutex %d\n",cur_mutex);
		if(mutex_lock(cur_mutex))
            panic("Failed to acquire mutex");
	    mutex_val[cur_mutex]=mutex_val[cur_mutex]*fun2_opval;	
		if(mutex_unlock(cur_mutex))
            panic("Failed to release mutex");
        cur_mutex++;
        if (event_wait(0) < 0)
            panic("Dev 0 failed");
	}
    while(1)
        if (event_wait(0) < 0)
            panic("Dev 0 failed");
}
//dev1
void fun3(void* str)
{
    int cur_mutex=1;
    
 	str = str;   
	while(cur_mutex<MUTEX_NUM){
        putchar((int)str);
        printf(">>mutex %d\n",cur_mutex);
		if(mutex_lock(cur_mutex))
            panic("Failed to acquire mutex");
	    mutex_val[cur_mutex]=mutex_val[cur_mutex]-fun3_opval;	
		if(mutex_unlock(cur_mutex))
            panic("Failed to release mutex");
        cur_mutex++;
        if (event_wait(1) < 0)
            panic("Dev 1 failed");
	}
    while(1)
        if (event_wait(1) < 0)
            panic("Dev 1 failed");
}
//dev2
void fun4(void* str)
{
    int cur_mutex=1,i=0,m_val;
    
 	str = str;   
	while(cur_mutex<MUTEX_NUM){
        putchar((int)str);
        printf(">>mutex %d\n",cur_mutex);
		if(mutex_lock(cur_mutex))
            panic("Failed to acquire mutex");
	    mutex_val[cur_mutex]=mutex_val[cur_mutex]*fun4_opval;	
		if(mutex_unlock(cur_mutex))
            panic("Failed to release mutex");
        cur_mutex++;
        if (event_wait(2) < 0)
            panic("Dev 2 failed");
	}
    for(;i<MUTEX_NUM;i++)
    {
        m_val=mutex_val[i];
        printf("Final mutex%d value %d == result value %d\n",i,m_val,result_val);
        if(m_val==result_val)
            puts(YES_STR);
        else
            puts(NO_STR);
    }
    puts(TEST_DONE);
    while(1)
        if (event_wait(2) < 0)
            panic("Dev 2 failed");
}
int main(int argc, char** argv)
{
	int mutex,i=0;
    puts("TEST STARTING...");
    result_val=((init_val+fun1_opval)*fun2_opval-fun3_opval)*fun4_opval;
    //creates an array of mutexes
    for(;i<MUTEX_NUM;i++)
    {
        mutex = mutex_create();
        if(errno == ENOMEM)
            puts("failed to create a mutex!!");
        mutex_val[i]=init_val;            
    }
    puts("Successfully created all the mutexes!!");
    puts(YES_STR);
	
    task_t tasks[4];
	tasks[0].lambda = fun2;
	tasks[0].data = (void*)'2';
	tasks[0].stack_pos = (void*)0xa2000000;
	tasks[0].C = 1;
	tasks[0].T = PERIOD_DEV0;

	tasks[1].lambda = fun3;
	tasks[1].data = (void*)'3';
	tasks[1].stack_pos = (void*)0xa1000000;
	tasks[1].C = 1;
	tasks[1].T = PERIOD_DEV1;

    tasks[2].lambda = fun4;
	tasks[2].data = (void*)'4';
	tasks[2].stack_pos = (void*)0xa1500000;
	tasks[2].C = 1;
	tasks[2].T = PERIOD_DEV2;
    //highest priority task
    tasks[3].lambda = fun1;
	tasks[3].data = (void*)'1';
	tasks[3].stack_pos = (void*)0xa2500000;
	tasks[3].C = 1;
	tasks[3].T = PERIOD_DEV3;

	task_create(tasks, 4);
	argc = argc ;
	argv = argv ;
	return 0;
}
