PACKAGE_MKS = $(PACKAGES:%=$(TDIR)/%/pack.mk)
PACKAGE_TARGETS = $(PACKAGES:%=$(TDIR)/bin/%)

ALL_CLOBBERS += $(PACKAGES:%=$(TDIR)/%/skyeye.conf) $(PACKAGES:%=$(TDIR)/%/package.bin)

include $(TLIBCDIR)/libc.mk

LIBC_GROUP = --start-group $(TLIBC) $(LIBGCC) --end-group

include $(PACKAGE_MKS)


$(PACKAGES) : % : $(TDIR)/bin/%.bin $(TDIR)/%/skyeye.conf $(TDIR)/%/package.bin

# Create a skyeye conf file link local to each binary so that you can easily 
# invoke skyeye.  Similarly create a symlink to the actual binary.
%/skyeye.conf :
	@echo LN $(notdir $@)
	@ln -s $(TDIR)/skyeye.conf $@

$(TDIR)/%/package.bin : $(TDIR)/bin/%.bin
	@echo LN $(notdir $@)
	@ln -s $< $@

$(PACKAGE_TARGETS):
	@echo LD $(notdir $@)
	@$(LD) -static $(LDFLAGS) -o $@ $^

