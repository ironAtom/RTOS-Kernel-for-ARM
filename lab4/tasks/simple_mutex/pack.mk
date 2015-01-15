PROGS_DAGGER_OBJS := simple_mutex.o
PROGS_DAGGER_OBJS := $(PROGS_DAGGER_OBJS:%=$(TDIR)/simple_mutex/%)
ALL_OBJS += $(PROGS_DAGGER_OBJS)

$(TDIR)/bin/simple_mutex : $(TSTART) $(PROGS_DAGGER_OBJS) $(TLIBC)

