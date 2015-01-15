/**
 * @file inline.h
 *
 * @brief GCC specific dances to guarantee correct inlining.
 *
 * Gcc will never generate code for an extern inline function on its own.  Any
 * occurences of a call to an extern inline function will be expanded inline.
 * If the address of an extern inline function is taken, it is counted as an
 * external reference.
 *
 * To use this feature correctly, we put the code for all functions that we want
 * to inline in headers as `extern inline' and then put a single copy of the
 * function without extern inline in a library file.  This will cause most calls
 * to the function to get inlined.  Any remaining uses of the function (such as
 * taking the address of the function) will now refer to the single library copy
 * of the function.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 *
 * @date 2008-07-08
 */

/* No guards...  on purpose! */

#ifdef INLINE
#undef INLINE
#endif

#ifndef IMPLEMENTATION
#define INLINE extern inline
#else
#define INLINE
#endif
