/** @file cyclone.c
 *
 * @brief recursively calls task create
 *	    Tests: 1. task_create cancels current task
 *	           2. Timer has at least 10ms granularity
 *		   3. Sleep works properly
 * @note  Dont think this is realted to the OS cyclone
 *
 * @author Tao Yang(taoy)
 * @date   2010-11-30
 */
#include <stdio.h>
#include <unistd.h>
#include <task.h>
#include <bits/dev.h>
//#include <lock.h>

#define ITE  30
volatile int ct;
void panic(const char* str)
{
	puts(str);
	while(1);
}

void fun1(void* str)
{
	ct++;
	str = str;
	if(ct > ITE) {
		puts("Test ends!!");
		while(1) {
			ct++;
		}
	}
	sleep(ct * 10);
	printf("Time now is %lu\n",time());

	task_t tasks[1];
	tasks[0].lambda = fun1;
	tasks[0].data = (void*)0;
	tasks[0].stack_pos = (void*)0xa1000000;
	tasks[0].C = 1;
	tasks[0].T = PERIOD_DEV3;
	
	task_create(tasks, 1);
	// task create wipe out the task, therefore never reaches here
	puts("TASK SHOULD NEVER REACH HERE, FAIL XXXXXXXXXXXXXXXXX");
}


int main(int argc, char** argv)
{
	ct = 0;
	puts("Test begin");
	task_t tasks[1];
	tasks[0].lambda = fun1;
	tasks[0].data = (void*)0;
	tasks[0].stack_pos = (void*)0xa1000000;
	tasks[0].C = 1;
	tasks[0].T = PERIOD_DEV3;

	task_create(tasks, 1);

	puts("WTF!\n");
	argc = argc;
	argv = argv;
	return 0;
}
