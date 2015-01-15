/** @file simple_mutex.c
 *
 * @brief Simple test for mutex. Should print out succeSs!
 *				Tests: 1. basic create,lock,unlock behavior, and dev_wait
 *							 2. unlock releases only oldest waiting task
 *				Overall flow: 1-2-3-3-1-2-1
 * @note   This will not work for part 2 of this lab
 *
 * @author Tao Yang(taoy)
 * @date   2010-11-30
 */
#include <stdio.h>
#include <unistd.h>
#include <task.h>
#include <lock.h>

int even_t1 = 1;
int once = 0;
int even_t2 = 1;
int even_t3 = 1;
volatile int mid = -1;

void panic(const char* str)
{
	puts(str);
	while(1);
}

void fun1(void* str)
{
	// On first pass, create the shared mutex
	mid = mutex_create();
	while(1) {
		if(even_t1) {	
			// first and last s
			putchar((int)str);
			// terminating
			if(once >0) {
				putchar((int)'!');
				while(1) mid++;
			}
			once = 1;
			even_t1 = 0;
		}	 
 		else {
			// should not succeed right away
			mutex_lock(mid);
			// prints e
			putchar((int)'e');
			even_t1 = 1;
			mutex_unlock(mid);
		}		
		if (event_wait(0) < 0) {
				panic("Dev 0 failed");
	  }
	}
}

void fun2(void* str)
{
	while(1)
	{
		if(even_t2) {
			// prints u
			putchar((int)str);
			even_t2 = 0;
		}
 		else {
			// should not succeed right away
			mutex_lock(mid);
			// prints s!
			putchar((int)'S');
		}
		if (event_wait(1) < 0)
			panic("Dev 1 failed");
	}
}

void fun3(void* str)
{
	while(1)
	{
		//c 
		putchar((int)str);
		if(even_t3) {
			// should succeed
			mutex_lock(mid);
			even_t3 = 0;
		} else {
			mutex_unlock(mid);
		}
		if (event_wait(2) < 0)
			panic("Dev 2 failed");
	}
}
int main(int argc, char** argv)
{
	task_t tasks[3];
	tasks[0].lambda = fun1;
	tasks[0].data = (void*)'s';
	tasks[0].stack_pos = (void*)0xa2000000;
	tasks[0].C = 1;
	tasks[0].T = PERIOD_DEV0;
	tasks[1].lambda = fun2;
	tasks[1].data = (void*)'u';
	tasks[1].stack_pos = (void*)0xa1000000;
	tasks[1].C = 1;
	tasks[1].T = PERIOD_DEV1;
	tasks[2].lambda = fun3;
	tasks[2].data = (void*)'c';
	tasks[2].stack_pos = (void*)0xa1200000;
	tasks[2].C = 1;
	tasks[2].T = PERIOD_DEV2;
	task_create(tasks, 3);
	// just to get rid of compiler...
	argc = argc;
	argv = argv;
	puts("WTF!\n");
	return 0;
}
