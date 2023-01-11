#include<stdio.h>

int main(){
    char linha[100];
    char caractere;
    int i = 0;

    printf("Digite uma string:\n");
    do {
        caractere = getchar();
        linha[i] = caractere;
        i++;
    } while (caractere != '\n'); //enquanto for diferente de enter
    linha[i-1] = '\0';

    printf("%s\n", linha);

    return 1;
}