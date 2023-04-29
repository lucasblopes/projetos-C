#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "../include/encode.h"
#include "../include/keys.h"

/* retorna uma chave aleatoria do caractere */
int catch_random_key(struct charList* charlist, char c) {

    struct charNode* character = search_character(charlist, c);
    struct keyNode* key_aux;
    int i;

    if (character != NULL) {
        i = rand() % (character->keylist->size);
        key_aux = character->keylist->head;
        for(int j = 0; j < i; j++) {
            key_aux = key_aux->next;
        }
        return key_aux->value;
    }

    return -3; /* caracter nao encontrado em charList */
}

/* realiza a codificacao de uma mensagem utilizando a lista de caracteres criada */
void encode(FILE* original, FILE* coded, struct charList* charlist) {

    int key;
    char c;
    
    srand((unsigned)time(NULL)); /* gera uma seed aleatoria */

    while ((c = getc(original)) != EOF) {

        if (c == ' ') {
            fprintf(coded, "-1 "); /* espaco */
            continue;
        }
        if (c == '\n') {
            fprintf(coded, "-2 "); /* nova linha */
            continue;
        }
        
        key = catch_random_key(charlist, tolower(c));
        fprintf(coded, "%d ", key);
    }
}

