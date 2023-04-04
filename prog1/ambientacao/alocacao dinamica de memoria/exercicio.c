#include <stdio.h>
#include <stdlib.h>

struct registro{
    int idade;
    long int gcc;
    char nome;
};

int main(){ 
    int tmp;
    struct registro *ptr1;
    struct registro *ptr2;

    printf("Digite o tamanho em bytes a ser alocado: ");
    scanf("%d", &tmp);
    ptr1 = malloc(sizeof(tmp));
    ptr2 = realloc(ptr1, 8);
    return 0;
}