/** @file kernel.h
 *
 * @brief Main kernel -- primary interface.
 *
 * Author:  Huacong Cai <hcai@andrew.cmu.edu>
 *          Qingyu Tong <qtong@andrew.cmu.edu>
 * Date:    2014-11-24
 */

#ifndef KERNEL_H
#define KERNEL_H

#include <types.h>
#include <arm/swi.h>
#include <arm/interrupt.h>
#include <arm/timer.h>
#include <arm/exception.h>

extern uint32_t global_data;
int valid_addr(const void* start, size_t count, uintptr_t base, uintptr_t bound);
int enter_user_mode(int argc, char *argv[]);


#endif /* KERNEL_H */
