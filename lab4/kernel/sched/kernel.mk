SCHED_OBJS := sched.o ub_test.o ctx_switch.o ctx_switch_asm.o run_queue.o
SCHED_OBJS := $(SCHED_OBJS:%=$(KDIR)/sched/%)

KOBJS += $(SCHED_OBJS)
