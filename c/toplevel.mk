
$(eval $(foreach mod,$(mdirs),$(call build, module, $(mod))))

##
all: $(mdirs) $(stlibs) $(shlibs) $(progs)

##
clean: FORCE $(modules-clean)
	-rm -f *.o
	-rm -f $(stlibs) $(shlibs) $(progs)

##
install: $(modules-install) $(progs) FORCE
	install -d $(DESTDIR)/$(bin)
	install -t $(DESTDIR)/$(bin) $(progs)

##
unistall: $(modules-uninstall) FORCE
	-rm -rf $(DESTDIR)/$(bin)

##
.PHONY: all clean install unistall $(mdirs) $(modules-clean) $(modules-install) $(modules-uninstall) FORCE
FORCE: