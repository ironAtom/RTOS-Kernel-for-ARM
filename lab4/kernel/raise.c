/**
 * @file raise.c
 *
 * @brief Divide by zero exception handler.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 */

#include <exports.h>

void raise(void)
{
	puts("Divide by zero -- In kernel\n");

	while(1);
}
