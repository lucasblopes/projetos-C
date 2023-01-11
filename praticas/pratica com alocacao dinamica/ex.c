#include<stdio.h>
#include<stdlib.h>

struct registro{
    char *nome;
    int idade;
    int matricula;  
};

int main(){
    struct registro *ptr, *ptr2;
    int n;

    printf("Digite um inteiro:\n");
    scanf("%d", &n);

    ptr = malloc(n*sizeof(int));
    printf("%p\n", &ptr);

    ptr2 = realloc(ptr, 8);

    printf("%p\n", &ptr);

    return  0;
}