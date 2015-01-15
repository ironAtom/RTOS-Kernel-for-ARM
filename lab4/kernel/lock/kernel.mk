LOCK_OBJS := mutex.o
LOCK_OBJS := $(LOCK_OBJS:%=$(KDIR)/lock/%)

KOBJS += $(LOCK_OBJS)
