# Kompilator
CCOMP = gcc

# Konsolidator
LOADER = gcc

# Opcje kompilacji
# Wersja do debugowania
OPT = -g -DDEBUG
# Wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

# Pliki nagłówkowe
INC = -I.

# Biblioteki (jeśli są potrzebne)
# LIB = -L../pomiar_czasu -lm

# Zależności i komendy
moj_program: moj_program.o pomiar_czasu.o
	$(LOADER) $(OPT) moj_program.o pomiar_czasu.o -o moj_program 

moj_program.o: moj_program.c pomiar_czasu.h
	$(CCOMP) $(OPT) $(INC) -c moj_program.c

pomiar_czasu.o: pomiar_czasu.c pomiar_czasu.h
	$(CCOMP) $(OPT) $(INC) -c pomiar_czasu.c

clean:
	rm -f *.o moj_program

.PHONY: all clean

