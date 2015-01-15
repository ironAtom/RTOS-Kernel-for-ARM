/** @file ctype.h
 *
 * @brief Predicates for characters.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-10-30
 */

#ifndef _CTYPE_H_
#define _CTYPE_H_

#include <inline.h>

INLINE int __attribute__((const)) isascii(int c)
{
	return (c >= 0) && (c <= 127);
}

INLINE int __attribute__((const)) iscntrl(int c) 
{
	return (c < ' ') || (c > 126);
}

INLINE int __attribute__((const)) isdigit(int c) 
{
	return (c >= '0') && (c <= '9');
}

INLINE int __attribute__((const)) isgraph(int c) 
{
	return (c > ' ') && (c <= 126);
}

INLINE int __attribute__((const)) islower(int c) 
{
	return (c >= 'a') && (c <= 'z');
}

INLINE int __attribute__((const)) isprint(int c) 
{
	return (c >= ' ') && (c <= 126);
}

INLINE int __attribute__((const)) isspace(int c) 
{
	return (c == ' ') || (c == '\f') || (c == '\n')
		|| (c == '\n') || (c == '\r') || (c == '\t') || (c == '\v');
}

INLINE int __attribute__((const)) isupper(int c) 
{
	return (c >= 'A') && (c <= 'Z');
}

INLINE int __attribute__((const)) isxdigit(int c) 
{
	return isdigit(c) ||
		((c >= 'A') && (c <= 'F')) ||
		((c >= 'a') && (c <= 'f'));
}

INLINE int __attribute__((const)) isalpha(int c) 
{
	return islower(c) || isupper(c);
}

INLINE int __attribute__((const)) isalnum(int c) 
{
	return isalpha(c) || isdigit(c);
}

INLINE int __attribute__((const)) ispunct(int c) 
{
	return isgraph(c) && !isalnum(c);
}

INLINE int __attribute__((const)) toupper(int c) 
{
	return islower(c) ? c - 'a' + 'A' : c;
}

INLINE int __attribute__((const)) tolower(int c) 
{
	return isupper(c) ? c - 'A' + 'a' : c;
}

#endif	/* _CTYPE_H_ */
