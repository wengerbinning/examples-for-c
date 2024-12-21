
TOPDIR ?= $(CURDIR)

include $(TOPDIR)/rule.mk
# =========================================================================== #

CFLAGS := -std=c99

LIBS += -lfcgi

iostream-objs := main.o

$(eval $(call build, object, executable, iostream))

# =========================================================================== #
include $(TOPDIR)/toplevel.mk