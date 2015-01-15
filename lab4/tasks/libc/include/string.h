/** @file string.h
 *
 * Taken from 15-410's 410lib files.
 * Adapted for use in 18-349.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-10-30
 */
/* 
 * Copyright (c) 1994 The University of Utah and
 * the Computer Systems Laboratory at the University of Utah (CSL).
 * All rights reserved.
 *
 * Permission to use, copy, modify and distribute this software is hereby
 * granted provided that (1) source code retains these copyright, permission,
 * and disclaimer notices, and (2) redistributions including binaries
 * reproduce the notices in supporting documentation, and (3) all advertising
 * materials mentioning features or use of this software display the following
 * acknowledgement: ``This product includes software developed by the
 * Computer Systems Laboratory at the University of Utah.''
 *
 * THE UNIVERSITY OF UTAH AND CSL ALLOW FREE USE OF THIS SOFTWARE IN ITS "AS
 * IS" CONDITION.  THE UNIVERSITY OF UTAH AND CSL DISCLAIM ANY LIABILITY OF
 * ANY KIND FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 *
 * CSL requests users of this software to return to csl-dist@cs.utah.edu any
 * improvements that they make and grant CSL redistribution rights.
 */
#ifndef _FLUX_MC_STRING_H_
#define _FLUX_MC_STRING_H_

#include <sys/types.h>

size_t strlen(const char *__s) __attribute__((const, nonnull));
char *strcpy(char *__dest, const char *__src) __attribute__((nonnull));
char *strncpy(char *__dest, const char *__src, size_t __n) __attribute__((nonnull));
char *strdup(const char *__s) __attribute__((nonnull));
char *strcat(char *__dest, const char *__src) __attribute__((nonnull));
char *strncat(char *__dest, const char *__src, size_t __n) __attribute__((nonnull));
int strcmp(const char *__a, const char *__b) __attribute__((const, nonnull));
int strncmp(const char *__a, const char *__b, size_t __n) __attribute__((const, nonnull));
char *strchr(const char *__s, int __c) __attribute__((const, nonnull));
char *strrchr(const char *__s, int __c) __attribute__((const, nonnull));
char *strstr(const char *__haystack, const char *__needle) __attribute__((const, nonnull));
char *strpbrk(const char *__s1, const char *__s2) __attribute__((const, nonnull));
size_t strspn(const char *__s1, const char *__s2) __attribute__((const, nonnull));
size_t strcspn(const char *__s1, const char *__s2) __attribute__((const, nonnull));

void *memset(void *__to, int __ch, size_t __n) __attribute__((nonnull));
int memcmp(const void *s1v, const void *s2v, size_t size) __attribute__((const, nonnull));

/* FIXME These are defined here only by tradition... we should move them. */
void *memcpy(void *__to, const void *__from, size_t __n) __attribute__((nonnull));
void *memmove(void *__to, const void *__from, size_t __n) __attribute__((nonnull));

#endif  /* _FLUX_MC_STRING_H_ */
