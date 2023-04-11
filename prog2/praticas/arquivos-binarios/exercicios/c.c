#include <stdio.h>
#include <stdlib.h>

/* escrever na tela os primeiros 10 números e os últimos 10 números contidos no arquivo. */

#define PATH "numbers.dat"
#define SIZE 10

int main() {

    FILE* arq;
    long int value[SIZE];

    arq = fopen(PATH, "r");
    if (!arq) {
        perror("Error opening File...\n");
        exit (1);
    }

    //le os primeiros 10 valores do arquivo
    fread(&value, sizeof(long int), 10, arq);  
    printf("Primeiros 10 valores do arquivo:\n");
    for(int i = 0; i < 10; i++)
        printf("%ld ", value[i]);
    printf("\n\n");
    //ajusta a posição do ponteiro do stream para o final - 10 numeros
    fseek (arq, -10*sizeof(long int), SEEK_END);

    //le os ultimos 10 valores do arquivo
    fread(&value, sizeof(long int), 10, arq);  
    printf("Ultimos 10 valores do arquivo:\n");
    for(int i = 0; i < 10; i++)
        printf("%ld ", value[i]);
    printf("\n\n");

    return 0;
}