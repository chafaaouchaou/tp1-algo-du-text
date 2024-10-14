#include <stdio.h>
#include <stdlib.h>
#include "triehachage.h"







int main() {
    // Création d'un trie avec un nombre maximal de 10 nœuds (à ajuster selon tes besoins)
    struct _trie *trie = create_trie(1000);
    struct _trie *trieinsertPrefixes = create_trie(1000);
    struct _trie *trieinsertSuffixes = create_trie(1000);
    struct _trie *trieinsertFactors = create_trie(1000);



    

// Inserer plusiers mots dans le trie
// Mots à insérer dans le trie
const unsigned char *words[] = {
    (const unsigned char *)"hello",
    (const unsigned char *)"hi",
    (const unsigned char *)"t",
    (const unsigned char *)"tree",
    (const unsigned char *)"hash",
    (const unsigned char *)"structure"
};
    const unsigned char *word = (const unsigned char *)"abcAZS";


int word_count = sizeof(words) / sizeof(words[0]);
// Insertion des mots dans le trie
for (int i = 0; i < word_count; i++) {
    insert(trie, words[i]);
}

    insertPrefixes(trieinsertPrefixes, word);
    insertSuffixes(trieinsertSuffixes, word);
    // insertPrefixesPasOptimale(trie, word); // c'est juste une autre methode pour inserer les prefixes
    insertFactors(trieinsertFactors, word);
    
    
    
    
    
    printf("TRIE\n");
    print_trie(trie);
        printf("_______________________________________________________________________________________________________\n");

    printf("TRIE INSERT PREFIXES\n");
    print_trie(trieinsertPrefixes);
        printf("_______________________________________________________________________________________________________\n");

    printf("TRIE INSERT SUFFIXES\n");
    print_trie(trieinsertSuffixes);
        printf("_______________________________________________________________________________________________________\n");

    printf("TRIE INSERT FACTORS\n");
    print_trie(trieinsertFactors);
        printf("_______________________________________________________________________________________________________\n");

    printf("Le mot \"%s\" est %s dans le trie.\n", word, isInTrie(trie, word) ? "présent" : "absent");



    // Libération de la mémoire
    free(trie->finite);
    free(trie->transition);
    free(trie);
    free(trieinsertPrefixes->finite);
    free(trieinsertPrefixes->transition);
    free(trieinsertPrefixes);
    free(trieinsertSuffixes->finite);
    free(trieinsertSuffixes->transition);
    free(trieinsertSuffixes);
    free(trieinsertFactors->finite);
    free(trieinsertFactors->transition);
    free(trieinsertFactors);


    return 0;
}

