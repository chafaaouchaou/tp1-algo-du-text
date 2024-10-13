// triehachage.h
#ifndef TRIEHACHAGE_H
#define TRIEHACHAGE_H

// Trie structure

#define M 100  // Nombre d'emplacements de la table de hachage

struct _list {
    int startNode;           /* Etat de départ de la transition */
    int targetNode;          /* Etat cible de la transition */
    unsigned char letter;    /* Etiquette de la transition */
    struct _list *next;      /* Maillon suivant */
};
typedef struct _list *List;

struct _trie {
    int maxNode;             /* Nombre maximal de noeuds du trie */
    int nextNode;            /* Indice du prochain noeud disponible */
    List *transition;        /* Listes d’adjacence (table de hachage) */
    char *finite;            /* Etats terminaux */
};




// Function declarations
int hash_function(int state, unsigned char letter, int m);
List create_list(int startNode, unsigned char letter, int targetNode);
struct _trie* create_trie(int maxNodes);
void insert(struct _trie *trie, const unsigned char *word);
void print_trie(struct _trie *trie);
int isInTrie(struct _trie *trie, const unsigned char *word);
void insertPrefixesPasOptimale(struct _trie *trie, const unsigned char *word);
void insertPrefixes(struct _trie *trie, const unsigned char *word);
void insertSuffixes(struct _trie *trie, const unsigned char *word);
void insertFactors(struct _trie *trie, const unsigned char *word);
#endif // TRIEHACHAGE_H
