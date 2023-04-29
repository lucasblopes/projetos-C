#include <stdlib.h>
#include <ctype.h>

#include "../include/keys.h"

/* inicializa uma lista de chaves */
struct keyList* new_keylist() {

    struct keyList* new_list = malloc(sizeof(struct keyList));
    if (!new_list) {
        perror("Error on malloc");
        return NULL;
    }

    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->size = 0;

    return new_list;
}

struct charList* new_charlist() {

    struct charList* new_list = malloc(sizeof(struct charList));
    if (!new_list) {
        perror("Error on malloc");
        return NULL;
    }

    new_list->head = NULL;
    new_list->tail = NULL;

    return new_list;
}

/* retorna um nodo da lista de caracteres, ou NULL, caso nao encontre */
struct charNode* search_character(struct charList* charlist, char c) {

    struct charNode* char_aux = charlist->head;

    while (char_aux) {
        if (char_aux->character == c)
            return char_aux;

        char_aux = char_aux->next;
    }
    
    return NULL;
}

/* insere uma chave na cabeca da lista de chaves */
void head_key_insertion(struct keyList* keylist, int key) {

    struct keyNode* new_key = malloc(sizeof(struct keyNode));
    if (!new_key) {
        perror("Error on malloc");
        exit (1);
    }
    new_key->value = key;
    /* caso a lista esteja vazia */
    if (!keylist->head) {
        new_key->next = NULL;
        keylist->head = new_key;
        keylist->tail = new_key;
    } else {
        new_key->next = keylist->head;
        keylist->head = new_key;
    }
    keylist->size += 1;
}

/* insere uma chave na cauda da lista de chaves */
void tail_key_insertion(struct keyList* keylist, int key) {

    struct keyNode* new_key = malloc(sizeof(struct keyNode));
    if (!new_key) {
        perror("Error on malloc");
        exit (1);
    }
    new_key->value = key;
    new_key->next = NULL;
    /* caso a lista esteja vazia */
    if (!keylist->head) {
        keylist->head = new_key;
        keylist->tail = new_key;
    } else {
        keylist->tail->next = new_key;
        keylist->tail = new_key;
    }
    keylist->size += 1;
}   


/* insere um nodo na cabeca da lista de caracteres */
struct charNode* head_character_insertion(struct charList* charlist, char c) {

    struct charNode* new_char = malloc(sizeof(struct charNode));
    if (!new_char) {
        perror("Error on malloc");
        exit (1);
    }
    new_char->character = c;
    new_char->keylist = new_keylist();

    /* caso a lista esteja vazia */
    if (!charlist->head) {
        new_char->next = NULL;
        charlist->head = new_char;
        charlist->tail = new_char;
    } else {
        new_char->next = charlist->head;
        charlist->head = new_char;
    }

    return new_char;
}   

/* insere um nodo na cauda da lista de caracteres */
struct charNode* tail_character_insertion(struct charList* charlist, char c) {
    
    struct charNode* new_char = malloc(sizeof(struct charNode));
    if (!new_char) {
        perror("Error on malloc");
        exit (1);
    }
    new_char->character = c;
    new_char->next = NULL;
    new_char->keylist = new_keylist();

    /* caso a lista esteja vazia */
    if (!charlist->head) { 
        charlist->head = new_char;
        charlist->tail = new_char;
    } else {
        charlist->tail->next = new_char;
        charlist->tail = new_char;
    }
    
    return new_char;
}

/* insere ordenado na lista de caracteres */
struct charNode* sorted_character_insertion(struct charList* charlist, char c) {

    /* caso a lista esteja vazia ou o caractere esteja antes da cabeca */
    if (!charlist->head || c < charlist->head->character) {
        return head_character_insertion(charlist, c);
    }
    /* se o caractere estiver antes da cauda */
    if (c > charlist->tail->character) {
        return tail_character_insertion(charlist, c);
    }
    struct charNode *aux, *new_char = malloc(sizeof(struct charNode));
    if (!new_char) {
        perror("Error on malloc");
        exit (1);
    }
 
    new_char->character = c;
    new_char->keylist = new_keylist();

    aux = charlist->head;
    while(aux->next && new_char->character > aux->next->character)
        aux = aux->next;
    new_char->next = aux->next;
    aux->next = new_char;

    return new_char;
}

/* cria o arquivo de chaves atraves do livro cifra */
void create_keylist_book(FILE* cipher, struct charList* charlist) {

    char c = 0;
    int next = 1, key = 0;
    struct charNode* charnode = NULL;

    while ((c = getc(cipher)) != EOF) {

        if (isspace(c)) {
            next = 1;
            continue;
        }

        if (next) {
            charnode = search_character(charlist, tolower(c));
            if (!charnode)
                charnode = sorted_character_insertion(charlist, tolower(c));
            head_key_insertion(charnode->keylist, key);
            key++;
            next = 0;
        }
    }
    
}

/* cria a lista de caracteres/chaves atraves de um arquivo de chaves */
void create_keylist_file(FILE* key_file, struct charList* charlist) {

    struct charNode* charnode;
    int key, newline = 1;
    char c;

    while ((c = getc(key_file)) != EOF) {

        if (newline) {

            charnode = tail_character_insertion(charlist, c);
            newline = 0;
        } 
        else if (isdigit(c)) {

            ungetc(c, key_file);
            fscanf(key_file, "%d", &key);
            tail_key_insertion(charnode->keylist, key);
        }
        else if (c == '\n') {
            newline = 1;
        }
    }
}

/* cria o arquivo de chaves */
void create_keyfile(FILE* key_file, struct charList* charlist) {

    struct charNode* char_aux = charlist->head;
    struct keyNode* key_aux;

    while (char_aux) {
        key_aux = char_aux->keylist->head;
        fprintf(key_file, "%c: ", char_aux->character);
        while (key_aux) {
            fprintf(key_file, "%d ", key_aux->value);
            key_aux = key_aux->next;
        }
        fprintf(key_file, "\n");

        char_aux = char_aux->next;
    }
}

/* libera memoria alocada as listas de chaves */
void free_keylist(struct keyNode *keynode) {

    struct keyNode *tmp;

    while (keynode != NULL) {

        tmp = keynode->next;
        free(keynode);
        keynode = NULL;
        keynode = tmp;
    }
}

/* libera memoria alocada a lista de caracteres */
void free_charlist(struct charNode* charnode) {

    struct charNode* tmp;

    while (charnode != NULL) {
        
        tmp = charnode->next;
        free_keylist(charnode->keylist->head);
        free(charnode->keylist);
        charnode->keylist = NULL;
        free(charnode);
        charnode = NULL;
        charnode = tmp;
    }
}