#
# Copyright (c) 2026, pinrip, rixel, et al.
#
# Abstract:
# 	NT kernel machdep build script
# Author:
# 	Chloe Pinrip
#

include ../../../mk/ntos.mk

ASMFILES = $(shell find . -name "*.S")
ASMOFILES = $(ASMFILES:.S=.S.o)
ASMDFILES = $(ASMFILES:.S=.S.d)

CFLAGS = 			\
	$(NTOS_CFLAGS)	\
	-MMD

KERNEL_OUTPUT = 					\
	$(NT_PROJECT_ROOT)/artifacts/ntoskrnl.sys

.PHONY: all
all: $(KERNEL_OUTPUT)

.PHONY: $(KERNEL_OUTPUT)
$(KERNEL_OUTPUT): $(ASMOFILES)
	$(LD) -Tdev/link.ld $(ASMOFILES) -o $@

%.S.o: %.S
	$(CC) -c $(CFLAGS) $< -o $@
