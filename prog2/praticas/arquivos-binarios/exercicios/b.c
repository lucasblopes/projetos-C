#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define PATH "numbers.dat"

/* ler o arquivo de inteiros em um vetor, ordenar o vetor e reescrever o arquivo */

int main() {

    FILE* arq;
    struct stat st;
    int numValues;

    arq = fopen(PATH, "r+");
    if (!arq) {
        perror("Error opening File...\n");
        exit (1);
    }

    if (stat(PATH, &st) == 0) {
        numValues = st.st_size / sizeof(long int);
        printf("%d numeros lidos com sucesso!\n", numValues);
    } else {
        perror("Error on stat()\n");
        exit (1);
    }

    long int value[numValues];
    fread(&value, sizeof(long int), numValues, arq);

    for (int i = 0; i < numValues-1; i++) {
    // encontra o menor elemento no restante do vetor
        int menor = i ;
        for (int j = i+1; j < numValues; j++)
            if (value[j] < value[menor])
                menor = j ;
    
        // se existe menor != i, os troca entre si
        if (menor != i) {
            int aux = value[i] ;
            value[i] = value[menor] ;
            value[menor] = aux ;
        }
    }
 
    // retorna o ponteiro ao início do arquivo
    rewind(arq);

    fwrite(value, sizeof(long int), numValues, arq);

    //fecha o arquivo
    fclose(arq);
    return 0;
}