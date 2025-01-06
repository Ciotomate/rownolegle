#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 10

int main ()
{
  double a[WYMIAR][WYMIAR];

  for(int i=0;i<WYMIAR;i++) for(int j=0;j<WYMIAR;j++) a[i][j]=1.02*i+1.01*j;

  // podwójna pętla - sekwencyjnie, suma kontrolna
  double suma=0.0;
  for(int i=0;i<WYMIAR;i++) {
    for(int j=0;j<WYMIAR;j++) {
      suma += a[i][j];
    }
  }
  
  printf("Suma wyrazów tablicy: %lf\n", suma);

  omp_set_nested(1);

  // podwójna pętla - docelowo równolegle
  double suma_parallel=0.0; int i,j;
  //7.1
  
  #pragma omp parallel for default(none) reduction(+:suma_parallel)  schedule(static, 2) shared(a) private(j) ordered 
   for(i=0;i<WYMIAR;i++) {
    int id_w = omp_get_thread_num();
       #pragma omp ordered
    }   
    // 7.2
   /*
   #pragma omp  parallel for default(none) reduction(+:suma_parallel)  schedule(dynamic) shared(a,i)  ordered
    for(j=0;j<WYMIAR;j++) {
      suma_parallel += a[i][j];
      #pragma omp ordered
      // dla dekompozycji 1D
      printf("(%1d,%1d)-W_%1d ",i,j,omp_get_thread_num()); 
      */
      
 /*     
     switch(omp_get_thread_num()){
      case 0:
      	printf("#");
      break;
      case 1:
      	printf("&");
      	
      break;
      case 2:
      	printf("$");
      break;
      }
      
    }
    
     #pragma omp ordered
    printf("\n");
    */
    /*
  }
 }
 */
 //}
  
  
  //7.3
  /*
  #pragma omp parallel default(none) shared(a, suma_parallel) 
  {
  double suma_tmp = 0.0;
  #pragma omp for schedule(static) ordered private(i)
  for(j=0;j<WYMIAR;j++) {
    int id_w = omp_get_thread_num();
    
    for(i=0;i<WYMIAR;i++) {
      suma_tmp += a[i][j];
      #pragma omp ordered
      // dla dekompozycji 1D
     // printf("(%1d,%1d)-W_%1d ",i,j,omp_get_thread_num()); 
      
     switch(omp_get_thread_num()){
      case 0:
      	printf("#");
      break;
      case 1:
      	printf("&");
      	
      break;
      case 2:
      	printf("$");
      break;
      }
    }
    #pragma omp ordered
    printf("\n");
  }
  #pragma omp critical(suma_parallel)
  suma_parallel += suma_tmp;
  #pragma omp barrier
  }
  //koniec 7.3
  printf("Suma wyrazów tablicy równolegle: %lf\n", suma_parallel);

}*/
