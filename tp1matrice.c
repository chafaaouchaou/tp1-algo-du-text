#include <stdio.h>
#include <stdlib.h>
#include "triehachage.h"

int main() {
    struct _trie *trie = create_trie(1000); // Initialisation du trie avec hachage
    struct _trie *trieinsertPrefixes = create_trie(1000); 
    struct _trie *trieinsertSuffixes = create_trie(1000); 
    struct _trie *trieinsertFactors = create_trie(1000); 

    // Liste de mots à insérer dans les différentes structures de trie
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
    
    // Insertion des mots dans le trie principal
    for (int i = 0; i < word_count; i++) {
        insert(trie, words[i]);
    }

    // Insertion des préfixes, suffixes, et facteurs dans les tries respectifs
    insertPrefixes(trieinsertPrefixes, word);
    // insertPrefixesPasOptimale(trie, word); // c'est juste une autre methode pour inserer les prefixes
    insertSuffixes(trieinsertSuffixes, word);
    insertFactors(trieinsertFactors, word);

    // Affichage des différents tries
    printf("TRIE (hachage)\n");
    print_trie(trie);
    printf("_______________________________________________________________________________________________________\n");

    printf("TRIE INSERT PREFIXES (hachage)\n");
    print_trie(trieinsertPrefixes);
    printf("_______________________________________________________________________________________________________\n");

    printf("TRIE INSERT SUFFIXES (hachage)\n");
    print_trie(trieinsertSuffixes);
    printf("_______________________________________________________________________________________________________\n");

    printf("TRIE INSERT FACTORS (hachage)\n");
    print_trie(trieinsertFactors);
    printf("_______________________________________________________________________________________________________\n");

    // Vérification si un mot est présent dans le trie principal
    printf("Le mot \"%s\" est %s dans le trie.\n", word, isInTrie(trie, word) ? "présent" : "absent");

    // Libération de la mémoire allouée pour chaque trie
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
