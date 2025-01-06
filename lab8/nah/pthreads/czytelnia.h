#ifndef _czytelnia_
#define _czytelnia_

#include <pthread.h>

/*** Structure Definition ***/
typedef struct {
    int readers;             // Number of active readers
    int writers;             // Number of active writers
    int waiting_writers;     // Number of waiting writers
    pthread_mutex_t mutex;   // Mutex for synchronization
    pthread_cond_t can_read; // Condition variable for readers
    pthread_cond_t can_write;// Condition variable for writers
} cz_t;

/*** Function Declarations ***/
void inicjuj(cz_t* czytelnia_p);
void czytam(cz_t* czytelnia_p);
void pisze(cz_t* czytelnia_p);

void start_read(cz_t* czytelnia_p);
void end_read(cz_t* czytelnia_p);
void start_write(cz_t* czytelnia_p);
void end_write(cz_t* czytelnia_p);

int my_read_lock_lock(cz_t* czytelnia_p);
int my_read_lock_unlock(cz_t* czytelnia_p);
int my_write_lock_lock(cz_t* czytelnia_p);
int my_write_lock_unlock(cz_t* czytelnia_p);


#endif

