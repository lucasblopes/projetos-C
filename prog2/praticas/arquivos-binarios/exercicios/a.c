#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* escrever um arquivo com n (n é um número aleatório > 100) inteiros long aleatórios, armazenados em modo binário; */

#define PATH "numbers.dat"

int main() {

    FILE* arq;
    int n, ret;

    arq = fopen (PATH, "wb");
    if (!arq) {
        perror("Error opening file\n");
        exit (1);
    }

    srand(clock());
    n = 100 + (rand() % 10000);
    
    long int value[n];
    for (int i = 0; i < n; i++)
        value[i] = random() / 100000;

    ret = fwrite (value, sizeof(long int), n, arq);
    if (ret)
        printf("Gravou %d valores com sucesso!\n", ret);
    else
        printf("Erro ao gravar...\n");

    // close file   
    fclose(arq);
    return 0;
}