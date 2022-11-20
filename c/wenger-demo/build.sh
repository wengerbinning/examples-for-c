
make CFLAGS=$(pkg-config --cflags demo) LDFLAGS=$(pkg-config --libs-only-L demo) LIBS=$(pkg-config --libs-only-l demo)

