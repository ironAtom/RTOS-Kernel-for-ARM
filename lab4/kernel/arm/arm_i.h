/** @file arm_i.h
 * 
 * @brief Internal header -- install and restore handler routines.
 *
 * Author:  Huacong Cai <hcai@andrew.cmu.edu>
 *          Qingyu Tong <qtong@andrew.cmu.edu>
 * Date:    2014-11-24
 */

#ifndef _ARM_I_H_
#define _ARM_I_H_

unsigned install_handler(uint32_t vec_address, uint32_t *new_address, uint32_t **handler_location,
                         uint32_t *instruction1, uint32_t *instruction2);

void restore_handler(uint32_t *handler_location, uint32_t instruction1, uint32_t instruction2);

#endif /* _ARM_I_H_ */
