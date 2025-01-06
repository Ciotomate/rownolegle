#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 18


int main ()
{
  double a[WYMIAR];

#pragma omp  parallel for default(none) shared(a)
  for(int i=0;i<WYMIAR;i++) a[i]=1.02*i;

  // pętla sekwencyjna
  double suma=0.0;
  for(int i=0;i<WYMIAR;i++) {
      suma += a[i];
  }
  
  printf("Suma wyrazów tablicy: %lf\n", suma);

  // pętla do modyfikacji - docelowo równoległa w OpenMP
  double suma_parallel=0.0;
  // ...
  //3.4
  //#pragma omp parallel for default(none) reduction(+:suma_parallel) shared(a) ordered 
  //zadanie 5 podpunkt 1
  //#pragma omp  parallel for default(none) schedule(static, 3) num_threads(4) reduction(+:suma_parallel) shared(a) ordered 
 //5.2
  //#pragma omp  parallel for default(none) schedule(static) num_threads(4) reduction(+:suma_parallel) shared(a) ordered 
  //5.3
  //#pragma omp  parallel for default(none) schedule(dynamic, 2) num_threads(4) reduction(+:suma_parallel) shared(a) ordered 
  //5.4
  //#pragma omp  parallel for default(none) schedule(dynamic) num_threads(4) reduction(+:suma_parallel) shared(a) ordered 
 
  for(int i=0;i<WYMIAR;i++) {
    int id_w = omp_get_thread_num();
      suma_parallel += a[i];
  
  #pragma omp ordered
      printf("a[%2d]->W_%1d  \n",i,id_w); 
  }

  printf("\nSuma wyrazów tablicy równolegle (z klauzulą - ....: %lf\n",
	 suma_parallel);

}
