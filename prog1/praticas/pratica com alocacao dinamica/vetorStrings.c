#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 50

void inicio(char **nomes, int n){
    int i, size;
    char entrada[SIZE];

    for(int i = 0; i < n; i++){
        __fpurge(stdin);
        printf("Nome %d: ", i);
        gets(entrada); //getString : salva a string digitada
        size = strlen(entrada); //stringLength (tamanho da string)
        nomes[i] = malloc((size+1)*sizeof(char));
        strcpy(nomes[i], entrada); //string copy
    }
}

void escreve(char **nomes, int n){
    int i;
    for(i = 0; i < n; i++)
        printf("%s\n", nomes[i]);
}

int main(){
    char **nomes;
    int i, n, size;

    printf("Quantidade de strings: ");
    scanf("%d", &n);

    nomes = malloc(n*sizeof(char*));

    /*
    printf("Tamanho de cada string: ");
    scanf("%d", &size);

    for(i = 0; i < n; i++)
        nomes[i] = malloc(size*sizeof(char));
    
    */
    inicio(nomes, n);
    escreve(nomes, n);

    //desalocando memoria
    //primeiro libera cada string separadamente
    for(i = 0; i < n; i++)
        free(nomes[i]);
    
    free(nomes);

    return 0;
}