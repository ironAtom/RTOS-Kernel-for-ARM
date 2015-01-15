/** @file unistd.h
 *
 * @brief Declares C standard library functions
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 07 Oct 2007 01:38:30 -0400
 */

#ifndef UNISTD_H
#define UNISTD_H

#include <bits/fileno.h>
#include <sys/types.h>

#define NUM_DEVICES 4
#define PERIOD_DEV0 100
#define PERIOD_DEV1 200
#define PERIOD_DEV2 500
#define PERIOD_DEV3 50

ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
unsigned long time(void);
void sleep(unsigned long millis);
int event_wait(unsigned int dev);

#endif /* UNISTD_H */
