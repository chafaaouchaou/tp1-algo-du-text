#include <stdio.h>
#include <stdlib.h>
#include "triehachage.h"







int main() {
    // Création d'un trie avec un nombre maximal de 10 nœuds (à ajuster selon tes besoins)
    struct _trie *trie = create_trie(100);



// Inserer plusiers mots dans le trie
// Mots à insérer dans le trie
// const unsigned char *words[] = {
//     (const unsigned char *)"hello",
//     (const unsigned char *)"hi",
//     (const unsigned char *)"t",
//     // (const unsigned char *)"tree",
//     // (const unsigned char *)"hash",
//     // (const unsigned char *)"structure"
// };

// Insertion des mots dans le trie
// for (int i = 0; i < 3; i++) {
//     insert(trie, words[i]);
// }



    const unsigned char *word = (const unsigned char *)"abcAZS";

    


    insert(trie, word);
    insertPrefixes(trie, word);
    insertSuffixes(trie, word);
    insertPrefixesPasOptimale(trie, word);
    insertFactors(trie, word);


    print_trie(trie);

    printf("Le mot \"%s\" est %s dans le trie.\n", word, isInTrie(trie, word) ? "présent" : "absent");


    // Libération de la mémoire
    free(trie->finite);
    free(trie->transition);
    free(trie);


    return 0;
}

