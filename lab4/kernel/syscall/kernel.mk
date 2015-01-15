SYSCALL_OBJS := io.o proc.o time.o
SYSCALL_OBJS := $(SYSCALL_OBJS:%=$(KDIR)/syscall/%)

KOBJS += $(SYSCALL_OBJS)
