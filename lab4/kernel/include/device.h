/** @file device.h
 *
 * @brief Declaration of "simulated devices".
 *
 * These devices each have an associated condition variable that they signal
 * with the given periodicity.  Each condition variable also has an associated
 * mutex of the same index.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date   2008-12-01
 */

#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <inline.h>
#include <types.h>
#include <exports.h>
#define NUM_DEVICES  4

extern const unsigned long dev_freq[NUM_DEVICES];
extern volatile bool_e dev_int_on;

void dev_init(void);
void dev_wait(unsigned int dev);
void dev_update(unsigned long num_millis);
void dev_clear(void);

INLINE void disable_device_interrupts(void) {
    dev_int_on = FALSE;
}

INLINE void enable_device_interrupts(void) {
    dev_int_on = TRUE;
}

#endif /* _DEVICE_H_ */

