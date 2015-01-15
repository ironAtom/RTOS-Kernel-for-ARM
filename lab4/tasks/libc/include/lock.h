/** @file lock.h
 *
 * @brief Declaration of locking and synchronization primitives.
 *
 * @author  Qinyu Tong <qtong@andrew.cmu.edu>
 *          HuaCong Cai <hcai@andrew.cmu.edu>
 *
 * @date    Tue Nov 25 15:23:08 EST 2014
 */

#ifndef _LOCK_H_
#define _LOCK_H_

int mutex_create(void);
int mutex_lock(int mutex);
int mutex_unlock(int mutex);

#endif /* _LOCK_H_ */
