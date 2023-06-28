#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <libgen.h>
#include <errno.h>

#include "tools.h"

#define BUFFER_SIZE 1024 /* max buffer size */

void print_help() {

    printf("Uso: vina++ <opção> <archive> [membro1 membro2 ...]\n");
    printf("Opções:\n");
    printf("-i : insere/acrescenta um ou mais membros ao archive.\n");
    printf("-a : mesmo comportamento da opção -i, mas substitui apenas se o parâmetro for mais recente.\n");
    printf("-m target : move o membro para imediatamente após o membro target existente no archive.\n");
    printf("-x : extrai os membros indicados de archive. Se não forem indicados, todos são extraídos.\n");
    printf("-r : remove os membros indicados de archive.\n");
    printf("-c : lista o conteúdo de archive em ordem, incluindo as propriedades de cada membro.\n");
    printf("-h : exibe esta mensagem de ajuda.\n");
    exit(1);
}

int copy_file(FILE *write, FILE *read, long write_pos, long read_pos, size_t size) {

    if (!write || !read) {
        return 1;
    }
    char buffer[BUFFER_SIZE];

    fseek(write, write_pos, SEEK_SET);
    fseek(read, read_pos, SEEK_SET);

    size_t remaining_size = size;
    size_t bytes_to_read, write_size;

    while (remaining_size > 0) {
        bytes_to_read = (remaining_size < BUFFER_SIZE) ? remaining_size : BUFFER_SIZE;
        bytes_to_read = fread(buffer, sizeof(char), bytes_to_read, read);
        if (bytes_to_read <= 0) {
            fclose(read);
            perror("Erro ao ler dados do arquivo!");
            return 1;
        }
        write_size = fwrite(buffer, sizeof(char), bytes_to_read, write);
        if (write_size != bytes_to_read) {
            fclose(read);
            perror("Erro ao escrever dados no archive!");
            return 1;
        }
        remaining_size -= bytes_to_read;
    }
    return 0;
}

/* cria hierarquia de diretórios */
int create_directory_hierarchy(char *path) {

    char *current_path = strdup(path);
    if (!current_path) {
        perror("malloc");
        return 1;
    }

    for (long unsigned i = 0; i < strlen(path); i++) {
        if (current_path[i] == '/') {
            current_path[i] = '\0';
            if (mkdir(current_path, S_IRWXU | S_IRWXG | S_IRWXO) && errno != EEXIST) {
                perror("Falha ao criar diretório");
                free(current_path);
                return 1;
            }
            current_path[i] = '/';
        }
    }
    
    if (mkdir(current_path, S_IRWXU | S_IRWXG | S_IRWXO) && errno != EEXIST) {
        perror("Falha ao criar diretório");
        free(current_path);
        return 1;
    }
    
    free(current_path);
    return 0;
}

/* retorna FILE após criar a hierarquia de diretórios local */
FILE *create_file(char *path) {

    size_t psize = strlen(path) + 3;
    char *relative_path = malloc(psize * sizeof(char));
    if (!relative_path) {
        perror("malloc");
        return NULL;
    }

    /* garante que seja criado um caminho relativo (./) */
    if (path[0] != '.') {
        if (path[0] == '/') {
            snprintf(relative_path, psize, ".%s", path);
        } else {
            snprintf(relative_path, psize, "./%s", path);
        }
    }  

    char *dir_name = strdup(relative_path);
    if (!dir_name) {
        perror("malloc");
        free(relative_path);
    }

    dir_name = dirname(dir_name);

    /* cria a hierarquia de diretórios */
    if (create_directory_hierarchy(dir_name) != 0){
        free(dir_name);
        free(relative_path);
        return NULL;
    }

    free(dir_name);

    FILE *file = fopen(relative_path, "wb");
    if (!file) {
        free(relative_path);
        return NULL;
    }

    free(relative_path);

    return file;
}

/* utilizada em qsort em archive_remove */
int long_compare(const void *a, const void *b) {

    long *pa = (long*) a;
    long *pb = (long*) b;
    
    if (*pa > *pb) return  1 ;
    if (*pa < *pb) return -1 ;
    return 0 ;
}

/* imprime o modo em texto */
void print_mode(mode_t mode) {

    printf((S_ISDIR(mode))  ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    return;
}