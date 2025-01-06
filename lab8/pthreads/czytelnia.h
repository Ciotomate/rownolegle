#ifndef _czytelnia_
#define _czytelnia_

/*** Definicje typow zmiennych ***/
typedef struct
{
  int czytelnicy;
  int pisarze;
  int czytelnicy_czekaj;
  int pisarze_czekaj;
  pthread_cond_t czyt_cond;
  pthread_cond_t pisz_cond;
  pthread_mutex_t mutex;
} czytelnia_t;

/*** Deklaracje procedur interfejsu ***/
void inicjuj(czytelnia_t *czytelnia_p);
void czytam(czytelnia_t *czytelnia_p);
void pisze(czytelnia_t *czytelnia_p);

int chce_czytac(czytelnia_t *czytelnia_p);
int koncze_czytac(czytelnia_t *czytelnia_p);
int chce_pisac(czytelnia_t *czytelnia_p);
int koncze_pisac(czytelnia_t *czytelnia_p);

#endif
