#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "czytelnia.h"


#define MY_DEBUG


int chce_czytac(czytelnia_t *czytelnia_p)
{
  pthread_mutex_lock(&czytelnia_p->mutex);

  while (czytelnia_p->pisarze > 0 || czytelnia_p->pisarze_czekaj > 0)
  {
    czytelnia_p->czytelnicy_czekaj++;
    pthread_cond_wait(&czytelnia_p->czyt_cond, &czytelnia_p->mutex);
    czytelnia_p->czytelnicy_czekaj--;
  }

  czytelnia_p->czytelnicy++;
  pthread_mutex_unlock(&czytelnia_p->mutex);
  return 0;
}

int koncze_czytac(czytelnia_t *czytelnia_p)
{
  pthread_mutex_lock(&czytelnia_p->mutex);

  czytelnia_p->czytelnicy--;
  if (czytelnia_p->czytelnicy == 0)
  {
    pthread_cond_broadcast(&czytelnia_p->pisz_cond);
  }

  pthread_mutex_unlock(&czytelnia_p->mutex);
  return 0;
}

int chce_pisac(czytelnia_t *czytelnia_p)
{
  pthread_mutex_lock(&czytelnia_p->mutex);

  while (czytelnia_p->czytelnicy > 0 || czytelnia_p->pisarze > 0)
  {
    czytelnia_p->pisarze_czekaj++;
    pthread_cond_wait(&czytelnia_p->pisz_cond, &czytelnia_p->mutex);
    czytelnia_p->pisarze_czekaj--;
  }

  czytelnia_p->pisarze++;
  pthread_mutex_unlock(&czytelnia_p->mutex);
  return 0;
}

int koncze_pisac(czytelnia_t *czytelnia_p)
{
  pthread_mutex_lock(&czytelnia_p->mutex);

  czytelnia_p->pisarze--;

  if (czytelnia_p->pisarze_czekaj > 0)
  {
    pthread_cond_signal(&czytelnia_p->pisz_cond);
  }
  else
  {
    pthread_cond_broadcast(&czytelnia_p->czyt_cond);
  }

  pthread_mutex_unlock(&czytelnia_p->mutex);
  return 0;
}

void inicjuj(czytelnia_t *czytelnia_p)
{
  czytelnia_p->czytelnicy = 0;
  czytelnia_p->pisarze = 0;
  czytelnia_p->czytelnicy_czekaj = 0;
  czytelnia_p->pisarze_czekaj = 0;


  pthread_cond_init(&czytelnia_p->czyt_cond, NULL);
  pthread_cond_init(&czytelnia_p->pisz_cond, NULL);
  pthread_mutex_init(&czytelnia_p->mutex, NULL);
}

void czytam(czytelnia_t *czytelnia_p)
{
  pthread_mutex_lock(&czytelnia_p->mutex);

  #ifdef MY_DEBUG
    printf("\tobecnie czytam, teraz czyta: %d, pisze: %d\n", czytelnia_p->czytelnicy, czytelnia_p->pisarze);
    if (czytelnia_p->pisarze > 0 || czytelnia_p->czytelnicy < 0 || czytelnia_p->pisarze < 0)
    {
      printf("\t\t\tczytam - blad\n");
      exit(1);
    }
  #endif

  pthread_mutex_unlock(&czytelnia_p->mutex);
  usleep(rand() % 300000);
}

void pisze(czytelnia_t *czytelnia_p)
{
  pthread_mutex_lock(&czytelnia_p->mutex);

  #ifdef MY_DEBUG
      printf("\tobecnie pisze, teraz czyta: %d, pisze: %d\n", czytelnia_p->czytelnicy, czytelnia_p->pisarze);
      if (czytelnia_p->pisarze > 1 || czytelnia_p->czytelnicy > 0 || czytelnia_p->pisarze < 0 || czytelnia_p->czytelnicy < 0)
      {
          printf("\t\t\tpisze - blad\n");
          exit(1);
      }
  #endif

  pthread_mutex_unlock(&czytelnia_p->mutex);
  usleep(rand() % 300000);
}
