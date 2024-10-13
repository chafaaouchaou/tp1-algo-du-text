# Définitions générales
CC = gcc
CFLAGS = -Wall -g

# Cible par défaut
all: prog1 prog2

# Cible pour le programme 1 (prog1)
prog1: tp1matrice
	./tp1matrice

# Compilation de l'exécutable tp1matrice
tp1matrice: tp1matrice.o triematriceimplimentation.o
	$(CC) $(CFLAGS) -o tp1matrice tp1matrice.o triematriceimplimentation.o

# Compilation du fichier objet principal (tp1matrice)
tp1matrice.o: tp1matrice.c triematrice.h
	$(CC) $(CFLAGS) -c tp1matrice.c

# Compilation du fichier objet de l'implémentation du trie
triematriceimplimentation.o: triematriceimplimentation.c triematrice.h
	$(CC) $(CFLAGS) -c triematriceimplimentation.c

# Cible pour le programme 2 (prog2)
prog2: tp1hachage
	./tp1hachage

# Compilation de l'exécutable tp1hachage
tp1hachage: tp1hachage.o triehachageimentation.o
	$(CC) $(CFLAGS) -o tp1hachage tp1hachage.o triehachageimentation.o

# Compilation du fichier objet principal (tp1hachage)
tp1hachage.o: tp1hachage.c triehachage.h
	$(CC) $(CFLAGS) -c tp1hachage.c

# Compilation du fichier objet de l'implémentation du hachage
triehachageimentation.o: triehachageimentation.c triehachage.h
	$(CC) $(CFLAGS) -c triehachageimentation.c

# Nettoyage des fichiers objets et exécutables (adapté pour Windows)
clean:
	del /Q tp1matrice.exe tp1matrice.o triematriceimplimentation.o tp1hachage.exe tp1hachage.o triehachageimentation.o
