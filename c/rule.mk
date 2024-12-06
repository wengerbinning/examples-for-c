
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

mods          :=
mod-cflags    :=
mod-cxxflags  :=
mod-cppflags  :=
mod-ldflags   :=
mod-libs      :=

## Project Build  Share Library Variables
# (No need to specify automatically generated the build framework.)
# This section specifices the build variables required for the share library.
# If you need debug, you can analyze it byu printing these variables.

shlibs          :=
shlib-cflags    :=
shlib-cxxflags  :=
shlib-cppflags  :=
shlib-ldflags   :=
shlib-libs      :=

## Project Build Static Library Variables
# (No need to specify automatically generated the build framework.)
# This section specifices the build variables required for the static library.
# If you need debug, you can analyze it byu printing these variables.

stlibs          :=
stlib-cflags    :=
stlib-cxxflags  :=
stlib-cppflags  :=
stlib-ldflags   :=
stlib-libs      :=

## Project Build Relocatable Object Variables
# (No need to specify automatically generated the build framework.)
# This section specifices the build variables required for the relocatable
# object. If you need debug, you can analyze it byu printing these variables.

relos          :=
relo-cflags    :=
relo-cxxflags  :=
relo-cppflags  :=
relo-ldflags   :=
relo-libs      :=

## Project Build Executable Object Variables
# (No need to specify automatically generated the build framework.)
# This section specifices the build variables required for the executable
# object. If you need debug, you can analyze it byu printing these variables.

execs          :=
exec-cflags    :=
exec-cxxflags  :=
exec-cppflags  :=
exec-ldflags   :=
exec-libs      :=

## Project Build Target Variables

objs     :=
cflags   :=
cxxflags :=
cppflags :=
ldflags  :=
libs     :=


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

# usage: module_perpare <mod>
define module_perpare
mods           += $(strip $(1))
mods-install   += $(strip $(1))-install
mods-uninstall += $(strip $(1))-uninstall
mods-clean     += $(strip $(1))-clean
cppflags  := -I$(TOPDIR)
cppflags  += $(if $(MOD_NAME),$(MOD_NAME)/)include
cppflags  += $(if $(CPPFLAGS), $(CPPFLAGS))
 ldflags  := -L$(TOPDIR)
 ldflags  += $(if $(MOD_NAME),$(MOD_NAME)/)$(if $(LDFLAGS), $(LDFLAGS))
modules    := $(mods)
makeflags  := --no-print-directory
makeflags  += MOD_NAME="$(if $(MOD_NAME),$(MOD_NAME)/)$(strip $(1))"
buildflags := MODS="$(modules)" CPPFLAGS="$(cppflags)" LDFLAGS="$(ldflags)"
endef

# usage: module_build <mod>
define module_build
$(strip $(1)): FORCE
	$(call log, info, MAKE, $(if $(MOD_NAME),$(MOD_NAME)/)$(strip $(1)))
	@$(MAKE)$(if $(makeflags), $(makeflags)) -C $$@ $(buildflags)
$(strip $(1))-install:
	$(call log, info, INSTALL, $(if $(MOD_NAME),$(MOD_NAME)/)$(strip $(1)))
	@$(MAKE)$(if $(makeflags), $(makeflags)) install -C $(strip $(1))
$(strip $(1))-uninstall:
	$(call log, info, UNINSTALL, $(if $(MOD_NAME),$(MOD_NAME)/)$(strip $(1)))
	@$(MAKE)$(if $(makeflags), $(makeflags)) uninstall -C $(strip $(1))
$(strip $(1))-clean:
	$(call log, info, CLEAN, $(if $(MOD_NAME),$(MOD_NAME)/)$(strip $(1)))
	@$(MAKE)$(if $(makeflags), $(makeflags)) clean -C $(strip $(1))
endef

# usage: module_target <mod> <target>
define module_target
$$(shell $(SCRIPTS_HOME)/build-target.sh $1 $2)
endef

# =========================================================================== #

# usage: library_share_perpare <target>
define library_share_perpare
  shlibs += lib$(strip $(1)).so
    objs := $(if $($(strip $(1))-objs), $($(strip $(1))-objs), $(strip $(1)).o)
  cflags := -fPIC$(if $(CFLAGS), $(CFLAGS))
  cflags += $(if $(shlib-cflags), $(shlib-cflags))
  cflags += $(if $($(strip $(1))-cflags), $($(strip $(1))-cflags))
cppflags := -Iinclude$(if $(CPPFLAGS), $(CPPFLAGS))
cppflags += $(if $(shlib-cppflags), $(shlib-cppflags))
cppflags += $(if $($(strip $(1))-cppflags), $($(strip $(1))-cppflags))
 ldflags := $(if $(LDFLAGS), $(LDFLAGS))
 ldflags += $(if $(shlib-ldflags), $(shlib-ldflags))
 ldflags += $(if $($(strip $(1))-ldflags), $($(strip $(1))-ldflags))
    libs := $(if $(LIBS), $(LIBS))
    libs += $(if $(shlib-libs), $(shlib-libs))
    libs += $(if $($(strip $(1))-libs), $($(strip $(1))-libs))
mod-libs += -l$(strip $(1))
endef
# usage: library_share_build <target>
define library_share_build
$(objs): %.o: %.c
	$(call log, info, CC, $(if $(MOD_NAME),$(MOD_NAME)/)$$@)
	@$(CC) -c$(if $(cflags), $(cflags))$(if $(cppflags), $(cppflags)) $$<
lib$(strip $(1)).so: $(objs)
	$(call log, info, LD, $(if $(MOD_NAME),$(MOD_NAME)/)$$@)
	@$(CC)$(if $(cflags), $(cflags))$(if $(ldflags), $(ldflags)) -shared -o $$@ $$^$(if $(libs), $(libs))
