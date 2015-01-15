/** @file memmove.c
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-10-30
 */

#include <string.h>

void* memmove(void* dest, const void* src, size_t count)
{
	char* d;
	const char* s;
	size_t i;

	d = (char*)dest;
	s = (const char*)src;

	if ((uintptr_t)d < (uintptr_t)s)
		for (i = 0; i != count; i++)
			d[i] = s[i];
	else
		for (i = count; i != 0; i--)
			d[i-1] = s[i-1];
	
	return dest;
}

void* memcpy(void* dest, const void* src, size_t count)
{
	return memmove(dest, src, count);
}
