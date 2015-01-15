/** @stdlib.h
 *
 * @brief Declares C standard library functions
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 07 Oct 2007 01:38:16 -0400
 *
 * Merged with code from 15-410's 410user libraries.  Thank you guys!
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-10-30
 */

#ifndef STDLIB_H
#define STDLIB_H

long atol(const char* str) __attribute__((const, nonnull));
int atoi(const char* str) __attribute__((const, nonnull));

long strtol(const char* p, char** out_p, int base) __attribute__((const, nonnull));
unsigned long strtoul(const char* p, char** out_p, int base) __attribute__((const, nonnull));

int rand(void);
void srand(unsigned int seed);

#endif /* STDLIB_H */
