TLIBC_STDIO_OBJS := doprnt.o doscan.o hexdump.o printf.o putchar.o puts.o \
	sprintf.o sscanf.o
TLIBC_STDIO_OBJS := $(TLIBC_STDIO_OBJS:%=$(TLIBCDIR)/stdio/%)
TLIBC_OBJS += $(TLIBC_STDIO_OBJS)
