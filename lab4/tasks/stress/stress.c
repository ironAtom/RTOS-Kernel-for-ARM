/** @file stress.c
 *
 * @brief Creates 60 periodic tasks,each with diff frequency
 *
 * This is just a stress test, to ensure no concurrency bugs	
 * 
 * @author Tao Yang(taoy)
 * @date   2010-12-7
 */
#include <stdio.h>
#include <task.h>
#include <unistd.h>

#define 	NUM_TASK	60
#define 	END_TIME  9000
#define 	NUM_ITER	2
int once;
int flag;
int score[NUM_TASK-1];
void panic(const char* str)
{
	puts(str);
	while(1);
}

void fun1(void* str)
{
	while(1)
	{	
		if(flag == 0) {	
			printf("Time is now %lu\n",time());
		}
		score[(int)str]++;
		sleep((int)str);
		if (event_wait((int)str) < 0)
			panic("Dev 0 failed");
	}
}

void fun2(void* str)
{
	int i;
	while(1)
	{
		if(once < NUM_ITER) {
			once++;
			puts("One more time");
		}
    else {
			// check RMA
			for(i=0;i<(NUM_TASK-2);i++) {
				if(score[i] < score[i+1]) {
					printf("RMA check failed on %d\n",i);
					puts("xxxxxxxxxx Test FAIL xxxxxxxx");
				}
				if(score[i] == 0) {
					printf("Task %d never executed?\n",i);
					puts("xxxxxxxxxx Test FAIL xxxxxxxxx");
				}
			}
			puts("*********** Test PASEED *******************");
			flag = 1;
		}
		if (event_wait((int)str) < 0)
			panic("Dev 0 failed");
	}
}

int main(int argc, char** argv)
{
	puts("Test begins");
	int i;
	task_t tasks[NUM_TASK];
	once = 0;
	flag = 0;
	for(i=0;i<(NUM_TASK-1);i++) {
		tasks[i].lambda = fun1;
		tasks[i].data = (void*)i;
		tasks[i].stack_pos = (void*)(0xa2000000 + 0x10000 * i);
		tasks[i].C = (i+1);
		tasks[i].T = (i+1)*100;
		score[i] = 0;
	}
	tasks[i].lambda = fun2;
	tasks[i].data = (void*)i;
  tasks[i].stack_pos = (void*)(0xa2000000 + 0x10000 * i);
  tasks[i].C = 0;
	tasks[i].T = END_TIME;
	task_create(tasks, NUM_TASK);
	argc=argc; /* remove compiler warning */
	argv=argv; /* remove compiler warning */

	puts("Elvis could not leave the building, but why did your code get here!\n");
	return 0;
}
