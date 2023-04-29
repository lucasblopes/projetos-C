#ifndef KEYS_H
#define KEYS_H

#include <stdio.h>

struct keyNode {

    struct keyNode* next;
    int value;
};

struct keyList {

    struct keyNode* head;
    struct keyNode* tail;
    int size;           
};

struct charNode {

    struct charNode* next;
    struct keyList* keylist;
    char character;
};

struct charList {

    struct charNode* head;
    struct charNode* tail;
};

struct charList* new_charlist();

void create_keylist_book(FILE* cipher, struct charList* charlist);

void create_keyfile(FILE* key_file, struct charList* charlist);

void create_keylist_file(FILE* key_file, struct charList* charlist);

struct charNode* search_character(struct charList* charlist, char c);

void free_charlist(struct charNode* charnode);

#endif