#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "../include/encode.h"
#include "../include/keys.h"

// return a random key of the character node
int catchRandomKey(struct charList* charlist, char c) {

    struct charNode* character = searchCharacter(charlist, c);
    struct keyNode* keyAux;
    int i;

    if (character != NULL) {
        i = rand() % (character->keylist->size);
        keyAux = character->keylist->head;
        for(int j = 0; j < i; j++) {
            keyAux = keyAux->next;
        }
        return keyAux->value;
    }

    return -3; // '-3' means the character was not found
}

void encode(FILE* original, FILE* coded, struct charList* charlist) {

    int key;
    char c;
    
    srand((unsigned)time(NULL)); // generate random seed

    while ((c = getc(original)) != EOF) {

        if (c == ' ') {
            fprintf(coded, "-1 ");
            continue;
        }
        if (c == '\n') {
            fprintf(coded, "-2 ");
            continue;
        }
        
        key = catchRandomKey(charlist, tolower(c));
        fprintf(coded, "%d ", key);
    }
}

