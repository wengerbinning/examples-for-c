CC := gcc
ECHO ?= echo
CFLAGS ?= -g
CPPFLAGS += -Iinclude/
LDFLAGS +=
LIBS :=


tlibs :=

slibs :=
slibs-cflags := -fPIC
slibs-ldflags :=
progs :=
progs-libs :=
progs-cflags := -Wl,-rpath=./
progs-ldflags := -L./

all:

##
define log
echo $2
endef

define perpare
build_type   := $(strip $(1))
build_target := $(strip $(2))
endef
#
define slibs_perpare
slibs += lib$(strip $(1)).so
progs-libs += -l$(strip $(1))
objs := $(if $($(strip $(1))-objs), $($(strip $(1))-objs), $(strip $(1)).o)
cflags   := $(CFLAGS) $(slibs-cflags) $($(strip $(1))-cflags)
cppflags = $(CPPFLAGS) $(slibs-cppflags) $($(strip $(1))-cppflags)
ldflags  := $(LDFLAGS) $(slibs-ldflags) $($(strip $(1))-ldflags)
libs  := $(LIBS) $(slibs-libs) $($(strip $(1))-libs)
endef
#
define progs_perpare
progs += $(strip $(1))
objs  := $(if $($(strip $(1))-objs), $($(strip $(1))-objs), $(strip $(1)).o)
cflags   := $(CFLAGS) $(progs-cflags) $($(strip $(1))-cflags)
cppflags = $(CPPFLAGS) $(progs-cppflags) $($(strip $(1))-cppflags)
ldflags  := $(LDFLAGS) $(progs-ldflags) $($(strip $(1))-ldflags)
libs  := $(LIBS) $(progs-libs) $($(strip $(1))-libs)
endef

##
%.o: %.c
	@$(call log,info,[CC] $@)
	@$(CC) -c $(cflags) $(cppflags) $<

#
define slibs_build
lib$(strip $(1)).so: $(objs)
	@$(call log,info,[LD] lib$(strip $(1)).so)
	@$(CC) $(cflags) $(ldflags) -shared -o lib$(strip $(1)).so $(objs) $(libs)
endef

#
define progs_build
$(1): $(objs)
	@$(call log,info,[LD] $(1))
	@$(CC) $(cflags) $(ldflags) -o $(1) $(objs) $(libs)
endef

define build
$(if $(findstring $(strip $(1)), progs slibs tlibs),, $(error Not support this type:$(strip $(1))))
$(eval $(call perpare, $(1), $(2)))
$(eval $(call $(strip $(1))_perpare, $(2)))
$(eval $(call $(strip $(1))_build, $(2)))
endef

##
$(eval $(call build, slibs, center))

##
worker-objs := main.o
$(eval $(call build,progs,worker))

##
all: $(tlibs) $(slibs) $(progs)

clean:
	-rm -f *.o
	-rm -f $(tlibs) $(slibs)
	-rm -f $(progs)

.PHONY: all clean

