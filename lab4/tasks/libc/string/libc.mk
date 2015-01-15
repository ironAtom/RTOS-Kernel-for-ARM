TLIBC_STRING_OBJS := memmove.o memcmp.o memset.o \
	strcat.o strchr.o strcmp.o strcpy.o strcspn.o strlen.o \
	strncat.o strncmp.o strncpy.o strpbrk.o strrchr.o strspn.o strstr.o
TLIBC_STRING_OBJS := $(TLIBC_STRING_OBJS:%=$(TLIBCDIR)/string/%)
TLIBC_OBJS += $(TLIBC_STRING_OBJS)
