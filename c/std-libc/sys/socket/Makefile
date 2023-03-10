
PROJECT =../../..

CFLAGS = -g

CXX=
CXXFLAGS=

ECHO = echo

CPPFLAGS = -I$(PROJECT)/include
LDFLAGS=

LIBS=

all: socket data


LIBS = 



data: data.o
	@$(ECHO) [LD] $@
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)	

socket: socket.o
	@$(ECHO) [LD] $@
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	@$(ECHO) [CC] $^
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $^

clean:
	@rm -rf *.o



