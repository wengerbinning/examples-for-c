
version-objs:= version.o


all: init bin/version

init:
	mkdir -p bin

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

bin/version: $(version-objs)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@ $< 

clean:
	-rm -f bin/version $(version-objs)
	@rm -rf bin

.PHONY: all init clean
