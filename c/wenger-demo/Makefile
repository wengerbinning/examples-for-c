
all: demo


%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

demo: demo.o
	$(CC) ${LDFLAGS} ${LIBS} -o $@ $<

clean:
	-rm -f demo *.o 

.PHONY: all clean
