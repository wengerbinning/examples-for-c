include $(TOPDIR)/rule.mk

##
$(eval $(call build, share_lib, center))

##
worker-objs := main.o
$(eval $(call build, program, worker))

include $(TOPDIR)/toplevel.mk