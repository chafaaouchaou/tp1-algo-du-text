#include "triehachage.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



// Fonction de hachage
// pour un couple (état, lettre) elle renvoyer un entier compris entre 0 et m - 1
// Le nombre 31 est un multiplicateur pour assurer une bonne répartition (c'est un nombre premier souvent utilisé en hachage).
int hash_function(int state, unsigned char letter, int m) {
    return (state * 31 + letter) % m;  
}




// Fonction pour créer une nouvelle liste
List create_list(int startNode, unsigned char letter, int targetNode) {
    List new_node = (List) malloc(sizeof(struct _list));
    new_node->startNode = startNode;
    new_node->letter = letter;
    new_node->targetNode = targetNode;
    new_node->next = NULL;
    return new_node;
}

// Fonction pour créer un trie
struct _trie* create_trie(int maxNodes) {
    struct _trie *trie = (struct _trie *) malloc(sizeof(struct _trie));
    trie->maxNode = maxNodes;
    trie->nextNode = 1;
    trie->transition = (List *) malloc(M * sizeof(List));

    for (int i = 0; i < M; i++) {
        trie->transition[i] = NULL;  // Initialisation des listes d'adjacence à NULL
    }

    trie->finite = (char *) malloc(maxNodes * sizeof(char));

    for (int i = 0; i < maxNodes; i++) {
        trie->finite[i] = 0;  // Initialisation des états terminaux à 0
    }

    return trie;
}




// Fonction pour inserer un mot dans un trie
void insert(struct _trie *trie, const unsigned char *word) {
    int currentNode = 0;  // Commence à la racine

    for (int i = 0; word[i] != '\0'; i++) {
        unsigned char letter = word[i];
        int hashIndex = hash_function(currentNode, letter, M);

        // Rechercher si la transition existe déjà dans la liste
        List temp = trie->transition[hashIndex];
        while (temp != NULL && (temp->startNode != currentNode || temp->letter != letter)) {
            temp = temp->next;
        }

        // Si la transition n'existe pas, on crée un nouveau noeud
        if (temp == NULL) {
            List newTransition = create_list(currentNode, letter, trie->nextNode++);
            newTransition->next = trie->transition[hashIndex];
            trie->transition[hashIndex] = newTransition;
        }

        // Passer au noeud suivant
        currentNode = temp ? temp->targetNode : trie->nextNode - 1;
    }

    // Marquer le dernier nœud comme état terminal
    trie->finite[currentNode] = 1;
}




// Fonction pour afficher le trie
void print_trie(struct _trie *trie) {
    printf("Matrice de transition (hash):\n");
    for (int i = 0; i < M; i++) {
        List temp = trie->transition[i];
        while (temp != NULL) {
            printf("État %d --[%c]--> État %d\n", temp->startNode, temp->letter, temp->targetNode);
            temp = temp->next;
        }
    }
    
    printf("États terminaux :\n");
    for (int i = 0; i < trie->maxNode; i++) {
        if (trie->finite[i]) {
            printf("État %d est un état terminal.\n", i);
        }
    }
}


// Fonction pour verifier que un mot est dans le trie ou pas
int isInTrie(struct _trie *trie, const unsigned char *word) {
    int currentNode = 0; // Commence à la racine

    for (int i = 0; word[i] != '\0'; i++) {
        unsigned char letter = word[i];
        int hashIndex = hash_function(currentNode, letter, M);

        // Rechercher si la transition existe dans la liste
        List temp = trie->transition[hashIndex];
        while (temp != NULL && (temp->startNode != currentNode || temp->letter != letter)) {
            temp = temp->next;
        }

        // Si la transition n'existe pas, le mot n'est pas dans le trie
        if (temp == NULL) {
            return 0; // Le mot n'est pas dans le trie
        }

        // Passer au noeud suivant
        currentNode = temp->targetNode;
    }

    // Vérifier si le dernier nœud est un état terminal
    return trie->finite[currentNode] == 1; // Retourne 1 si c'est un état terminal, sinon 0
}




// Insérer un mot dans le trie en créant un chemin pour chaque préfixe
//  le mot lui meme est inclu
void insertPrefixesPasOptimale(struct _trie *trie, const unsigned char *word) {
    int length = strlen((const char *)word);
    
    // Insérer tous les préfixes sauf le mot lui-même
    for (int i = 0; i < length ; i++) { // Ne pas inclure le dernier caractère
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

    // Marquer tous les nœuds sauf le dernier comme terminaux
    int currentNode = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        unsigned char letter = word[i];
        int hashIndex = hash_function(currentNode, letter, M);

        // Rechercher la transition pour cette lettre
        List temp = trie->transition[hashIndex];
        while (temp != NULL && (temp->startNode != currentNode || temp->letter != letter)) {
            temp = temp->next;
        }

        // Passer au nœud suivant
        currentNode = temp ? temp->targetNode : trie->nextNode - 1;

        // Marquer les nœuds comme terminaux sauf le dernier
        if (word[i + 1] != '\0') {  // Assure que ce n'est pas le dernier caractère du mot
            trie->finite[currentNode] = 1;  // Marquer comme état terminal
        }
    }

    // Ne pas marquer le dernier nœud comme état terminal
    // trie->finite[currentNode] = 0;  // S'assurer que le dernier nœud n'est pas terminal
    // le probleme avec cette instruction est que si le mot existe deja dans le trie le fait d'inserer ces prefixes vas metre le dernier noeud comme non terminal ce qui veux dire que le mot n'est pas dans le trie
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
            unsigned char factor[100]; // Faut s'assura que la taille est suffisante
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