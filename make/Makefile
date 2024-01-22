TOPDIR:=${CURDIR}

world:



include $(TOPDIR)/include/debug.mk



log_make = \
	 $(if $(call debug,$(1),v),,@)+ \
	 $(if $(BUILD_LOG), \
		set -o pipefail; \
		mkdir -p $(BUILD_LOG_DIR)/$(1)$(if $(4),/$(4));) \
	$(SCRIPT_DIR)/time.pl "time: $(1)$(if $(4),/$(4))/$(if $(3),$(3)-)$(2)" \
	$$(SUBMAKE) $(subdir_make_opts) $(if $(3),$(3)-)$(2) \
		$(if $(BUILD_LOG),SILENT= 2>&1 | tee $(BUILD_LOG_DIR)/$(1)$(if $(4),/$(4))/$(if $(3),$(3)-)$(2).txt)

define target
  $(if $(call debug,$(1),v),true,false)
  $(eval $(call warn,$(1),d,D $(1)))
endef

bd=linux
btype=mediatek
target=mt7981

define build
  $(call target, linux)
  $(eval $(call warn_eval,$(1)/$(bd),t,T,$(1)/$(bd)/$(btype)/$(target): $(if $(NO_DEPS)$(QUILT),,$($(1)/$(bd)/$(btype)/$(target)) $(call $(1)//$(btype)/$(target),$(1)/$(bd)/$(btype)))))
  $(call log_make,$(1)/$(bd),$(target),$(btype),$(filter-out __default,$(variant)))
endef



$(echo -e '\e[31 mdede')
$(info ---- Install Kernel Header ----)
$(echo -e '\e[0m')


world:
	$(call devel_warning, "test")
#	$(call build, work)


.PHONY: world