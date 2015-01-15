/**
 * @file raise.c
 *
 * @brief Divide by zero exception handler.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 */

#include <stdio.h>
#include <stdlib.h>

void raise(void)
{
	puts("Divide by zero\n");
	while(1);
}
