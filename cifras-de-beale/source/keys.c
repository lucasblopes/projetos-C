#include <stdlib.h>
#include <ctype.h>

#include "../include/keys.h"

struct keyList* newKeyList() {

    struct keyList* newList = malloc(sizeof(struct keyList));
    if (!newList) {
        perror("Error on malloc");
        return NULL;
    }

    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;

    return newList;
}

struct charList* newCharList() {

    struct charList* newList = malloc(sizeof(struct charList));
    if (!newList) {
        perror("Error on malloc");
        return NULL;
    }

    newList->head = NULL;
    newList->tail = NULL;

    return newList;
}

struct charNode* searchCharacter(struct charList* charlist, char c) {

    struct charNode* charAux = charlist->head;

    while (charAux) {
        if (charAux->character == c)
            return charAux;

        charAux = charAux->next;
    }
    
    return NULL;
}

// insert the key into the head of the keyList
void headKeyInsertion(struct keyList* keylist, int key) {

    struct keyNode* newKey = malloc(sizeof(struct keyNode));
    if (!newKey) {
        perror("Error on malloc");
        exit (1);
    }
    newKey->value = key;
    //in case the list is empty
    if (!keylist->head) {
        newKey->next = NULL;
        keylist->head = newKey;
        keylist->tail = newKey;
    } else {
        newKey->next = keylist->head;
        keylist->head = newKey;
    }
    keylist->size += 1;
}

// insert the key into the tail of the keyList
void tailKeyInsertion(struct keyList* keylist, int key) {

    struct keyNode* newKey = malloc(sizeof(struct keyNode));
    if (!newKey) {
        perror("Error on malloc");
        exit (1);
    }
    newKey->value = key;
    newKey->next = NULL;
    //in case the list is empty
    if (!keylist->head) {
        keylist->head = newKey;
        keylist->tail = newKey;
    } else {
        keylist->tail->next = newKey;
        keylist->tail = newKey;
    }
    keylist->size += 1;
}   


// head insertion into character list
struct charNode* headCharacterInsertion(struct charList* charlist, char c) {

    struct charNode* newChar = malloc(sizeof(struct charNode));
    if (!newChar) {
        perror("Error on malloc");
        exit (1);
    }
    newChar->character = c;
    newChar->keylist = newKeyList();

    //in case the list is empty
    if (!charlist->head) {
        newChar->next = NULL;
        charlist->head = newChar;
        charlist->tail = newChar;
    } else {
        newChar->next = charlist->head;
        charlist->head = newChar;
    }

    return newChar;
}   

// tail insertion into character list
struct charNode* tailCharacterInsertion(struct charList* charlist, char c) {
    
    struct charNode* newChar = malloc(sizeof(struct charNode));
    if (!newChar) {
        perror("Error on malloc");
        exit (1);
    }
    newChar->character = c;
    newChar->next = NULL;
    newChar->keylist = newKeyList();

    //in case the list is empty
    if (!charlist->head) { 
        charlist->head = newChar;
        charlist->tail = newChar;
    } else {
        charlist->tail->next = newChar;
        charlist->tail = newChar;
    }
    
    return newChar;
}

// sorted insertion into character list
struct charNode* sortedCharacterInsertion(struct charList* charlist, char c) {

    // in case the list is empty or the character is before the head
    if (!charlist->head || c < charlist->head->character) {
        return headCharacterInsertion(charlist, c);
    }
    // in the case the character is after the tail
    if (c > charlist->tail->character) {
        return tailCharacterInsertion(charlist, c);
    }
    struct charNode *aux, *newChar = malloc(sizeof(struct charNode));
    if (!newChar) {
        perror("Error on malloc");
        exit (1);
    }
 
    newChar->character = c;
    newChar->keylist = newKeyList();

    aux = charlist->head;
    while(aux->next && newChar->character > aux->next->character)
        aux = aux->next;
    newChar->next = aux->next;
    aux->next = newChar;

    return newChar;
}

void createKeyListFromBook(FILE* cipher, struct charList* charlist) {

    char c = 0;
    int next = 1, key = 0;
    struct charNode* charnode = NULL;

    while ((c = getc(cipher)) != EOF) {

        if (isspace(c)) {
            next = 1;
            continue;
        }

        if (next) {
            charnode = searchCharacter(charlist, tolower(c));
            if (!charnode)
                charnode = sortedCharacterInsertion(charlist, tolower(c));
            headKeyInsertion(charnode->keylist, key);
            key++;
            next = 0;
        }
    }
    
}

void createKeyListFromFile(FILE* keyFile, struct charList* charlist) {

    struct charNode* charnode;
    int key, newline = 1;
    char c;

    while ((c = getc(keyFile)) != EOF) {

        if (newline) {

            charnode = tailCharacterInsertion(charlist, c);
            newline = 0;
        } 
        else if (isdigit(c)) {

            ungetc(c, keyFile);
            fscanf(keyFile, "%d", &key);
            tailKeyInsertion(charnode->keylist, key);
        }
        else if (c == '\n') {
            newline = 1;
        }
    }
}

void createKeyFile(FILE* keyFile, struct charList* charlist) {

    struct charNode* charAux = charlist->head;
    struct keyNode* keyAux;

    while (charAux) {
        keyAux = charAux->keylist->head;
        fprintf(keyFile, "%c: ", charAux->character);
        while (keyAux) {
            fprintf(keyFile, "%d ", keyAux->value);
            keyAux = keyAux->next;
        }
        fprintf(keyFile, "\n");

        charAux = charAux->next;
    }
}

void freeKeyList(struct keyNode *keynode) {

    struct keyNode *tmp;

    while (keynode != NULL) {

        tmp = keynode->next;
        free(keynode);
        keynode = NULL;
        keynode = tmp;
    }
}

void freeCharList(struct charNode* charnode) {

    struct charNode* tmp;

    while (charnode != NULL) {
        
        tmp = charnode->next;
        freeKeyList(charnode->keylist->head);
        free(charnode->keylist);
        charnode->keylist = NULL;
        free(charnode);
        charnode = NULL;
        charnode = tmp;
    }
}