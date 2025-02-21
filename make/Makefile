
targets := helloworld



helloworld-type=shared-library






Q=@

build_object = echo $1 $(type)

define build_library_target
	$(Q)case $(if $($(target)-type),$($(target)-type),shared-library) in \
		*shared-library) $(call build_library_target, $(target))   ;; \
		*static-library) $(call build_library_target, $(target))   ;; \
		esac
endef

# .SECONDEXPANSION:
define build_target
	$(Q)target=$(strip $(1))
	$(Q)case $(if $($(target)-type),$($(target)-type),executable-object) in \
		*include)   echo $(type)   ;; \
		*object) 	$(build_object )   ;; \
		*library)   $(call build_library_target, $(target))   ;; \
		*license)	echo $($(target)-type)   ;; \
		*document)  echo $($(target)-type)   ;; \
		*config)    echo $($(target)-type)   ;; \
		*data)      echo $($(target)-type)   ;; \
		*script)	echo $($(target)-type)   ;; \
		*)			echo $(target) ; \
		esac
endef


all:
	$(foreach target, $(targets), $(call build_target, $(target)))