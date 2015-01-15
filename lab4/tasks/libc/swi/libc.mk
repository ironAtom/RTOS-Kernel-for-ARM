TLIBC_SWI_OBJS := read.o write.o time.o sleep.o event_wait.o mutex_create.o mutex_unlock.o mutex_lock.o task_create.o
TLIBC_SWI_OBJS := $(TLIBC_SWI_OBJS:%=$(TLIBCDIR)/swi/%)
TLIBC_OBJS += $(TLIBC_SWI_OBJS)
