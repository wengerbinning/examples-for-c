
TOPDIR ?= $(CURDIR)

include $(TOPDIR)/rule.mk
# =========================================================================== #

CFLAGS := -std=c99

LIBS += -lcurl

request-objs := main.o

$(eval $(call build, object, executable, request))

# =========================================================================== #
include $(TOPDIR)/toplevel.mk