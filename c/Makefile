
TOPDIR ?= $(CURDIR)

include $(TOPDIR)/rule.mk
# =========================================================================== #

CFLAGS := -std=c99

mdirs := c std-c std-libc version
$(eval $(foreach mod,$(mdirs),$(call build, module, $(mod))))

$(eval $(call build, object, executable, helloworld))

# =========================================================================== #
include $(TOPDIR)/toplevel.mk
