#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PATH "bkp.bin"

FILE* open_file(char* directory, char* mode) {

    FILE* file = fopen(directory, mode);
    if (!file) {
        perror("Error opening file\n");
        exit (1);
    }

    return file;
}

/* realiza a extracao ou a listagem, dependendo do numeor de argumentos */
void exec_backup(FILE* file, int argc) {

    unsigned int reg_num, reg_size, string_size = 0;
    char c = 0;

    fread(&reg_num, sizeof(unsigned int), 1, file);
    
    for(int i = 0; i < reg_num; i++) {

        /* le o tamanho do registro */
        fread(&reg_size, sizeof(unsigned int), 1, file);
        /* determina a quantidade de caracteres do titulo */
        while (c != '\n') {
            string_size++;
            fread(&c, sizeof(char), 1, file);
        }
        char title[string_size];
        /* volta o ponteiro do stream para o inicio do titulo para ler ele */
        fseek(file, - (string_size * sizeof(char)), SEEK_CUR);
        fread(&title, sizeof(char), string_size, file);
        title[string_size-1] = '\0';

        /* ./backup (faz a extracao) */
        if (argc == 1) {
            FILE* write = fopen(title, "w");
            /* cria um buffer para armazenar o content do register */
            char* content[reg_size - string_size * sizeof(char)];
            fread(content, reg_size - string_size * sizeof(char), 1, file);
            fwrite(content, reg_size - string_size * sizeof(char), 1, write);

            fclose(write);
        }
        /* ./backup -t (faz a listagem de arquivos) */
        else {
            /* avanca o ponteiro do stream para o final do conteudo do registro */
            fseek(file, reg_size - (string_size * sizeof(char)), SEEK_CUR);
            printf("%s (%lu bytes)\n", title, reg_size - string_size*sizeof(char));
        }

        c = 0;
        string_size = 0;
    }
}

int main(int argc, char** argv) {

    if (argc == 1 || (argc == 2 && strcmp(argv[1], "-t") == 0)) {
        FILE* file = open_file(PATH, "r");
        exec_backup(file, argc);
        fclose(file);
    } else {
        printf("Usage: %s\n", argv[0]);
        printf("Usage: %s -t\n", argv[0]);
        exit (1);
    } 
    
    return 0;
}