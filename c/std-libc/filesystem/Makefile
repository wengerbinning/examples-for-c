


all: file

%.o: %.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $<
	@echo "[CC] $@"


file: file_open.o file.o
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)
	@echo "[LD] $@"



clean:
	-rm -rf *.o