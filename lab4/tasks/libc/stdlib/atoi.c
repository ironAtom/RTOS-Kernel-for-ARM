/** @file atoi.c
 *
 * @brief Implements atoi -- man atoi for info.
 *
 * Imported from 15-410's 410user.
 *
 * @author Unknown souls who worked on mbermanref
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 */

#include <stdlib.h>
#include <ctype.h>

long atol(const char* str)
{
	long n = 0;

	while (isdigit(*str))
	{
		n = n * 10 + *str - '0';
		str++;
	}

	return n;
}

int atoi(const char* str)
{
	return (int)atol(str);
}
