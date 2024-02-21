
_all: build_programs


%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $^


# usage: prog_rule <prog>
define prog_rule
PROG_LIST += $(addprefix bin/, $(1))
$(addprefix bin/, $(1)): $($(addsuffix -objs, $(1)))
	@echo LD $$@
	@$(CC) $(LDFLAGS) $(LIBS) -o $$@ $$^
endef

$(foreach prog, $(programs), $(eval $(call prog_rule, $(prog))))

build_programs: $(PROG_LIST)
	@echo Build programs: $^

.PHONY += _all build_programs
