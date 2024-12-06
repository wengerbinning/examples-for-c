
## Dependent Command Tools
# This section specifies the command tools required for building the framework,
# which can be overridden using environment variables in across compilation
# environment.

ECHO ?= echo
MAKE ?= make
RM   ?= rm
CC   ?= gcc
LD   ?= ld
AR   ?= ar

export ECHO MAKE RM CC LD AR

## Project Build Parameters
# This section specifies the compilation parameters required for the project.

CFLAGS   += -g
CXXFLAGS ?=
CPPFLAGS ?=
LDFLAGS  ?=
LIBS     ?=

TOPDIR  ?= $(CURDIR)
DESTDIR ?= $(shell pwd)/dest

export DESTDIR
## Project Install Parameters
# This section specifies the install parameters required for the project.

prefix  ?= usr/local
bin     ?= $(prefix)/bin
sbin    ?= $(prefix)/sbin
lib     ?= $(prefix)/lib
libexec ?= $(prefix)/libexec
include ?= $(prefix)/include
share	?= $(prefix)/share
etc		?= $(prefix)/etc

## Porject Build Module Variables
# (No need to specify automatically generated the build framework.)
# this section specificies the build variables required for the module. If you
# need debug, you can analyze it by printing these variables.

mod-cflags   :=
mod-cxxflags :=
mod-cppflags :=
mod-ldflags  :=
mod-libs     :=

## Project Build  Share Library Variables
# (No need to specify automatically generated the build framework.)
# This section specifices the build variables required for the share library.
# If you need debug, you can analyze it byu printing these variables.

shlib-cflags    :=
shlib-cxxflags  :=
shlib-cppflags  :=
shlib-ldflags   :=
shlib-libs      :=

## Project Build Static Library Variables
# (No need to specify automatically generated the build framework.)
# This section specifices the build variables required for the static library.
# If you need debug, you can analyze it byu printing these variables.

stlib-cflags    :=
stlib-cxxflags  :=
stlib-cppflags  :=
stlib-ldflags   :=
stlib-libs      :=

## Project Build Relocatable Object Variables
# (No need to specify automatically generated the build framework.)
# This section specifices the build variables required for the relocatable
# object. If you need debug, you can analyze it byu printing these variables.

relo-cflags    :=
relo-cxxflags  :=
relo-cppflags  :=
relo-ldflags   :=
relo-libs      :=

## Project Build Executable Object Variables
# (No need to specify automatically generated the build framework.)
# This section specifices the build variables required for the executable
# object. If you need debug, you can analyze it byu printing these variables.

exec-cflags    :=
exec-cxxflags  :=
exec-cppflags  :=
exec-ldflags   :=
exec-libs      :=

## Project Build Target Variables
# (No need to specify automatically generated the build framework.)

mods           :=
mods-install   :=
mods-uninstall :=
mods-clean     :=
shlibs         :=
stlibs         :=
relos          :=
execs          :=

cflags    :=
cxxflags  :=
cppflags  :=
ldflags   :=
objs      :=
relo-objs :=
libs      :=
flags1    :=
flags2    :=



# =========================================================================== #

export TOPDIR
SCRIPTS_HOME :=$(TOPDIR)/scripts
CURDIR=$(PWD)

all:

# =========================================================================== #

define log
@echo -en "\e[32m[$(strip $(2))] \e[0m"; echo $(strip $(3))
endef

# =========================================================================== #

## Build Module
# =============

# usage: module_perpare_variables <mod>
define module_perpare_variables
  cppflags := -I$(TOPDIR)
  cppflags += -I$(if $(MOD_NAME),$(MOD_NAME)/)include
  cppflags += $(if $(CPPFLAGS), $(CPPFLAGS))
  ldflags := -L$(TOPDIR)$(if $(MOD_NAME),/$(MOD_NAME))
  ldflags += $(if $(LDFLAGS), $(LDFLAGS))
endef
# usage: module_perpare <mod>
define module_perpare
  mods += $(strip $(1))
  mods-install += $(strip $(1))-install
  mods-uninstall += $(strip $(1))-uninstall
  mods-clean += $(strip $(1))-clean
  $(eval $(call module_perpare_variables, $(1)))
  
  flags1 := --no-print-directory
  flags1 += MOD_NAME="$(if $(MOD_NAME),$(MOD_NAME)/)$(strip $(1))"
  flags2 := MODS="$(mods)" CPPFLAGS="$(cppflags)" LDFLAGS="$(ldflags)"
endef
# usage: module_build <mod>
define module_build
$(strip $(1)): FORCE
	$(call log, info, MAKE, $(if $(MOD_NAME),$(MOD_NAME)/)$(strip $(1)))
	@$(MAKE)$(if $(flags1), $(flags1)) -C $$@ $(flags2)
$(strip $(1))-install:
	$(call log, info, INSTALL, $(if $(MOD_NAME),$(MOD_NAME)/)$(strip $(1)))
	@$(MAKE)$(if $(flags1), $(flags1)) install -C $(strip $(1))
$(strip $(1))-uninstall:
	$(call log, info, UNINSTALL, $(if $(MOD_NAME),$(MOD_NAME)/)$(strip $(1)))
	@$(MAKE)$(if $(flags1), $(flags1)) uninstall -C $(strip $(1))
$(strip $(1))-clean:
	$(call log, info, CLEAN, $(if $(MOD_NAME),$(MOD_NAME)/)$(strip $(1)))
	@$(MAKE)$(if $(flags1), $(flags2)) clean -C $(strip $(1))
endef
# usage: module_target <mod> <target>
define module_target
  $$(shell $(SCRIPTS_HOME)/build-target.sh $1 $2)
endef

# =========================================================================== #

# usage: library_share_perpare_varibales <target>
define library_share_perpare_varibales
  cflags := -fPIC
  cflags += $(if $(CFLAGS), $(CFLAGS))
  cflags += $(if $(shlib-cflags), $(shlib-cflags))
  cflags += $(if $($(strip $(1))-cflags), $($(strip $(1))-cflags))
  cppflags := -Iinclude
  cppflags += $(if $(CPPFLAGS), $(CPPFLAGS))
  cppflags += $(if $(shlib-cppflags), $(shlib-cppflags))
  cppflags += $(if $($(strip $(1))-cppflags), $($(strip $(1))-cppflags))
  ldflags := $(if $(LDFLAGS), $(LDFLAGS))
  ldflags += $(if $(shlib-ldflags), $(shlib-ldflags))
  ldflags += $(if $($(strip $(1))-ldflags), $($(strip $(1))-ldflags))
 
  objs := $(if $($(strip $(1))-objs), $($(strip $(1))-objs), $(strip $(1)).o)
  libs := $(if $(LIBS), $(LIBS))
  libs += $(if $(shlib-libs), $(shlib-libs))
  libs += $(if $($(strip $(1))-libs), $($(strip $(1))-libs))
endef
# usage: library_share_perpare <target>
define library_share_perpare
  shlibs += lib$(strip $(1)).so
  mod-libs += -l$(strip $(1))
  $(eval $(call library_share_perpare_varibales, $(1)))
  flags1 := -c
  flags1 += $(if $(cflags), $(cflags))$(if $(cppflags), $(cppflags))
  flags2 := $(if $(cflags), $(cflags))$(if $(ldflags), $(ldflags))
endef
# usage: library_share_build <target>
define library_share_build
$(objs): %.o: %.c
	$(call log, info, CC, $(if $(MOD_NAME),$(MOD_NAME)/)$$@)
	@$(CC)$(if $(flags1), $(flags1)) $$<
lib$(strip $(1)).so: $(objs)
	$(call log, info, LD, $(if $(MOD_NAME),$(MOD_NAME)/)$$@)
	@$(CC)$(if $(flags2), $(flags2)) -shared -o $$@ $$^$(if $(libs), $(libs))
endef

# usage: library_static_perpare_variables <target>
define library_static_perpare_variables
  cflags := $(if $(CFLAGS), $(CFLAGS))$(if $(stlib-cflags), $(stlib-cflags))
  cflags += $(if $($(strip $(1))-cflags), $($(strip $(1))-cflags))
  cppflags := -Iinclude
  cppflags += $(if $(CPPFLAGS), $(CPPFLAGS))
  cppflags += $(if $(stlib-cppflags), $(stlib-cppflags))
  cppflags += $(if $($(strip $(1))-cppflags), $($(strip $(1))-cppflags))
  ldflags := $(if $(LDFLAGS), $(LDFLAGS))
  ldflags += $(if $(stlib-ldflags), $(stlib-ldflags))
  ldflags += $(if $($(strip $(1))-ldflags), $($(strip $(1))-ldflags))

  objs := $(if $($(strip $(1))-objs), $($(strip $(1))-objs), $(strip $(1)).o)
  libs := $(if $(LIBS), $(LIBS))
  libs += $(if $(stlib-libs), $(stlib-libs))
  libs += $(if $($(strip $(1))-libs), $($(strip $(1))-libs))
endef
# usage: library_static_perpare <target>
define library_static_perpare
  stlibs += lib$(strip $(1)).a
  mod-libs += -l$(strip $(1))
  $(eval $(call library_static_perpare_variables, $(1)))
  flags1 := -c
  flags1 += $(if $(cflags), $(cflags))$(if $(cppflags), $(cppflags))
  flags2 := $(if $(cflags), $(cflags))$(if $(ldflags), $(ldflags))
endef
# usage: library_static_build <target>
define library_static_build
$(objs): %.o: %.c
	$(call log, info, CC, $(if $(MOD_NAME),$(MOD_NAME)/)$$@)
	@$(CC)$(if $(flags1), $(flags1)) $$<
lib$(strip $(1)).a: $(objs)
	$(call log, info, LD, $(if $(MOD_NAME),$(MOD_NAME)/)$$@)
	@$(AR) crv $$@ $$^ >/dev/null
endef

## Build Library
# ==============

# usage: library_perpare <type> <target>
define library_perpare
  $(eval $(call library_$(strip $(1))_perpare, $(2)))
endef
# usage: library_build <type> <target>
define library_build
  $(eval $(call library_$(strip $(1))_build, $(2)))
endef

# =========================================================================== #

# usage: object_relocatable_perpare_variables <target>
define object_relocatable_perpare_variables
  cflags := $(if $(CFLAGS), $(CFLAGS))
  cflags += $(if $(relo-cflags), $(relo-cflags))
  cflags += $(if $($(strip $(1))-cflags), $($(strip $(1))-cflags))
  cppflags := -Iinclude
  cppflags += $(if $(CPPFLAGS), $(CPPFLAGS))
  cppflags += $(if $(relo-cppflags), $(relo-cppflags))
  cppflags += $(if $($(strip $(1))-cppflags), $($(strip $(1))-cppflags))
  ldflags := -L.
  ldflags += $(if $(LDFLAGS), $(LDFLAGS))
  ldflags += $(if $(relo-ldflags), $(relo-ldflags))
  ldflags += $(if $($(strip $(1))-ldflags), $($(strip $(1))-ldflags))

  objs := $(if $($(strip $(1))-objs), $($(strip $(1))-objs), $(strip $(1)).o)
  libs := $(if $(LIBS), $(LIBS))
  libs += $(if $(relo-libs), $(relo-libs))
  libs += $(if $($(strip $(1))-libs), $($(strip $(1))-libs))
endef
# usage: object_relocatable_perpare <target>
define object_relocatable_perpare
  relos += $(strip $(1)).o
  $(eval $(call object_relocatable_perpare_variables, $(1)))
  flags1 := -c
  flags1 += $(if $(cflags), $(cflags))$(if $(cppflags), $(cppflags))
  flags2 := $(if $(cflags), $(cflags))$(if $(ldflags), $(ldflags))
