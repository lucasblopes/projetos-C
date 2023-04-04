//alocacao dinamica de vetor
#include <stdio.h>
#include <stdlib.h> //lib padrao do C para alocar memoria em tempo de execucao

struct datas {
    int dia;
    int mes;
};

int main(){
    struct datas *ptr;
    ptr = malloc(10*sizeof(int));

    
    ptr->dia = 5; //ptr[0]
    ptr->mes = 10;
    (ptr+1)->dia = 23; //a[1]
    (ptr+1)->mes = 5;

    for(int i = 0; i < 2; i++)
        printf("%d/%d\n", (ptr+i)->dia, (ptr+i)->mes);
    printf("\n");

    return 0;
}