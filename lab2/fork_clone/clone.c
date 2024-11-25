#define _GNU_SOURCE
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>

#include "pomiar_czasu.h"
int zmienna_globalna=0;

#define ROZMIAR_STOSU 1024*64

int funkcja_watku( void* argument )
{

  int zmienna_lokalna = 0;

  for(int i = 0; i < 100000; i++){
  	zmienna_lokalna++;
  	zmienna_globalna++;
  	}
  printf("Zmienna globalna: %d\n", zmienna_globalna);
  printf("Zmienna lokalna: %d\n", zmienna_lokalna);

  return 0;
}

int main()
{

  void *stos, *stos1;
  pid_t pid, pid1;
  int i; 
  
  stos = malloc( ROZMIAR_STOSU );
  if (stos == 0) {
    printf("Proces nadrzędny - blad alokacji stosu\n");
    exit( 1 );
  }
  
  stos1 = malloc( ROZMIAR_STOSU );
  if (stos1 == 0) {
    printf("Proces nadrzędny - blad alokacji stosu\n");
    exit( 1 );
  }
  
    pid = clone( &funkcja_watku, (void *) stos+ROZMIAR_STOSU, 
		 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );
    
    pid1 = clone( &funkcja_watku, (void *) stos1+ROZMIAR_STOSU, 
		 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );
		     
    waitpid(pid, NULL, __WCLONE);
    waitpid(pid1, NULL, __WCLONE);
    
    printf("Koncowy wynik\n");
    printf("Zmienna globalna: %d\n", zmienna_globalna);

  free( stos );
}
