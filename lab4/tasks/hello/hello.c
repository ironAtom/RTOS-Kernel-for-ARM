/** @file hello.c
 *
 * @brief Prints out Hello world using the syscall interface.
 *
 * Links to libc.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date   2008-10-29
 */
#include <stdio.h>
#include <task.h>
#include <unistd.h>

const char hello[] = "Hello World\r\n";

int main(int argc, char** argv)
{
	task_t tasks[2];
	task_create(tasks, 0);
	argc=argc; /* remove compiler warning */
	argv[0]=argv[0]; /* remove compiler warning */

	//puts("Why did your code get here!\n");
	
	write(STDOUT_FILENO, hello, sizeof(hello) - 1);
	return 0;
}
