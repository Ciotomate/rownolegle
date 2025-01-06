#include <pthread.h>
#include <stdio.h>


static pthread_mutex_t bariera_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t bariera_cond = PTHREAD_COND_INITIALIZER;
static int thread_count = 0; 
static int waiting_threads = 0; 


void bariera_init(int count) {
    pthread_mutex_lock(&bariera_mutex);
    thread_count = count;
    waiting_threads = 0;
    pthread_mutex_unlock(&bariera_mutex);
}


void bariera(void) {
    pthread_mutex_lock(&bariera_mutex);

    waiting_threads++;
    if (waiting_threads < thread_count) {
        pthread_cond_wait(&bariera_cond, &bariera_mutex);
    } else {
        waiting_threads = 0;
        pthread_cond_broadcast(&bariera_cond);
    }

    pthread_mutex_unlock(&bariera_mutex);
}

