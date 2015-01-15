/**
 * @file math.h
 *
 * @brief  Contains interface to integer math routines.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-08-07
 */

#ifndef _MATH_H_
#define _MATH_H_

unsigned int ilog2(unsigned int x);
unsigned int sum_region(unsigned int* buf, size_t num_words);

#endif   /* _MATH_H_ */
