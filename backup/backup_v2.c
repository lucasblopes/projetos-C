#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH "bkp.bin"

/* OBS: fazer func de free em Register */

struct Register {
    unsigned int qtd;
    unsigned int *size;
    char **title;
    char **content;
};

struct Register *assemble_struct() {

    char c = 0;
    unsigned int string_size = 0;
    struct Register *reg = malloc(sizeof(struct Register));
    if (!reg)
        exit(1);

    /* abre o arquivo bkp.bin em leitura binaria */
    FILE *file = fopen(PATH, "rb");
    if (!file)
        exit(1);

    /* le a quantidade de registros */
    fread(&reg->qtd, sizeof(unsigned int), 1, file);

    reg->size = malloc(reg->qtd * sizeof(unsigned int*));
    if (!reg->size)
        exit(1);

    reg->title = malloc(reg->qtd * sizeof(char*));
    if (!reg->title)
        exit(1);

    reg->content = malloc(reg->qtd * sizeof(char*));
    if (!reg->content)
        exit(1);
    
    for(int i = 0; i < reg->qtd; i++) {
        /* le o tamanho do registro atual */
        fread(&reg->size[i], sizeof(unsigned int), 1, file);
        /* conta a quantidade de caracteres do titulo para alocar memoria */
        while (c != '\n') {
            string_size++;
            fread(&c, sizeof(char), 1, file);
        }

        reg->title[i] = malloc(string_size * sizeof(char));
            if (!reg->title[i])
                exit(1);
        /* volta o stream para ler o titulo */
        fseek(file, - (string_size * sizeof(char)), SEEK_CUR);
        fread(reg->title[i], sizeof(char), string_size, file);
        reg->title[i][string_size-1] = '\0';

        reg->content[i] = malloc(reg->size[i] - string_size * sizeof(char));
        if (!reg->content[i])
            exit(1);
        /* le o conteudo do reg atual */
        fread(reg->content[i], reg->size[i] - string_size * sizeof(char), 1, file);
        string_size = 0;
        c = 0;
    }

    fclose(file);
    return reg;
}

void backup_list(struct Register *reg) {

    for(int i = 0; i < reg->qtd; i++) { /* obs: strlen nao considera o '\0' */
        printf("%s (%lu bytes)\n", reg->title[i], reg->size[i] - (strlen(reg->title[i])+1)*sizeof(char)); 
    }
}

void backup_extract(struct Register *reg) {

    for(int i = 0; i < reg->qtd; i++) {
        FILE* write = fopen(reg->title[i], "w");
        fwrite(reg->content[i], reg->size[i] - (strlen(reg->title[i])+1)*sizeof(char), 1, write);
        fclose(write);
    }
}

void free_register(struct Register *reg) {

}

int main(int argc, char **argv) {

    struct Register *reg = NULL;

    if (argc == 1) {
        reg = assemble_struct();
        backup_extract(reg);
    } else if (argc == 2 && strcmp("-t", argv[1]) == 0) {
        reg = assemble_struct();
        backup_list(reg);
    } else {
        printf("Usage: ./backup\n");
        printf("Usage: ./backup -t\n");
        exit(1);
    }

    free_register(reg);

    return 0;
}