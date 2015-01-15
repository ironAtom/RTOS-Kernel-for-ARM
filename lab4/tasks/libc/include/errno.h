/** @file errno.h
 *
 * @brief Declares the global errno variable
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 07 Oct 2007 01:37:12 -0400
 */

#ifndef ERRNO_H
#define ERRNO_H

#include <bits/errno.h>

#ifndef ASSEMBLER

extern int errno;

#endif /* ASSEMBLER */

#endif /* ERRNO_H */
