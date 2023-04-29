#include "../include/decode.h"

/* retorna o caractere atrelado a chave */
char find_key(struct charList* charlist, int key) {

    struct charNode* char_aux = charlist->head;
    struct keyNode* key_aux;

    while (char_aux) {
       key_aux = char_aux->keylist->head;
       while (key_aux) {
            if (key_aux->value == key)
                return char_aux->character;
            key_aux = key_aux->next;
        }
        char_aux = char_aux->next;
        key_aux = char_aux->keylist->head;
    }

    return '?'; /* numero nao tem caractere correspondente */
}

/* realiza a decodificacao de uma mensagem codificada utilizando a lista de caracteres */
void decode(FILE* coded_msg, FILE* decoded_msg, struct charList* charlist) {
    
    int numb, ret;

    while ((ret = fscanf(coded_msg, "%d", &numb)) != EOF) {
        
        if (ret > 0) {
            switch (numb) {
                case -1:
                    fprintf(decoded_msg, " ");
                    continue;
                case -2:
                    fprintf(decoded_msg, "\n");
                    continue;
                case -3:
                    fprintf(decoded_msg, "(?)");
                    continue;
            }
        fprintf(decoded_msg, "%c", find_key(charlist, numb));
        }
        /* caso a leitura falhe */
        else
            fgetc (coded_msg);
    }
}

  