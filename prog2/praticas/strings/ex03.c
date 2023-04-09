#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define MAX 100

int main(){

    char *string = malloc(MAX * sizeof(char));

    printf("Digite uma string de ate 100 caracteres:\n");
    do {
        scanf("%100[^\n]", string);
        char c = string[0];
        for(int i = 0; c != '\0'; i++)
            c = string[i];
    } while (strlen(string) < 0 || strlen(string) > MAX);
    string = realloc(string, strlen(string) * sizeof(char));
    
    for(int i = 0; i < strlen(string); i++){
        if (string[i] > 65 && string[i] < 90)
            string[i] = string[i] + 32;
    }

    printf("string em minusculas: %s\n", string);

    free(string);

    return 0;
}