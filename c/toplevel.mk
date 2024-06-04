
$(eval $(foreach mod,$(dirs),$(call build, module, $(mod))))

##
all: $(dirs) $(stlibs) $(shlibs) $(progs)

##
clean: FORCE $(modules-clean)
	-rm -f *.o
	-rm -f $(stlibs) $(shlibs) $(progs)

##
install: $(dirs) $(progs) FORCE
	install -d $(DESTDIR)/$(bin)
	install -t $(DESTDIR)/$(bin) $(progs)

##
unistall:
	-rm -rf $(DESTDIR)/$(bin)

##
.PHONY: all clean install $(dirs) $(modules-clean) FORCE
FORCE: