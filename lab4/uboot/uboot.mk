UOBJS := stubs.o
UOBJS := $(UOBJS:%=$(UDIR)/%)
ALL_OBJS += $(UOBJS)

