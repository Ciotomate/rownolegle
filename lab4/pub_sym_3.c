#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define ILE_MUSZE_WYPIC 3

int liczba_kufli;

pthread_mutex_t mutex_kufel, mutex_kran;

void *watek_klient(void *arg);

int main(void) {
    pthread_t *tab_klient;
    int *tab_klient_id;

    int l_kl, l_kf, i;

    pthread_mutex_init(&mutex_kufel, NULL);
    pthread_mutex_init(&mutex_kran, NULL);

    printf("\nLiczba klientow: ");
    scanf("%d", &l_kl);

    printf("\nLiczba kufli: ");
    scanf("%d", &l_kf);

    liczba_kufli = l_kf;

    printf("L. Kufli początkowo: %d\n", liczba_kufli);

    tab_klient = (pthread_t *)malloc(l_kl * sizeof(pthread_t));
    tab_klient_id = (int *)malloc(l_kl * sizeof(int));
    for (i = 0; i < l_kl; i++) tab_klient_id[i] = i;

    printf("\nOtwieramy pub (simple)!\n");
    printf("\nLiczba wolnych kufli %d\n", l_kf);

    for (i = 0; i < l_kl; i++) {
        pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]);
    }
    for (i = 0; i < l_kl; i++) {
        pthread_join(tab_klient[i], NULL);
    }
    printf("\nZamykamy pub!\n");
    printf("L. Kufli na końcu: %d\n", liczba_kufli);


    return 0;
}

void *watek_klient(void *arg_wsk) {
    int moj_id = *((int *)arg_wsk);
    int ile_musze_wypic = ILE_MUSZE_WYPIC;
    long int wykonana_praca = 0;

    for (int i = 0; i < ile_musze_wypic; i++) {
        int success = 0;

        // Próba zdobycia kufla
        while (!success) {
            if (pthread_mutex_trylock(&mutex_kufel) == 0) {
                if (liczba_kufli > 0) {
                    liczba_kufli--;
                    pthread_mutex_unlock(&mutex_kufel);
                    success = 1;
                } else {
                    pthread_mutex_unlock(&mutex_kufel);
                }
            } else {
                // Jeśli nie udało się zdobyć kufla, "pracuj" (zliczanie pracy)
                wykonana_praca++;
                usleep(10); // Symulacja pracy podczas oczekiwania
            }
        }

        // Nalewanie i picie
        pthread_mutex_lock(&mutex_kran);
        usleep(30); // Symulacja nalewania
        pthread_mutex_unlock(&mutex_kran);

        nanosleep((struct timespec[]){{0, 50000000L}}, NULL); // Symulacja picia

        // Odkładanie kufla
        pthread_mutex_lock(&mutex_kufel);
        liczba_kufli++;
        pthread_mutex_unlock(&mutex_kufel);
    }

    printf("Klient %d, wykonana praca w trakcie oczekiwania: %ld \n", moj_id, wykonana_praca);
    return NULL;
}
