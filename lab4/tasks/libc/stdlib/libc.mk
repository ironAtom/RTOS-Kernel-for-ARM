TLIBC_STDLIB_OBJS := errno.o ctype.o atoi.o strtol.o strtoul.o rand.o
TLIBC_STDLIB_OBJS := $(TLIBC_STDLIB_OBJS:%=$(TLIBCDIR)/stdlib/%)
TLIBC_OBJS += $(TLIBC_STDLIB_OBJS)
