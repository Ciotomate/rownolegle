#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "czytelnia.h"

// Initialize the monitor
void inicjuj(cz_t* cz_p) {
    cz_p->readers = 0;
    cz_p->writers = 0;
    cz_p->waiting_writers = 0;
    pthread_mutex_init(&cz_p->mutex, NULL);
    pthread_cond_init(&cz_p->can_read, NULL);
    pthread_cond_init(&cz_p->can_write, NULL);
}

// Reader start
void start_read(cz_t* cz_p) {
    pthread_mutex_lock(&cz_p->mutex);

    // Wait if a writer is active or writers are waiting
    while (cz_p->writers > 0 || cz_p->waiting_writers > 0) {
        pthread_cond_wait(&cz_p->can_read, &cz_p->mutex);
    }

    // Increment the count of active readers
    cz_p->readers++;
    pthread_mutex_unlock(&cz_p->mutex);
}

// Reader end
void end_read(cz_t* cz_p) {
    pthread_mutex_lock(&cz_p->mutex);

    // Decrement the count of active readers
    cz_p->readers--;

    // Signal writers if no readers are left
    if (cz_p->readers == 0) {
        pthread_cond_signal(&cz_p->can_write);
    }

    pthread_mutex_unlock(&cz_p->mutex);
}

// Writer start
void start_write(cz_t* cz_p) {
    pthread_mutex_lock(&cz_p->mutex);

    // Increment the count of waiting writers
    cz_p->waiting_writers++;

    // Wait if any readers or writers are active
    while (cz_p->readers > 0 || cz_p->writers > 0) {
        pthread_cond_wait(&cz_p->can_write, &cz_p->mutex);
    }

    // Writer becomes active
    cz_p->waiting_writers--;
    cz_p->writers++;

    pthread_mutex_unlock(&cz_p->mutex);
}

// Writer end
void end_write(cz_t* cz_p) {
    pthread_mutex_lock(&cz_p->mutex);

    // Mark writer as finished
    cz_p->writers--;

    // Signal readers or writers
    if (cz_p->waiting_writers > 0) {
        pthread_cond_signal(&cz_p->can_write);
    } else {
        pthread_cond_broadcast(&cz_p->can_read);
    }

    pthread_mutex_unlock(&cz_p->mutex);
}

// Reader simulation
void czytam(cz_t* cz_p) {
    start_read(cz_p);

    // Simulate reading
    printf("Reader is reading...\n");
    usleep(rand() % 1000000);

    end_read(cz_p);
}

// Writer simulation
void pisze(cz_t* cz_p) {
    start_write(cz_p);

    // Simulate writing
    printf("Writer is writing...\n");
    usleep(rand() % 1000000);

    end_write(cz_p);
}


