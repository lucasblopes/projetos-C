#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define MAX 100

int main(){

    int tam = 0;
    char *string = malloc(MAX * sizeof(char));

    printf("Digite uma string de ate 100 caracteres:\n");
    do {
        scanf("%100[^\n]", string);
        char c = string[0];
        for(int i = 0; c != '\0'; i++){
            c = string[i];
            tam++;
        }
        tam--;
    } while (tam < 0 || tam > MAX);
    string = realloc(string, tam * sizeof(char));
    
    printf("tamanho da string digitada = %d\n", tam);

    free(string);

    return 0;
}