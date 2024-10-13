#include <stdio.h>
#include <stdlib.h>
#include "triematrice.h"


int main() {
    struct _trie *trie = create_trie(100); 

    const unsigned char *word = (const unsigned char *)"abab";
    const unsigned char *word2 = (const unsigned char *)"abBBBB";

    insert(trie,word);
    insertPrefixesPasOptimale(trie, word);
    printf("le mot %s est dans le trie : %d\n",word,isInTrie(trie,word));
    printf("le mot %s est dans le trie : %d\n",word2,isInTrie(trie,word2));
    insertPrefixes(trie, word);
    insertSuffixes(trie, word);
    insertFactors(trie, word);

    print_trie(trie);

    free(trie->finite);
    free(trie->transition);
    free(trie);



    return 0;
}