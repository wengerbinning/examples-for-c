#include <time.h>
#include <pthread.h>
#include <unistd.h>

#include "develop.h"
#include "thread.h"
#include "buffer.h"
#include "download.h"

static pthread_t thread;
static download_t download;
static buffer_t buf;

#define BLKIZE 1

int main (int argc, const char *argv[]) {
	url_t *url;
	block_t block[BLKIZE];
	int i;


	INIT_LIST_HEAD(&buf.blk_list);

	for (i=0; i < BLKIZE; i++) {
		block[i].size = BUFIZE;
		list_add_tail(&block[i].list, &buf.blk_list);
		devel_debug("block: %p, size %d", &block[i], block[i].size);
		buf.count++;
	}

	buf.blk = &block[0];
	devel_debug("buffer %p, block count %d", &buf, buf.count);

	pthread_mutex_init(&download.mutex, NULL);

	if ( 0 != pthread_create(&thread, NULL, thread_task, &download)) {
		devel_info("crate thread is error!");
	}


	sleep(1);
	url = url_new("http://127.0.0.1");
	pthread_mutex_lock(&download.mutex);
	download.url = url;
	download.flags |= DOWNF_BUFFER;
	download.buffer = &buf;
	pthread_mutex_unlock(&download.mutex);





	devel_info("Wait for thread ...");
	pthread_join(thread , NULL);
	devel_info("thread exit");
	return 0;
}
