/**
 * @file assert.c
 *
 * @brief Assertion and debugging infrastructure.
 *
 * @author Kartik Subramanian
 */

#include <assert.h>
#include <stdarg.h>
#include <exports.h>

#include <arm/psr.h>
#include <arm/exception.h>

void panic(const char* fmt, ...)
{
	va_list list;

	va_start(list, fmt);
	// XXX This is not working... fix it later.
	//vprintf(fmt, list);
	printf("PANIC!");
	va_end(list);

	disable_interrupts();

	while(1);
}

