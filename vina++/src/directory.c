#include <string.h>
#include <time.h>
#include <pwd.h>

#include "directory.h"
#include "tools.h"

struct Directory *directory_init(const char *path) {

    if (!path) {
        perror("Caminho do archive inválido");
        return NULL;
    }   
    struct Directory *dir = malloc(sizeof(struct Directory));
    if (!dir) {
        perror("malloc");
        return NULL;
    }
    dir->path = strdup(path);
    if (!dir->path) {
        perror("malloc");
        return NULL;
    }
    dir->archive = fopen(path, "r+b");
    dir->pos = sizeof(long);
    dir->modified = 0;
    dir->n = 0;
    dir->m = NULL;
    return dir;
}

/* retorna o índice de path no diretório */
long directory_search_path(struct Directory *dir, const char *path) {

    if (!dir || !path) {
        perror("diretório ou path inválidos!");
        return 1;
    }
    for(long i = 0; i < dir->n; i++) {
        if (strcmp(dir->m[i].path, path) == 0) {
            return i;
        }
    }
    return -1; /* arquivo não encontrado */
}

/* retorna o indíce correspondente à ordem de inserção */
long directory_search_order(struct Directory *dir, long order) {

    if (!dir) {
        return -1;
    }

    for(long i = 0; i < dir->n; i++) {
        if (dir->m[i].order == order) {
            return i;
        }
    }
    return -1;
}

/* retorna o índice do último membro inserido */
long directory_last_member(struct Directory *dir) {

    long b = 0; /* biggest order index */
    long biggest_order = dir->m[0].order;
        for(long i = 0; i < dir->n; i++) {
            if (dir->m[i].order > biggest_order) {
                biggest_order = dir->m[i].order;
                b = i;
            }
        }
    return b;
}

/* insere membro no final do diretório */
int directory_insert(struct Directory *dir, struct stat st_file, const char *path) {

    dir->m = realloc(dir->m, ((dir->n) + 1)  *sizeof(struct Member));
    if (!dir->m) {
        perror("realloc");
        return 1;
    }

    dir->m[dir->n].plength = strlen(path) + 1;
    dir->m[dir->n].path    = strdup(path);
    if (!dir->m[dir->n].path) {
        perror("malloc");
        free(dir->m[dir->n].path);
        return 1;
    }

    dir->m[dir->n].mtime = st_file.st_mtime;
    dir->m[dir->n].size  = st_file.st_size;
    dir->m[dir->n].uid   = st_file.st_uid;
    dir->m[dir->n].mode  = st_file.st_mode;

    if (dir->n > 0) {
        long b = directory_last_member(dir);
        dir->m[dir->n].order = dir->m[b].order + 1;
        dir->m[dir->n].pos   = dir->m[b].pos + dir->m[b].size;
    } else {
        dir->m[dir->n].pos   = sizeof(long); /* primeiro membro -> depois da posição do diretório */
        dir->m[dir->n].order = 1;
    }

    dir->n++;
    return 0;
}

/* move scr para dest em um vetor */
int directory_move(struct Directory *dir, long dest, long src) {

    if (!dir->archive || !dir->n || dest < 0 || src < 0) {
        return 1;
    }
    if (src == dest) {
        return 0;
    }
    if (src < dest) {
        dest--;
    }

    struct Member temp = dir->m[src];

    if (src < dest) {
        for (long i = src; i < dest; i++) {
            dir->m[i] = dir->m[i+1];
        }
    } else {
        for (long i = src; i > dest; i--) {
            dir->m[i] = dir->m[i-1];
        }
    }
    dir->m[dest] = temp;
    dir->modified = 1;
    return 0;
}

/* imprime as propriedades de todos os membros do archive */
int directory_list(struct Directory *dir) {

    if (!dir || !dir->n || !dir->archive) {
        return 1;
    }
    for (long i = 0; i < dir->n; i++) {
        struct Member m = dir->m[i];
        struct passwd *pw = getpwuid(m.uid);
        struct tm *timeinfo = localtime(&m.mtime);
        char date_modified[17];
        strftime(date_modified, sizeof(date_modified), "%Y-%m-%d %H:%M", timeinfo);
        print_mode(m.mode);
        printf(" %s %8ld (%ld) %s %s\n", pw->pw_name, m.size, i + 1, date_modified, m.path);
    }
    return 0;
}

/* libera a memória alocada ao diretório */
void directory_free(struct Directory **dir) {

    if(!*dir) {
        return;
    }
    if ((*dir)->archive) {
        fclose((*dir)->archive);
    }
    for(long i = 0; i < (*dir)->n; i++) {
        free((*dir)->m[i].path);
    }
    free((*dir)->path);    
    free((*dir)->m);
    free(*dir);
    *dir = NULL;
}