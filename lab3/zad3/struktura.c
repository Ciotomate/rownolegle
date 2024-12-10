#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    double poczatek;  
    double koniec;    
    double wynik;     
} DaneFragmentu;


void* funkcja_watku(void* argument) {
    DaneFragmentu* dane = (DaneFragmentu*) argument;
    
    // Obliczanie średniej jako przykład operacji
    dane->wynik = (dane->poczatek + dane->koniec) / 2.0;

    printf("Wątek: %ld, Fragment: (%.2f, %.2f), Wynik: %.2f\n",
           pthread_self(), dane->poczatek, dane->koniec, dane->wynik);

    pthread_exit(NULL);
}

int main() {
    double a = 0.0, b = 10.0;      
    int liczba_watkow = 4;         


    pthread_t watki[liczba_watkow];

    DaneFragmentu fragmenty[liczba_watkow];

    double dlugosc_fragmentu = (b - a) / liczba_watkow;

    // Tworzenie wątków
    for (int i = 0; i < liczba_watkow; i++) {
        fragmenty[i].poczatek = a + i * dlugosc_fragmentu;
        fragmenty[i].koniec = fragmenty[i].poczatek + dlugosc_fragmentu;
        fragmenty[i].wynik = 0.0;

        pthread_create(&watki[i], NULL, funkcja_watku, &fragmenty[i]);
    }

    // Oczekiwanie na zakończenie pracy wątków
    for (int i = 0; i < liczba_watkow; i++) {
        pthread_join(watki[i], NULL);
    }

    double suma_wynikow = 0.0;
    for (int i = 0; i < liczba_watkow; i++) {
        suma_wynikow += fragmenty[i].wynik;
    }

    printf("Suma wyników: %.2f\n", suma_wynikow);

    return 0;
}

