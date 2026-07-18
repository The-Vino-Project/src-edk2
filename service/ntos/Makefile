#
# Copyright (c) 2026, pinrip, rixel, et al.
#
# Abstract:
# 	NT kernel build script
# Author:
# 	Chloe Pinrip
#

.PHONY: all
all: ke machine

.PHONY: ke
ke:
	cd ke/; $(MAKE)

.PHONY: machine
machine:
	cd arch/$(NT_TARGET_ARCH); $(MAKE)
