# Flagi dla kompilatora
CCOMP = gcc       # Kompilator
LOADER = gcc      # Linker
OPT = -g -DDEBUG  # Debugowanie (możesz odkomentować inną wersję OPT)
# OPT = -O3        # Optymalizacja do mierzenia czasu

# Biblioteki
LIB = 

# Pliki wykonywalne
BINARIES = pub_sym_1 pub_sym_1_2 pub_sym_2 pub_sym_3 pub_sym_bez_mutex

# Reguła główna
all: $(BINARIES)

# Reguły budowania plików wykonywalnych
pub_sym_1: pub_sym_1.o 
	$(LOADER) $(OPT) pub_sym_1.o -o $@ -lpthread $(LIB)

pub_sym_1_2: pub_sym_1_2.o 
	$(LOADER) $(OPT) pub_sym_1_2.o -o $@ -lpthread $(LIB)

pub_sym_2: pub_sym_2.o 
	$(LOADER) $(OPT) pub_sym_2.o -o $@ -lpthread $(LIB)

pub_sym_bez_mutex: pub_sym_bez_mutex.o 
	$(LOADER) $(OPT) pub_sym_bez_mutex.o -o $@ -lpthread $(LIB)

pub_sym_3: pub_sym_3.o
	$(LOADER) $(OPT) pub_sym_3.o -o $@ -lpthread $(LIB)

# Reguły budowania plików obiektowych
%.o: %.c
	$(CCOMP) -c $(OPT) $< -o $@

# Czyszczenie plików tymczasowych
clean:
	rm -f *.o $(BINARIES)

