TLIBC = $(TLIBCDIR)/libc.a
TSTART = $(TLIBCDIR)/crt0.o

TLIBC_GLOBAL_OBJS := raise.o
TLIBC_GLOBAL_OBJS := $(TLIBC_GLOBAL_OBJS:%=$(TLIBCDIR)/%)

TLIBC_LIBS = swi string stdio stdlib
TLIBC_MKS = $(TLIBC_LIBS:%=$(TLIBCDIR)/%/libc.mk)

include $(TLIBC_MKS)

TLIBC_OBJS += $(TLIBC_GLOBAL_OBJS)
ALL_OBJS += $(TLIBC_OBJS) $(TSTART)
ALL_CLEANS += $(TLIBC)

$(TLIBC) : $(TLIBC_OBJS)

	@echo AR $(notdir $@)
	@cp $(LIBGCC) $@
	@$(AR) rs $@ $^