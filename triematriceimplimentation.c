#include "triematrice.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Function to create a trie
struct _trie* create_trie(int maxNodeParam) {
    struct _trie *trie = malloc(sizeof(struct _trie));
    trie->maxNode = maxNodeParam;  // Maximum number of nodes
    trie->nextNode = 1;  // Start at 1, 0 is the root

    // Allocate transition matrix
    trie->transition = malloc(maxNodeParam * sizeof(int*));  // Allocate rows
    for (int i = 0; i < maxNodeParam; i++) {
        trie->transition[i] = malloc(UCHAR_MAX * sizeof(int));  // Allocate columns
        for (int j = 0; j < UCHAR_MAX; j++) {
            trie->transition[i][j] = -1;  // -1 indicates no transition
        }
    }

    // Allocate space for terminal states
    trie->finite = malloc(maxNodeParam * sizeof(char));
    memset(trie->finite, 0, maxNodeParam * sizeof(char));  // Initialize to 0

    return trie;
}

// Fonction pour ajouter un mot au trie
void insert(struct _trie *trie, const unsigned char *word) {
    int currentNode = 0; // Commence à la racine du trie

    for (int i = 0; word[i] != '\0'; i++) { // \0 indique la fin du mot

        int index = (int)word[i]; // Utiliser la valeur ASCII du caractère comme index
        

        // Si la transition n'existe pas, créer un nouveau nœud
        if (trie->transition[currentNode][index] == -1) {
            trie->transition[currentNode][index] = trie->nextNode++;
        }

        // Passer au nœud suivant
        currentNode = trie->transition[currentNode][index];
    }

    // Marquer le dernier nœud comme état terminal
    trie->finite[currentNode] = 1; // 1 indique que c'est un état terminal
}

// Fonction pour visualiser le trie
void print_trie(struct _trie *trie) {
    printf("Matrice de transition :\n");
    for (int i = 0; i < trie->nextNode; i++) { // Parcourt chaque nœud
        printf("État %d : ", i);
        for (int j = 0; j < UCHAR_MAX; j++) { // Parcourt les colonnes (tous les caractères possibles)
            if (trie->transition[i][j] != -1) {
                printf(" (%c -> %d) ", j, trie->transition[i][j]); // Affiche la transition avec le caractère ASCII
            }
        }
        printf("\n");
    }
    
    // Affichage de la table des états terminaux
    printf("États terminaux : ");
    for (int i = 0; i < trie->nextNode; i++) {
        if (trie->finite[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

// Fonction qui vérifie si un mot est dans le trie
int isInTrie(struct _trie *trie, const unsigned char *word) {
    int currentNode = 0; // On commence à la racine du trie

    // Parcourt chaque caractère du mot
    for (int i = 0; word[i] != '\0'; i++) {
        int index = (int)word[i]; // Utiliser la valeur ASCII du caractère comme index

        // Si la transition n'existe pas, le mot n'est pas dans le trie
        if (trie->transition[currentNode][index] == -1) {
            return 0; // Mot non trouvé
        }

        // Passe au nœud suivant
        currentNode = trie->transition[currentNode][index];
    }

    // Vérifie si le dernier nœud est un état terminal
    if (trie->finite[currentNode] == 1) {
        return 1; // Le mot est accepté, se termine dans un état terminal
    }

    return 0; // Le mot est dans le trie mais ne se termine pas dans un état terminal
}

// Insérer un mot dans le trie en créant un chemin pour chaque préfixe
void insertPrefixesPasOptimale(struct _trie *trie, const unsigned char *word) {
    int length = strlen((const char *)word);

    // Insérer tous les préfixes sauf le mot lui-même
    for (int i = 0; i < length - 1; i++) { // Ne pas inclure le dernier caractère
        // Insérer le préfixe à partir de la position 0 jusqu'à i
        unsigned char prefix[i + 2]; // +1 pour le caractère nul, +1 pour le préfixe
        strncpy((char *)prefix, (const char *)word, i + 1);
        prefix[i + 1] = '\0'; // Terminer la chaîne

        insert(trie, prefix);
    }
}


// Insérer un mot dans le trie en créant un chemin et en rendant tous les états terminaux
// sauf le dernier pour ne pas reconnaître le mot lui-même.
// De plus, s'il y a un seul caractère, on considère qu'il n'y a pas de préfixe.
void insertPrefixes(struct _trie *trie, const unsigned char *word) {
    // Insérer le mot entier une seule fois
    insert(trie, word);
    // Longueur du mot
    int length = strlen((const char *)word);
    int currentNode = 0;

    // Passer par chaque lettre du mot pour marquer les états terminaux
    for (int i = 0; i < length; i++) {
        int index = (int)word[i]; // Utiliser la valeur ASCII du caractère comme index

        // Rechercher la transition pour cette lettre
        currentNode = trie->transition[currentNode][index];

        // Marquer les nœuds comme terminaux sauf le dernier
        if (i < length - 1) { // Assurer que ce n'est pas le dernier caractère du mot
            trie->finite[currentNode] = 1; // Marquer comme état terminal
        }
    }

    // Ne pas marquer le dernier nœud comme état terminal
    trie->finite[currentNode] = 0; // S'assurer que le dernier nœud n'est pas terminal
}

// Fonction pour insérer tous les suffixes d'un mot dans un trie
void insertSuffixes(struct _trie *trie, const unsigned char *word) {
    int length = strlen((const char *)word);

    // Commencer à partir de l'indice 1 pour éviter d'insérer le mot complet
    for (int i = 1; i < length; i++) {
        // Insérer le suffixe à partir de la position i
        insert(trie, word + i);
    }
}

// Fonction pour insérer tous les facteurs d'un mot dans un trie
void insertFactors(struct _trie *trie, const unsigned char *word) {
    int length = strlen((const char *)word);

    // Insérer les facteurs du mot
    for (int i = 0; i < length; i++) { // i est l'indice de début
        for (int j = i; j < length; j++) { // j est l'indice de fin
            // Créer un facteur qui va de i à j
            unsigned char factor[100]; // la taille du mot ne dois pas depacer 99 caracters
            int k = 0;
            for (int l = i; l <= j; l++) {
                factor[k++] = word[l];
            }
            factor[k] = '\0'; // Terminer la chaîne

            // Insérer le facteur dans le trie
            insert(trie, factor);
        }
    }
}



