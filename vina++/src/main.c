#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "archive.h"
#include "directory.h"
#include "tools.h"

int main(int argc, char **argv) {

    if (argc < 3 ) {
        print_help();
    }

    const char *archive_path;
    if (strcmp(argv[1], "-m") != 0) {
        archive_path = argv[2];
    } else {
        archive_path = argv[3];
    }

    struct Directory *directory = directory_init(archive_path);
    if (!directory) {
        return 1;
    }

    if (directory->archive) {
        if (archive_directory_read(directory) != 0) {
            perror("Falha ao ler diretório do archive!");
            return 1;
        }
    } else if (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "-a") == 0) {
        directory->archive = fopen(directory->path, "w+b");
        if (!directory->archive) {
            perror("Falha ao criar archive");
            return 1;
        }
    }
     
    int op;
    while ((op = getopt (argc, argv, "iamxrc:")) != -1) {
        switch (op) {
            case 'i':  
                if (argc < 4) {
                    perror("Argumentos insuficientes para '-i'");
                    print_help();
                    return 1;
                }
                for (int i = 3; i < argc; i++) {
                    if (archive_insert(directory, argv[i], 1) != 0) {
                        printf("Falha ao adicionar o membro '%s' ao archive.\n", argv[i]);
                    }
                }
                break;
            case 'a':  
                if (argc < 4) {
                    perror("Argumentos insuficientes para '-a'");
                    print_help();
                    return 1;
                }
                for (int i = 3; i < argc; i++) {
                    if (archive_insert(directory, argv[i], 0) != 0) {
                        printf("Falha ao adicionar o membro '%s' ao archive.\n", argv[i]);
                    }
                }
                break;
            case 'm':
                if (argc < 5) {
                    perror("Argumentos insuficientes para '-m target'");
                    print_help();
                    return 1;
                }
                long target = directory_search_path(directory, argv[2]) + 1;
                long member = directory_search_path(directory, argv[4]);
                if (directory_move(directory, target, member) != 0) {
                    printf("Falha ao mover o %s\n", argv[4]);
                    return 1;
                }
                break;
            case 'x':
                if (argc < 3) {
                    perror("Argumentos insuficientes para '-x'");
                    print_help();
                    return 1;
                } else if (argc == 3) {
                    if (archive_extract(directory, 0) != 0) {
                        printf("Falha ao extrair os arquivos de '%s'\n", argv[2]);
                    }
                } else {
                    for (int i = 3; i < argc; i++) {
                        if (archive_extract(directory, argv[i]) != 0) {
                            printf("Falha ao extrair o membro '%s' ao archive.\n", argv[i]);
                        }
                    }
                }
                break;
            case 'r':
                if (argc < 4) {
                    perror("Argumentos insuficientes para '-x'");
                    return 1;
                }
                for (int i = 3; i < argc; i++) {
                    if (archive_remove(directory, directory_search_path(directory, argv[i])) != 0) {
                        printf("Falha ao remover o membro '%s' ao archive.\n", argv[i]);
                    }
                }
                break;
            case 'c':  
                if (argc != 3) {
                    print_help();
                    return 1;
                }
                if (directory_list(directory) != 0) {
                    perror("Archive vazio ou não encontrado!");
                    return 1;
                } 
                break;
            default:
                print_help();
                break;
        }
    }

    if (directory->modified > 0) {
        if (archive_directory_write(directory) != 0) {
            perror("Não foi possível atualizar archive!");
            return 1;
        }
    }
    directory_free(&directory);
    return 0;
}
