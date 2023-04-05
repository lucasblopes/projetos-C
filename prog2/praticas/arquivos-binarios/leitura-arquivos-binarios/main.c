#include <stdio.h>
#include <stdlib.h>

#define ARQUIVO "arq.bin"

int main() {
    FILE* arq;
    int posicao, tam = 0;
    char *string = NULL, caractere = 0;

    // abre o arquivo em modo leitura binaria
    arq = fopen(ARQUIVO, "rb");
    if (!arq) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }
 
    // le o primeiro bloco para definir o tamanho inicial do vetor string
    if (fread(&posicao, sizeof(int), 1, arq) != 1) {
        perror("Erro ao ler arquivo");
        exit(1);
    }
    tam = posicao;
    string = malloc(tam * sizeof(char));
    if (!string) {
        perror("Erro ao alocar memoria");
        exit(1);
    }
    if (fread(&caractere, sizeof(char), 1, arq) != 1) {
        perror("Erro ao ler arquivo");
        exit(1);
    }
    string[posicao] = caractere;

    // le os demais blocos e adiciona os caracteres na string
    while (fread(&posicao, sizeof(int), 1, arq) == 1) {
        if (fread(&caractere, sizeof(char), 1, arq) != 1) {
            perror("Erro ao ler arquivo");
            exit(1);
        }
        // se ler uma posicao que seja maior que o tamanho do vetor, realoca o tamanho dele
        if (posicao >= tam) {
            tam = posicao + 1;
            string = realloc(string, tam * sizeof(char));
            if (!string) {
                perror("Erro ao alocar memoria");
                exit(1);
            }
        }
        string[posicao] = caractere;
    }
 
    //imprime a string
    printf("%s\n", string);

    // fecha o arquivo e libera memoria
    fclose(arq);
    free(string);

    return 0;
}
