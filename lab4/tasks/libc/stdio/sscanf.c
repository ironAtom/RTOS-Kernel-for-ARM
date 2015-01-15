/** @file sscanf.c
 *
 * Modified from 15-410's 410usr library.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-10-30
 */
/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */

#include <stdio.h>
#include <stdarg.h>
#include "doscan.h"

static int readchar(void* arg)
{
	return *(*(unsigned char**)arg)++;
}

static void unchar(int c __attribute__((unused)), void* arg)
{
	c=c;
	(*(unsigned char**)arg)--;
}

int vsscanf(const char* s, const char* fmt, va_list args)
{
	return _doscan((const unsigned char*)fmt, args, readchar, unchar, &s);
}

int sscanf(const char *s, const char *fmt, ...)
{
	int ret;
	va_list args;

	va_start(args, fmt);
	ret = vsscanf(s, fmt, args);
	va_end(args);

	return ret;
}

