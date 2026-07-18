#
# Copyright (c) 2026, pinrip, rixel, et al.
#
# Abstract:
# 	Kernel make flags and such
# Author:
# 	Chloe Pinrip
#

ifeq ($(NT_TARGET_ARCH), x64)
	CC_TARGET = x86_64-windows-unknown
else
	CC_TARGET =
endif

CC	=		\
	clang

NTOS_CFLAGS =						\
	-target $(CC_TARGET)			\
	-ffreestanding					\
	-nostdlib						\
	-I$(NT_PROJECT_ROOT)/sdk/head
