
TOPDIR := $(CURDIR)


include $(TOPDIR)/rule.mk
# =========================================================================== #

mdirs :=  version debug file pipe

##
$(eval $(call build, library, share, version))

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
