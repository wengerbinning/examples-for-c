all: helloworld
	echo "Build all"
	echo build $@
	echo depends $^
	

helloworld: helloworld.o helloworld.c
	echo $<.c
	$(CC) -o helloworld helloworld.o
clean:
	-rm *.o
	echo "Clean is over!"
