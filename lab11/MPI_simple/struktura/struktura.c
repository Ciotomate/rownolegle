#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include "mpi.h"

struct My_struct {
    char name[7];  // 7B (6 znaków + '\0')
    int age;       // 4B
    float height;  // 4B
};

int main( int argc, char** argv ){ 
  
    int rank, ranksent, size, source, dest, tag; 
    MPI_Status status;
  
    MPI_Init( &argc, &argv ); 
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );  
    MPI_Comm_size( MPI_COMM_WORLD, &size );
  
    int size_struct; // Zliczanie rozmiaru pojedynczego pola w strukturze
    int packet_size; // Rozmiar bufora i paczki, którą będziemy wysyłać
    int position = 0; // Zapisanie gdzie skończyliśmy w buforze

    MPI_Pack_size(7, MPI_CHAR, MPI_COMM_WORLD, &size_struct); // 7 znaków w tablicy
    packet_size = size_struct;
    MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &size_struct);
    packet_size += size_struct; // Sumowanie rozmiaru podstruktur
    MPI_Pack_size(1, MPI_FLOAT, MPI_COMM_WORLD, &size_struct);
    packet_size += size_struct;

    // Alokacja pamięci na te dane
    void* bufor = (void*) malloc(packet_size);

    if(size > 1) {
        if(rank == 0) { // Proces początkowy
            tag = 0; dest = 1;
            struct My_struct value = {"Mateusz", 22, 187.5}; // Wypełnienie struktury

            MPI_Pack(&value.name[0], 7, MPI_CHAR, bufor, packet_size, &position, MPI_COMM_WORLD);
            MPI_Pack(&value.age, 1, MPI_INT, bufor, packet_size, &position, MPI_COMM_WORLD);
            MPI_Pack(&value.height, 1, MPI_FLOAT, bufor, packet_size, &position, MPI_COMM_WORLD);

            MPI_Send(&rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
            MPI_Send(bufor, position, MPI_PACKED, dest, tag + 1, MPI_COMM_WORLD);
        } 
        else { // Wszystkie inne wątki niż początkowy
            int prev = rank - 1;
            int next = rank + 1;

            MPI_Recv(&ranksent, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &status);
            MPI_Recv(bufor, packet_size, MPI_PACKED, prev, 1, MPI_COMM_WORLD, &status); 

            struct My_struct value;

            MPI_Unpack(bufor, packet_size, &position, &value.name, 7, MPI_CHAR, MPI_COMM_WORLD);
            MPI_Unpack(bufor, packet_size, &position, &value.age, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Unpack(bufor, packet_size, &position, &value.height, 1, MPI_FLOAT, MPI_COMM_WORLD);

            printf("Proces %d, odebrał imię: %s, wiek: %d, wzrost: %.2f od procesu %d\n",  
                   rank, value.name, value.age, value.height, ranksent);

            if(rank < size - 1) { // Procesy środkowe
                position = 0; 
                value.age++; // Przykład modyfikacji danych
                MPI_Pack(&value.name[0], 7, MPI_CHAR, bufor, packet_size, &position, MPI_COMM_WORLD);
                MPI_Pack(&value.age, 1, MPI_INT, bufor, packet_size, &position, MPI_COMM_WORLD);
                MPI_Pack(&value.height, 1, MPI_FLOAT, bufor, packet_size, &position, MPI_COMM_WORLD);

                MPI_Send(&rank, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
                MPI_Send(bufor, position, MPI_PACKED, next, 1, MPI_COMM_WORLD);
            }
        }
    } else {
        printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
    }

    free(bufor);
    MPI_Finalize(); 
  
    return(0);
}


