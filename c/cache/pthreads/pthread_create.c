#include <stdio.h>
#include <time.h>
#include <pthread.h>

pthread_t ntid;

void * thread_print (void *arg) {
    
    printf("Now is thread ID: %lu\n", pthread_self());
    
    return NULL;
}

int main(int argc, const char **argv) {

    
    if ( 0 != pthread_create(&ntid, NULL, thread_print, NULL)) {
    	printf("crate thread is error!\n");
    }
    sleep(3);
    return 0;
}
