#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define PATH "numbers.dat"

/* Utilize stat ou fstat para recuperar o tamanho do arquivo */

int main() {

    FILE* arq;
    struct stat st; 
    int arq_size;

    arq = fopen(PATH, "r");
    if (!arq) {
        perror("Error opening File...\n");
        exit (1);
    }

    if (stat(PATH, &st) == 0) {
        arq_size = st.st_size;
    } else {
        perror("Error on stat()\n");
        exit (1);
    }

    printf("O tamanho do arquivo eh %d bytes!\n", arq_size);

    //fecha o arquivo
    fclose(arq);
    return 0;
}