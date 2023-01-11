#include<stdio.h>

int tamanhoString(char string[]){
    int numCaracteres = 0;

    while(string[numCaracteres] != '\0'){
        ++numCaracteres;
    }

    return numCaracteres;
}

int main(){
    char nome[20];

    printf("Digite o seu nome: ");
    scanf("%s", nome);

    printf("Seu nome possui %d caracteres\n", tamanhoString(nome));

    return 1;
}