endef
# usage: object_relocatable_build <taregt>
define object_relocatable_build
$(objs): %.o: %.c
	$(call log, info, CC, $(if $(MOD_NAME),$(MOD_NAME)/)$$@)
	@$(CC) -c$(if $(flags1), $(flags1)) $$<
$(strip $(1)).o: $(objs)
	$(call log, info, LD, $(if $(MOD_NAME),$(MOD_NAME)/)$$@)
	@$(LD) --no-gc-sections -o $$@ -r $$^
endef

# usage: object_executable_perpare_variables <target>
define object_executable_perpare_variables
  cflags := $(if $(CFLAGS), $(CFLAGS))$(if $(exec-cflags), $(exec-cflags))
  cflags += $(if $($(strip $(1))-cflags), $($(strip $(1))-cflags))
  cppflags := -Iinclude
  cppflags += $(if $(CPPFLAGS), $(CPPFLAGS))
  cppflags += $(if $(exec-cppflags), $(exec-cppflags))
  cppflags += $(if $($(strip $(1))-cppflags), $($(strip $(1))-cppflags))
  ldflags := -L.
  ldflags += $(if $(LDFLAGS), $(LDFLAGS))
  ldflags += $(if $(mod-ldflags), $(mod-ldflags))
  ldflags += $(if $(exec-ldflags), $(exec-ldflags))
  ldflags += $(if $($(strip $(1))-ldflags), $($(strip $(1))-ldflags))
  
  objs := $(if $($(strip $(1))-objs), $($(strip $(1))-objs), $(strip $(1)).o)
  relo-objs := $(foreach mod, $(mods),$$(call module_target,$(mod), relos))
  libs := $(if $(LIBS), $(LIBS))$(if $(mod-libs), $(mod-libs))
  libs += $(if $(exec-libs), $(exec-libs))
  libs += $(if $($(strip $(1))-libs), $($(strip $(1))-libs))
endef
# usage: object_executable_perpare <target>
define object_executable_perpare
  execs += $(strip $(1))
  $(eval $(call object_executable_perpare_variables, $(1)))
  flags1 := -c
  flags1 += $(if $(cflags), $(cflags))$(if $(cppflags), $(cppflags))
  flags2 := $(if $(cflags), $(cflags))$(if $(ldflags), $(ldflags))
  link := $(objs)$(if $(relo-objs), $(relo-objs))$(if $(libs), $(libs))
endef

# usage: object_executable_build <target>
define object_executable_build
$(objs): %.o: %.c
	$(call log, info, CC, $(if $(MOD_NAME),$(MOD_NAME)/)$$@)
	@$(CC) $(if $(flags1), $(flags1)) $$<
$(1): $(objs) $(relo-objs)
	$(call log, info, LD, $(if $(MOD_NAME),$(MOD_NAME)/)$$@)
	@$(CC)$(if $(flags2), $(flags2)) -o $$@ $(if $(link), $(link)) 
endef

## Build Object
# =============

# usage: object_perpare <type> <target>
define object_perpare
  $(eval $(call object_$(strip $(1))_perpare, $(2)))
endef
# usage: object_build <type> <target>
define object_build
  $(eval $(call object_$(strip $(1))_build, $(2)))
endef

# =========================================================================== #

## Build
# ======

# usage: perpare <type> <target> <name>
define perpare
 type := $(strip $(1))/$(strip $(2))
 target := $(strip $(3))
endef
# usage: perpare <type> <target> <name>
define build
  $(if $(findstring $(strip $(1)), module library object), ,
    $(error Not support this type:$(strip $(1))))
  $(eval $(call perpare, $(1), $(2), $(3)))
  $(eval $(call $(strip $(1))_perpare, $(2), $(3)))
  $(eval $(call $(strip $(1))_build,   $(2), $(3)))
endef


