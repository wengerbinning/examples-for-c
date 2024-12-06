TOPDIR ?= $(CURDIR)
include $(TOPDIR)/rule.mk
# =========================================================================== #

builtin-objs := version.o

$(eval $(call build, object, relocatable, builtin))

$(eval $(call build, object, executable, main))

# =========================================================================== #
include $(TOPDIR)/toplevel.mk