// triematrice.h
#ifndef TRIEMATRICE_H
#define TRIEMATRICE_H

// Trie structure
struct _trie {
    int maxNode;          // Maximum number of nodes in the trie
    int nextNode;         // Index of the next available node
    int **transition;     // Transition matrix
    char *finite;         // Terminal states
};

// Function declarations
struct _trie* create_trie(int maxNodeParam);
void insert(struct _trie *trie, const unsigned char *word);
void print_trie(struct _trie *trie);
int isInTrie(struct _trie *trie, const unsigned char *word);
void insertPrefixesPasOptimale(struct _trie *trie, const unsigned char *word);
void insertPrefixes(struct _trie *trie, const unsigned char *word);
void insertSuffixes(struct _trie *trie, const unsigned char *word);
void insertFactors(struct _trie *trie, const unsigned char *word);

#endif // TRIEMATRICE_H
