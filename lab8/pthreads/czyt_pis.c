#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "czytelnia.h"

void *funkcja_czytelnika(void *);
void *funkcja_pisarza(void *);

int main()
{

  int i;
  pthread_t pisarze[5], czytelnicy[10];
  int indeksy[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  czytelnia_t czytelnia;

  inicjuj(&czytelnia);

  for (i = 0; i < 5; i++)
  {
    pthread_create(&pisarze[i], NULL, funkcja_pisarza, (void *)&czytelnia);
  }
  for (i = 0; i < 10; i++)
  {
    pthread_create(&czytelnicy[i], NULL, funkcja_czytelnika, (void *)&czytelnia);
  }
  for (i = 0; i < 5; i++)
  {
    pthread_join(pisarze[i], NULL);
  }
  for (i = 0; i < 10; i++)
  {
    pthread_join(czytelnicy[i], NULL);
  }
}

void *funkcja_czytelnika(void *arg)
{

  czytelnia_t *cz_p = (czytelnia_t *)arg;

  for (;;)
  {

    usleep(rand() % 1000000);
    printf("czytelnik %lu - przed zamkiem\n", pthread_self());

    chce_czytac(cz_p);

    // korzystanie z zasobow czytelni
    printf("czytelnik %lu - wchodze\n", pthread_self());

    czytam(cz_p);

    printf("czytelnik %lu - wychodze\n", pthread_self());

    koncze_czytac(cz_p);

    printf("czytelnik %lu - po zamku\n", pthread_self());
  }
}

void *funkcja_pisarza(void *arg)
{

  czytelnia_t *cz_p = (czytelnia_t *)arg;

  for (;;)
  {

    usleep(rand() % 3000000);
    printf("pisarz %lu - przed zamkiem\n", pthread_self());

    chce_pisac(cz_p);

    // korzystanie z zasobow czytelni
    printf("pisarz %lu - wchodze\n", pthread_self());

    pisze(cz_p);

    printf("pisarz %lu - wychodze\n", pthread_self());

    koncze_pisac(cz_p);

    printf("pisarz %lu - po zamku\n", pthread_self());
  }
}
