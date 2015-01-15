/**
 * @file reg.h
 *
 * @brief Generic memory mapped register access routines.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 *
 * @date 2008-07-08
 */

#ifndef _REG_H_
#define _REG_H_

#include <inline.h>
#include <types.h>

#define PERIPHERAL_BASE       0x40000000

INLINE uint32_t reg_read(size_t addr)
{
	return *((volatile uint32_t*)(PERIPHERAL_BASE + addr));
}

INLINE void reg_write(size_t addr, uint32_t data)
{
	*((volatile uint32_t*)(PERIPHERAL_BASE + addr)) = data;
}

INLINE void reg_set(size_t addr, uint32_t flags)
{
	volatile uint32_t* reg = (volatile uint32_t*)(PERIPHERAL_BASE + addr);
	*reg = *reg | flags;
}

INLINE void reg_clear(size_t addr, uint32_t flags)
{
	volatile uint32_t* reg = (volatile uint32_t*)(PERIPHERAL_BASE + addr);
	*reg = *reg & (~flags);
}

#endif /* _REG_H_ */
