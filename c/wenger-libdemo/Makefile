DESTDIR=/usr/local
prefix=/

all: demo


%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<
    

demo: demo.h demo.o
	$(CC) -shared -fPIC -o libdemo.so demo.o    

demo-a: demo.h demo-a.o
	$(CC) -shared -fPIC -o libdemo.so demo-a.o

clean:
	-rm -f *.o *.so

distclean: clean

install: demo
	install -D -m 664 demo.h	$(DESTDIR)$(prefix)/include/demo.h
	install -D -m 755 libdemo.so $(DESTDIR)$(prefix)/lib/libdemo.so
	install -D -m 664 demo.pc $(DESTDIR)$(prefix)/lib/pkgconfig/demo.pc

uninstall:
	-rm -f $(DESTDIR)$(prefix)/include/demo.h
	-rm -f $(DESTDIR)$(prefix)/lib/libdemo.so
	-rm -f $(DESTDIR)$(prefix)/lib/pkgconfig/demo.pc

.PHONY: all clean install uninstall
