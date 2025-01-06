#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "czytelnia.h"

// Function declarations
void* funkcja_pisarza(void* arg);
void* funkcja_czytelnika(void* arg);

#define NUM_READERS 10
#define NUM_WRITERS 5

pthread_t czytelnicy[NUM_READERS];
pthread_t pisarze[NUM_WRITERS];

int main() {
    cz_t czytelnia;
    inicjuj(&czytelnia);

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_create(&pisarze[i], NULL, funkcja_pisarza, (void*)&czytelnia);
    }
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_create(&czytelnicy[i], NULL, funkcja_czytelnika, (void*)&czytelnia);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(pisarze[i], NULL);
    }
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(czytelnicy[i], NULL);
    }

    return 0;
}

void* funkcja_czytelnika(void* arg) {
    cz_t* cz_p = (cz_t*)arg;

    for (;;) {
        usleep(rand() % 1000000);
        printf("czytelnik %lu - przed zamkiem\n", pthread_self());

        my_read_lock_lock(cz_p);

        // Accessing shared resources
        printf("czytelnik %lu - wchodze\n", pthread_self());
        czytam(cz_p);
        printf("czytelnik %lu - wychodze\n", pthread_self());

        my_read_lock_unlock(cz_p);

        printf("czytelnik %lu - po zamku\n", pthread_self());
    }

    return NULL;
}

void* funkcja_pisarza(void* arg) {
    cz_t* cz_p = (cz_t*)arg;

    for (;;) {
        usleep(rand() % 3000000);
        printf("pisarz %lu - przed zamkiem\n", pthread_self());

        my_write_lock_lock(cz_p);

        // Accessing shared resources
        printf("pisarz %lu - wchodze\n", pthread_self());
        pisze(cz_p);
        printf("pisarz %lu - wychodze\n", pthread_self());

        my_write_lock_unlock(cz_p);

        printf("pisarz %lu - po zamku\n", pthread_self());
    }

    return NULL;
}