endef

# usage: library_static_perpare <target>
define library_static_perpare
  stlibs += lib$(strip $(1)).a
    objs := $(if $($(strip $(1))-objs), $($(strip $(1))-objs), $(strip $(1)).o)
  cflags := $(if $(CFLAGS), $(CFLAGS))$(if $(stlib-cflags), $(stlib-cflags))
  cflags += $(if $($(strip $(1))-cflags), $($(strip $(1))-cflags))
cppflags := -Iinclude$(if $(CPPFLAGS), $(CPPFLAGS))
cppflags += $(if $(stlib-cppflags), $(stlib-cppflags))
cppflags += $(if $($(strip $(1))-cppflags), $($(strip $(1))-cppflags))
 ldflags := $(if $(LDFLAGS), $(LDFLAGS))
 ldflags += $(if $(stlib-ldflags), $(stlib-ldflags))
 ldflags += $(if $($(strip $(1))-ldflags), $($(strip $(1))-ldflags))
    libs := $(if $(LIBS), $(LIBS))
    libs += $(if $(stlib-libs), $(stlib-libs))
	libs += $(if $($(strip $(1))-libs), $($(strip $(1))-libs))
mod-libs += -l$(strip $(1))
endef
# usage: library_static_build <target>
define library_static_build
$(objs): %.o: %.c
	$(call log, info, CC, $(if $(MOD_NAME),$(MOD_NAME)/)$$@)
	@$(CC) -c$(if $(cflags), $(cflags))$(if $(cppflags), $(cppflags)) $$<
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

# usage: object_relocatable_perpare <target>
define object_relocatable_perpare
   relos += $(strip $(1)).o
    objs := $(if $($(strip $(1))-objs), $($(strip $(1))-objs), $(strip $(1)).o)
  cflags := $(if $(CFLAGS), $(CFLAGS))
  cflags += $(if $(relo-cflags), $(relo-cflags))
  cflags += $(if $($(strip $(1))-cflags), $($(strip $(1))-cflags))
cppflags := -Iinclude$(if $(CPPFLAGS), $(CPPFLAGS))
cppflags += $(if $(relo-cppflags), $(relo-cppflags))
cppflags += $(if $($(strip $(1))-cppflags), $($(strip $(1))-cppflags))
 ldflags := -L.$(if $(LDFLAGS), $(LDFLAGS))
 ldflags += $(if $(relo-ldflags), $(relo-ldflags))
 ldflags += $(if $($(strip $(1))-ldflags), $($(strip $(1))-ldflags))
   libs  := $(if $(LIBS), $(LIBS))
   libs  += $(if $(relo-libs), $(relo-libs))
   libs  += $(if $($(strip $(1))-libs), $($(strip $(1))-libs))
endef
# usage: object_relocatable_build <taregt>
define object_relocatable_build
$(objs): %.o: %.c
	$(call log, info, CC, $(if $(MOD_NAME),$(MOD_NAME)/)$$@)
	@$(CC) -c$(if $(cflags), $(cflags))$(if $(cppflags), $(cppflags)) $$<
$(strip $(1)).o: $(objs)
	$(call log, info, LD, $(if $(MOD_NAME),$(MOD_NAME)/)$$@)
	@$(LD) --no-gc-sections -r $$^ -o $$@
endef

# usage: object_executable_perpare
define object_executable_perpare
   execs += $(strip $(1))
    objs := $(if $($(strip $(1))-objs), $($(strip $(1))-objs), $(strip $(1)).o)
  cflags := $(if $(CFLAGS), $(CFLAGS))$(if $(exec-cflags), $(exec-cflags))
  cflags += $(if $($(strip $(1))-cflags), $($(strip $(1))-cflags))
cppflags := -Iinclude$(if $(CPPFLAGS), $(CPPFLAGS))
cppflags += $(if $(exec-cppflags), $(exec-cppflags))
cppflags += $(if $($(strip $(1))-cppflags), $($(strip $(1))-cppflags))
 ldflags := $(if $(LDFLAGS), $(LDFLAGS))
 ldflags += $(if $(mod-ldflags), $(mod-ldflags))
 ldflags += $(if $(exec-ldflags), $(exec-ldflags))
 ldflags += $(if $($(strip $(1))-ldflags), $($(strip $(1))-ldflags))
    libs := $(if $(LIBS), $(LIBS))$(if $(mod-libs), $(mod-libs))
    libs += $(if $(exec-libs), $(exec-libs))
    libs += $(if $($(strip $(1))-libs), $($(strip $(1))-libs))
mod-objs := $(foreach mod, $(mods),$$(call module_target,$(mod), relos))
endef
# usage: object_executable_build <target>
define object_executable_build
$(objs): %.o: %.c
	$(call log, info, CC, $(if $(MOD_NAME),$(MOD_NAME)/)$$@)
	@$(CC) -c$(if $(cflags), $(cflags))$(if $(cppflags), $(cppflags)) $$<
$(1): $(objs) $(mod-objs)
	$(call log, info, LD, $(if $(MOD_NAME),$(MOD_NAME)/)$$@)
	@$(CC)$(if $(cflags), $(cflags))$(if $(ldflags), $(ldflags)) -o $$@ $(objs)$(if $(mod-objs), $(mod-objs))$(if $(libs), $(libs))
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
type   := $(strip $(1))/$(strip $(2))
target := $(strip $(3))
endef
# usage: perpare <type> <target> <name>
define build
$(if $(findstring $(strip $(1)), module library object), ,$(error Not support this type:$(strip $(1))))
$(eval $(call perpare, $(1), $(2), $(3)))
$(eval $(call $(strip $(1))_perpare, $(2), $(3)))
$(eval $(call $(strip $(1))_build,   $(2), $(3)))
endef


