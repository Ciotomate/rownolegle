
CC = gcc

LD = gcc

OPT =

INC =

LIB = -fopenmp

openmp_petle: openmp_petle.o 
	$(LD) $(OPT) -o openmp_petle openmp_petle.o $(LIB)

openmp_petle.o: openmp_petle.c
	$(CC)  $(OPT) -fopenmp -c openmp_petle.c $(INC)


clean:
	rm -f *.o openmp_petle
