/** @file sys_err.c
 *
 * @brief 1. Tests task_create return EINVAL and EFAULT
 *				2. Tests mutex lock return EINVAL and EDEADLOCK
 *				3. Tests unlock return EINVAL and EPERM
 *				4. Tests device returning EINVAL
 *				5. Tests mutex create returning ENOMEM
 *
 * @author Tao Yang(taoy)
 * @date   2010-11-30
 */
#include <stdio.h>
#include <unistd.h>
#include <task.h>
#include <bits/errno.h>
#include <lock.h>
#include <errno.h>

#define MAX_MUTEX  32  // check this
volatile int spin = 0;
void check_return(int r,int expected,const char *str);
void report_suc(const char *str);
void report_fail(const char *str);

void fun1(void* str)
{	
	int ret2,i,ind;
	str = str;
	for(i=0 ;i<MAX_MUTEX;i++) {
		ind = mutex_create();
	}
	ret2 = mutex_create();
	check_return(errno,ENOMEM,"3. Mutex Create returns ENOMEM");
	ret2 = mutex_unlock(165);
	check_return(errno,EINVAL,"4. Mutex Unlock return EINVAL");
	ret2 = mutex_unlock(23);
	check_return(errno,EPERM,"5. Mutex Unlock return EPERM");
	ret2 = mutex_lock(124);
	check_return(errno,EINVAL,"6. Mutex Lock return EINVAL");
	ret2 = mutex_lock(4);
	check_return(ret2,0,"7. Mutex Lock return success");
	ret2 = mutex_lock(4);
	check_return(errno,EDEADLOCK,"8. Mutex Lock return EDEADLOCK");
	ret2 = mutex_unlock(4);
	check_return(ret2,0,"9. Mutex Unlock return success");
	ret2 = event_wait(10000);
	check_return(errno,EINVAL,"10. Event Wait return EINVAL");
	puts("TEST END!\n");
	while(1) {
		spin++;
	}
}


int main(int argc, char** argv)
{
	puts("TEST BEGIN!\n");
	int ret;

	task_t tasks[1];
	tasks[0].lambda = fun1;
	tasks[0].data = (void*)'@';
	tasks[0].stack_pos = (void*)0xa2000000;
	tasks[0].C = 1;
	tasks[0].T = PERIOD_DEV0;

	// this should fail and return EINVAL
	ret = task_create(tasks, 65);
	check_return(errno,EINVAL,"1. Test create return EINVAL");
	// this should return EFAULT
	ret = task_create((task_t *)0xdeadbeef, 30);
	check_return(errno,EFAULT,"2. Test create return EFAULT");
	
	ret = task_create(tasks, 1);
	puts("TEST END!\n");
	argc = argc;
	argv = argv;
	return 0;
}

void report_suc(const char *str) 
{
	puts(str);
	puts("        SUCCESS ****************\n");
}

void report_fail(const char *str) 
{
	puts(str);
	puts("        FAIL xxxxxxxxxxxxxxxxxx\n");
}

void check_return(int r,int expected,const char *str) {
	if(r == expected) 
		report_suc(str);
	else {
		printf("expect %d, get %d\n",expected,r);
		report_fail(str);
	}
}
