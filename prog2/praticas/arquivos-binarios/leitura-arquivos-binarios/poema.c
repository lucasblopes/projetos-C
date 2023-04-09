#include <stdio.h>
#include <stdlib.h>

#define ARQUIVO "arq.bin"

int main(){

    FILE* arq;
    int posicao, tam = 0;
    char *string = NULL, caractere;

    // abre o arquivo em modo leitura binaria
    arq = fopen(ARQUIVO, "rb");
    if (!arq){
        perror ("Erro ao abrir arquivo");
        exit (1) ;
    }
 
    // le o primeiro bloco para definir o tamanho inicial do vetor string
    fread(&posicao, sizeof(int), 1, arq);
    tam = posicao;
    string = malloc(tam * sizeof(char));
    fread(&caractere, sizeof(char), 1, arq);
    string[posicao] = caractere;

    // le os demais blocos e adiciona os caracteres na string
    while (!feof(arq)){
        fread(&posicao, sizeof(int), 1, arq);
        fread(&caractere, sizeof(char), 1, arq);
        // se ler uma posicao que seja maior que o tamanho do vetor, realoca o tamanho dele
        if (posicao >= tam){
            tam = posicao + 1;
            string = realloc(string, tam * sizeof(char));
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