/** @file syscall.h
 *
 * @brief Declares the kernel supported syscalls
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sat, 13 Oct 2007 23:54:45 -0400
 */

#ifndef SYSCALL_H
#define SYSCALL_H

#include <types.h>
#include <task.h>

ssize_t read_syscall(int fd, char *buf, size_t count);
ssize_t write_syscall(int fd, const char *buf, size_t count);

unsigned long time_syscall(void);
void sleep_syscall(unsigned long millis);

void invalid_syscall(unsigned int num) __attribute__((noreturn));

int task_create(task_t* tasks, size_t num_tasks);
int event_wait(unsigned int dev);

#endif /* SYSCALL_H */
