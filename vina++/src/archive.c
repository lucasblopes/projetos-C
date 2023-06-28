#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "archive.h"
#include "directory.h"
#include "tools.h"

int archive_directory_read(struct Directory *dir) {

    fread(&dir->pos, sizeof(long), 1, dir->archive);

    fseek(dir->archive, dir->pos, SEEK_SET);

    fread(&dir->n, sizeof(long), 1, dir->archive);

    dir->m = malloc((dir->n)  *sizeof(struct Member));
    if (!dir->m) {
        return 1;
    }
    for (long i = 0; i < dir->n; i++) {
        fread(&dir->m[i].plength, sizeof(int), 1, dir->archive);
        dir->m[i].path = malloc(dir->m[i].plength);
        if (!dir->m[i].path) {
            free(dir->m[i].path);
            return 1;
        }
        fread(dir->m[i].path, dir->m[i].plength, 1, dir->archive);
        fread(&dir->m[i].order, sizeof(long), 1, dir->archive);
        fread(&dir->m[i].pos, sizeof(long), 1, dir->archive);
        fread(&dir->m[i].uid, sizeof(uid_t), 1, dir->archive);
        fread(&dir->m[i].mode, sizeof(mode_t), 1, dir->archive);
        fread(&dir->m[i].size, sizeof(size_t), 1, dir->archive);
        fread(&dir->m[i].mtime, sizeof(time_t), 1, dir->archive);
    }
    return 0;
}

/* insere um membro no diretório e escreve o seu conteúdo no archive */
int archive_insert(struct Directory *dir, const char *path, int flag_i) {

    if (!dir || !path) {
        return 1;
    }

    /* abre o arquivo externo */
    FILE *file = fopen(path, "rb");
    if (!file) {
        perror("Não foi possível abrir o arquivo externo!");
        return 1;
    }

    /* obtem as propriedades do arquivo externo */
    struct stat st_file;
    if (stat(path, &st_file) == -1) {
        perror("Não foi possivel obter informacoes sobre o arquivo externo");
        fclose(file);
        return 1;
    }

    long index = directory_search_path(dir, path);

    /* substitui se for -i ou -a e o arquivo externo for mais recente */
    if (index != -1) {
        if (flag_i || difftime(st_file.st_mtime, dir->m[index].mtime) > 0) { 
            archive_remove(dir, index);
        } 
    }

    /* escreve o novo membro no diretório */
    if (directory_insert(dir, st_file, path) != 0) {
        perror("Falha ao adicionar novo membro no diretório!");
        fclose(file);
        return 1;
    }

    /* copia o conteúdo do arquivo externo no archive */
    if (copy_file(dir->archive, file, dir->m[dir->n-1].pos, 0, st_file.st_size) != 0) {
        perror("Falha ao escrever dados no archive");
        fclose(file);
        return 1;
    }
    fclose(file);

    /* se substituiu ajusta a ordem no diretório */
    if (index != -1) {
        if (directory_move(dir, index, dir->n-1) != 0) {
            perror("Falha ao mover o membro substituído para a sua posição incial.");
            return 1;
        }
    }
    dir->modified = 1;
    return 0;
}

int archive_extract(struct Directory *dir, char *path) {

    if (!dir->archive || !dir->n) {
        perror("Archive vazio ou não encontrado");
        return 1;
    }
    if (!path) {
        /* extrai todos os membros */
        for (long i = 0; i < dir->n; i++) {
            
            /* cria hierarquaia de diretórios e abre o arquivo */
            FILE *file = create_file(dir->m[i].path);
            if (!file) {
                return 1;
            }

            copy_file(file, dir->archive, 0, dir->m[i].pos, dir->m[i].size);
            fclose(file);
        }
    } else {
        /* extrai membro especificado */
        long index = directory_search_path(dir, path);
        if (index == -1) {
            perror("Membro não encontrado no archive!");
            return 1;
        }

        /* cria hierarquaia de diretórios e abre o arquivo */
        FILE *file = create_file(path);
        if (!file) {
            return 1;
        }

        copy_file(file, dir->archive, 0, dir->m[index].pos, dir->m[index].size);
        fclose(file);
    }
    return 0;
}

int archive_remove(struct Directory *dir, long index) {

    if (!dir->archive || !dir || index < 0) {
        return 1;
    }

    FILE *write = fopen(dir->path, "r+b");
    if (!write) {
        return 1;
    }

    long write_pos = dir->m[index].pos;

    /* temp armazena a ordem crescente dos membros */
    long *order_tmp = malloc(dir->n  *sizeof(long));
    if (!order_tmp) {
        free(order_tmp);
        fclose(write);
        return 1;
    }
    for(long i = 0; i < dir->n; i++) {
        order_tmp[i] = dir->m[i].order;
    }

    qsort(order_tmp, dir->n, sizeof(long), long_compare);
    long i = 0;

    /* realiza o deslocamento à esquerda para preencher o espaço removido */
    do {
        if (order_tmp[i] > dir->m[index].order) {
            long ind = directory_search_order(dir, order_tmp[i]);
            copy_file(write, dir->archive, write_pos, dir->m[ind].pos, dir->m[ind].size);
            dir->m[ind].pos = write_pos;
            write_pos += dir->m[ind].size;
        }
        i++;
    } while (i < dir->n);

    ftruncate(fileno(dir->archive), (off_t) write_pos);
    fclose(write);

    free(order_tmp);
    free(dir->m[index].path); 

    /* ajusta o diretório */
    for (long i = index; i < dir->n - 1; i++) {
        dir->m[i] = dir->m[i+1];
    }
    dir->n--;
    dir->modified = 1;

    /* atualiza archive */
    dir->pos -= dir->m[index].size;
    fseek(dir->archive, 0, SEEK_SET);
    fwrite(&dir->pos, sizeof(long), 1, dir->archive);

    return 0;
}  

/* escreve o diretório atualizado no final do archive */
int archive_directory_write(struct Directory *dir) {

    if (!dir->archive || !dir) {
        return 1;
    }

    if (dir->m && dir->n > 0) {
        long b = directory_last_member(dir);
        dir->pos = dir->m[b].pos + dir->m[b].size;
    } else {
        dir->pos = sizeof(long);
    }
    fseek(dir->archive, dir->pos, SEEK_SET);
 
    fwrite(&dir->n, sizeof(long), 1, dir->archive);

    for(int i = 0; i < dir->n; i++) {
        fwrite(&dir->m[i].plength, sizeof(int), 1, dir->archive);
        fwrite(dir->m[i].path, dir->m[i].plength, 1, dir->archive);
        fwrite(&dir->m[i].order, sizeof(long), 1, dir->archive);
        fwrite(&dir->m[i].pos, sizeof(long), 1, dir->archive);
        fwrite(&dir->m[i].uid, sizeof(uid_t), 1, dir->archive);
        fwrite(&dir->m[i].mode, sizeof(mode_t), 1, dir->archive);
        fwrite(&dir->m[i].size, sizeof(size_t), 1, dir->archive);
        fwrite(&dir->m[i].mtime, sizeof(time_t), 1, dir->archive);
    }

    fseek(dir->archive, 0, SEEK_SET);
    fwrite(&dir->pos, sizeof(long), 1, dir->archive);
    return 0;
}

