/** @file memcheck.c
 *
 * @brief  Memory address validation.
 *
 * @author Kartik Subramanian
 * @date   2008-11-21
 */

#include "kernel.h"

/**
 * @brief This function verifies of a given buffer is within an address range.
 *
 * @param start  A pointer to the start of the buffer.
 * @param count  The number of bytes in the buffer.
 * @param base   The base of the address space checked against.
 * @param bound  The bound or limit of the address space checked against.
 *               This is the address of the word past the last valid address in
 *               the segment.
 *
 * @return 0  Address is invalid.
 * @return 1  Address is valid.
 */
int valid_addr(const void* start, size_t count, uintptr_t base, uintptr_t bound)
{
	uintptr_t mem_start = (uintptr_t)start;
	uintptr_t mem_end   = (uintptr_t)start + count;

	if (mem_start < base || mem_start >= bound)
		return 0;

	if (mem_end < mem_start || mem_end > bound)
		return 0;
	
	return 1;
}

