#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "encode.h"

// return a random key of the character list
int catchRandomKey(struct charList* charlist, char c) {

    struct charNode* charAux = charlist->head;
    struct keyNode* keyAux;
    int i;

    while (charAux) {
        if (charAux->character == c) {
            i = rand() % (charAux->keylist->size);
            keyAux = charAux->keylist->head;
            for(int j = 0; j < i; j++) {
                keyAux = keyAux->next;
            }
            return keyAux->value;
        }
        charAux = charAux->next;
    }
    
    return 0;
}

void encode(FILE* original, FILE* coded, struct charList* charlist) {

    int key;
    char c;
    
    srand((unsigned)time(NULL)); // generate random seed

    while ((c = getc(original)) != EOF) {

        if (isspace(c)) {
            fprintf(coded, "-1 ");
            continue;
        }
        
        key = catchRandomKey(charlist, tolower(c));
        fprintf(coded, "%d ", key);
    }
}