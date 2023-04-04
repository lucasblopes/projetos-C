#include <stdio.h>
#include <string.h>
#include <strings.h>

#define TAM 100

int main(){

    char string[TAM+1]; // considerar o \0
    printf("Digite uma string de ate 100 caracteres:\n");
    scanf("%100s", string);
    printf("string invertida:\n");

    for (int i = 0; i < strlen(string); i++)  
        putchar (string[strlen(string)-i-1]);
    printf("\n");

    return 0;
}