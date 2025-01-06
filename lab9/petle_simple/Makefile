
CC = gcc

LD = gcc

OPT =

INC =

LIB = -fopenmp

openmp_petle_simple: openmp_petle_simple.o 
	$(LD) $(OPT) -o openmp_petle_simple openmp_petle_simple.o $(LIB)

openmp_petle_simple.o: openmp_petle_simple.c
	$(CC)  $(OPT) -fopenmp -c openmp_petle_simple.c $(INC)


clean:
	rm -f *.o openmp_petle_simple
