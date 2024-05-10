
include scripts/toolchain.mk

objects=main1.o foo.o main2.o bar.o
mains=main1.o main2.o
src=$(PWD)/demk
export src

Q=@

ECHO=echo
INSTALL=
MAKELEVEL=1
all:

MAKEFILES=$(abspath $(lastword $(MAKEFILE_LIST)))


prepare: FORCE
	$(Q)$(ECHO) $(MAKELEVEL) $(MAKEFILE_LIST)
	$(Q)$(MAKE) $(prepare-toolchain)


all: prepare
	$(Q)$(ECHO) TOPDIR: $(CURDIR)
	$(Q)$(ECHO) $(filter-out $(mains),$(objects))




.PHONY: prepare all

FORCE: