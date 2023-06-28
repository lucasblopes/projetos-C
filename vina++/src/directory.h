#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

struct Directory {
    FILE *archive;       /* ponteiro para o archive */
    struct Member *m;    /* vetor para as propriedades dos membros */ 
    int modified;        /* se o archive foi modificado atualiza o diretório no final */
    char *path;          /* nome do archive */
    long pos;            /* posição do diretório no archive */
    long n;              /* número de membros */
};

struct Member { 
    char *path;
    int plength;         /* tamanho do path */
    long order;          /* ordem de inserção */
    long pos;            /* posição do membro no archive */
    uid_t uid;           /* user id */
    mode_t mode;         /* permissões */
    size_t size;         /* tamanho do membro */
    time_t mtime;        /* data de modificação */
};

struct Directory *directory_init(const char *path);

long directory_search_path(struct Directory *dir, const char *path);

long directory_search_order(struct Directory *dir, long order);

long directory_last_member(struct Directory *dir);

int directory_insert(struct Directory *dir, struct stat st_file, const char *path);

int directory_move(struct Directory *dir, long dest, long src);

int directory_list(struct Directory *dir);

void directory_free(struct Directory **dir);

#endif