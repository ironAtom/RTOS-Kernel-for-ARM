/* Modified from u-boot-1.1.4/include/exports.h */

#ifndef _EXPORTS_H_
#define _EXPORTS_H_

#include <types.h>
#include <stdarg.h>

/* From common.h: */
typedef void (interrupt_handler_t)(void *);

/* These are declarations of exported functions available in C code */
unsigned long get_version(void);
int  getc(void);
int  tstc(void);
void putc(const char);
void puts(const char*) __attribute__((nonnull));
void printf(const char* fmt, ...) __attribute__((nonnull (1), format (printf, 1, 2)));
void install_hdlr(int, interrupt_handler_t*, void*);
void free_hdlr(int);
void *malloc(size_t);
void free(void*);
void udelay(unsigned long);
unsigned long get_timer(unsigned long);
void vprintf(const char *, va_list) __attribute__((nonnull));
void do_reset (void) __attribute__((noreturn));
unsigned long simple_strtoul(const char*, char**, unsigned int) __attribute__((const, nonnull));
char* getenv (char*) __attribute__((nonnull));
void setenv (char*, char*) __attribute__((nonnull));

void app_startup(void);

enum {
#define EXPORT_FUNC(x) XF_ ## x ,
#include <_exports.h>
#undef EXPORT_FUNC

	XF_MAX
};

#define XF_VERSION	2

#endif /* _EXPORTS_H_ */
