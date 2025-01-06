#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc, char** argv) {
  
  int rank, size;
  MPI_Status status;
  
  MPI_Init(&argc, &argv); 
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  
  int send_value = 10;
  int receive_value;

  if (size > 1) {
  //proces poczatkowy
    if (rank == 0) {
      MPI_Send(&send_value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } 
    //proces srodkowy
    else if (rank < size - 1) {
      MPI_Recv(&receive_value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
      printf("Wątek %d odebrał liczbę %d, od wątka %d\n", rank, receive_value, rank - 1);
      receive_value++;
      MPI_Send(&receive_value, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
    }
    //proces koncowy 
    else {
      MPI_Recv(&receive_value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
      printf("Wątek %d odebrał liczbę %d, od wątka %d\n", rank, receive_value, rank - 1);
    }
  } else {
    printf("Pojedynczy wątek o ranku: %d (brak komunikatów)\n", rank);
  }

  MPI_Finalize(); 
  
  return 0;
}

