#ifndef KEYS_H
#define KEYS_H

#include <stdio.h>
#include <ctype.h>

struct charNode {

    struct charNode* next;
    struct keyList* keylist;
    char character;
};

struct charList {

    struct charNode* head;
    struct charNode* tail;
    //int size;
};

struct keyNode {

    struct keyNode* next;
    int value;
};


struct keyList {

    struct keyNode* head;
    struct keyNode* tail;
    int size;           
};

struct charList* newCharList();

void createKeyListFromBook(FILE* cipher, struct charList* charlist);

void createKeyFile(FILE* keyFile, struct charList* charlist);

void createKeyListFromFile(FILE* keyFile, struct charList* charlist);

#endif