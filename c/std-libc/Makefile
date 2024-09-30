
TOPDIR ?= $(CURDIR)


include $(TOPDIR)/rule.mk
# =========================================================================== #

mdirs :=  hexdump
$(eval $(foreach mod,$(mdirs),$(call build, module, $(mod))))

# =========================================================================== #
include $(TOPDIR)/toplevel.mk
