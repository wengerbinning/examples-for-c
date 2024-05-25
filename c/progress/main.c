

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>


#define PROG_PID "./prog.pid"
#define BUFIZE 16

#define PROG_LOCK prog_lock()
bool prog_lock (void) {
	int fd;
	char buffer[BUFIZE + 1];
	int ret;

	if (0 < access(PROG_PID, X_OK);

	printf("ret: %d\n", ret);


	fd = open(PROG_PID, O_RDWR | O_CREAT);
	printf("Open %s in %d ...\n", PROG_PID, fd);
	memset(buffer, 0, sizeof(buffer));
	snprintf(buffer, BUFIZE, "%d", getpid());
	write(fd, buffer, strlen(buffer));

	close(fd);

	return true;
}



void prog_unlock (void) {
	if (0 < access(PROG_PID, F_OK))
		remove(PROG_PID);
}

int main (int argc, char *argv[]) {

	if ( !prog_lock() )
		return 0;

	printf("Start worker ...\n");
	sleep(10);
	printf("Worker Finished!\n");

	prog_unlock();
	return 0;
}