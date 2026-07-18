#
# Copyright (c) 2026, pinrip, rixel, et al.
#
# Abstract:
# 	Kernel executive build script
# Author:
# 	Chloe Pinrip
#

include ../../mk/ntos.mk
CFILES = $(shell find . -name "*.c")
DFILES = $(CFILES:.c=.d)
OFILES = $(CFILES:.c=.o)

CFLAGS =							   \
	$(NTOS_CFLAGS)					   \

.PHONY: all
all: $(OFILES)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
