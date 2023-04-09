#include "decode.h"

// returns the character of the key
char findKey(struct charList* charlist, int key) {

    struct charNode* charAux = charlist->head;
    struct keyNode* keyAux;

    while (charAux) {
       keyAux = charAux->keylist->head;
       while (keyAux) {
            if (keyAux->value == key)
                return charAux->character;
            keyAux = keyAux->next;
        }
        charAux = charAux->next;
        keyAux = charAux->keylist->head;
    }

    return '?'; // "?" significa que o numero não tem caractere correspondente
}

void decode(FILE* codedMsg, FILE* decodedMsg, struct charList* charlist) {
    
    int numb;

    while (fscanf(codedMsg, "%d", &numb) != EOF) {
        
        switch (numb) {
            case -1:
                fprintf(decodedMsg, " ");
                continue;
            case -2:
                fprintf(decodedMsg, "\n");
                continue;
            case -3:
                fprintf(decodedMsg, "*");
                continue;
        }

        fprintf(decodedMsg, "%c", findKey(charlist, numb));
    }
}

  