
TOPDIR := $(CURDIR)


include $(TOPDIR)/rule.mk
# =========================================================================== #

dirs := file debug pipe

##
$(eval $(call build, share_lib, version))

##
$(eval $(call build, program, helloworld))
#
$(eval $(call build, program, environment))
#
$(eval $(call build, program, readlink))
#
$(eval $(call build, program, regex))


# =========================================================================== #
include $(TOPDIR)/toplevel.mk
