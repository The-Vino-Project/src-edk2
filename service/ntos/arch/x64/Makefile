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
OFILES = $(shell find ../../ -name "*.o" | grep -v "arch")
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
	$(CC) 						\
		$(CFLAGS) 				\
		-fuse-ld=lld 			\
		-Wl,/subsystem:native	\
		-Wl,/entry:BspStart		\
		-Wl,/base:0x100000		\
		-Wl,/fixed:no			\
		-Wl,/dynamicbase		\
		$(ASMOFILES) 			\
		$(OFILES)				\
		-o $@

%.S.o: %.S
	$(CC) -c $(CFLAGS) $< -o $@
