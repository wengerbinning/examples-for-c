#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "worker.h"

#define WORK_PID "worker.pid"
#define BUFIZE 64


bool work_lock (bool force) {
	int fd, pid;
	char buffer[BUFIZE + 1];

	if ((access(WORK_PID, F_OK) >= 0) && !force) {
		if ((fd = open(WORK_PID, S_IRUSR)) < 0)
			return false;

		memset(buffer, 0, sizeof(buffer));
		read(fd, buffer, BUFIZE);
		sscanf(buffer, "%d", &pid);

		if (pid == getpid())
			return true;

		return false;
	}

	if ((fd = creat(WORK_PID, S_IRUSR | S_IWUSR)) < 0)
		return false;

	memset(buffer, 0, sizeof(buffer));
	snprintf(buffer, BUFIZE, "%d", getpid());
	write(fd, buffer, sizeof(buffer));

	close(fd);

	return true;
}

void work_unlock (bool force) {
	
	int fd, pid;
	char buffer[BUFIZE + 1];	
	
	if (access(WORK_PID, F_OK) < 0)
		return;

	if (((fd = open(WORK_PID, S_IRUSR)) < 0) && !force)
		return;

	memset(buffer, 0, sizeof(buffer));
	read(fd, buffer, BUFIZE);
	sscanf(buffer, "%d", &pid);

	if ((pid != getpid()) && !force)
		return;

	remove(WORK_PID);
}

int main (int argc, const char *argv[]) {

	int ret;
	if (!(ret = work_lock(false)))
		return -WORKE_BUSY;

	printf("Worker start in %d from %d...\n", getpid(), getppid());


	sleep(3);

	printf("Worker finished.\n");
	work_unlock(false);
    return 0;
}