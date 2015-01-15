/**
 * @file physmem.h
 *
 * @brief Definitions for Intel PXA-255 physical memory layout.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 *
 * @date 2008-11-16
 */

#ifndef _PHYSMEM_H_
#define _PHYSMEM_H_

#define FLASH_START_ADDR 0x00000000
#define FLASH_END_ADDR   0x01000000
#define RAM_START_ADDR   0xa0000000
#define RAM_END_ADDR     0xa4000000

#ifndef ASSEMBLER

#endif /* ASSEMBLER */

#endif /* _PHYSMEM_H_ */
