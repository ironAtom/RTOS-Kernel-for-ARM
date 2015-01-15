/** @file puts.c
 *
 * @brief Uses the write syscall to write out a string.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-10-31
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int puts(const char *s)
{
	write(STDOUT_FILENO, s, strlen(s));
	write(STDOUT_FILENO, "\n", 1);
	return 0;
}

