
# debug flags:
#
# d: show subdirectory tree
# t: show added targets
# l: show legacy targets
# r: show autorebuild messages
# v: verbose (no .SILENCE for common targets)

build_debug:=dltvr

# $1 - name
# $2 - flag
define debug
$$(findstring $(2),$$(if $$(DEBUG_SCOPE_DIR),$$(if $$(filter $$(DEBUG_SCOPE_DIR)%,$(1)),$(build_debug)),$(build_debug)))
endef


# $1 - name
# $2 - flag
# $3 - text
define warn
$$(if $(call debug,$(1),$(2)),$$(warning $(3)))
endef

# $1 - name
# $2 - flag
# $3 - command
define debug_eval
$$(if $(call debug,$(1),$(2)),$(3))
endef

# $1 - name
# $2 - flag
# $3 - command1
# $4 - command2
define warn_eval
$(call warn,$(1),$(2),$(3) $(4))
$(4)
endef

