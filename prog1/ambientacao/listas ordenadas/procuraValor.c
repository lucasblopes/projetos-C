#include<stdio.h>

struct lista{
    int valor;
    struct lista *proximo;
};

struct lista * procuraValor(struct lista *pLista, int valor){
    while(pLista != (struct lista *)0){
        if(valor == pLista->valor){
            return pLista;
        } else{
            pLista = pLista->proximo;
        }
    }
};

int main(){
    struct lista m1, m2, m3, *resultado, *gancho = &m1;
    int valor;

    m1.valor = 10;
    m2.valor = 20;
    m3.valor = 30;

    m1.proximo = &m2;
    m2.proximo = &m3;
    m3.proximo = 0;

    printf("Digite um valor para pesquisa: ");
    scanf("%d", &valor);

    resultado = procuraValor(gancho, valor);

    if(resultado == (struct lista *)0){
        printf("Valor nao encontrado!\n");
    } else {
        printf("Valor %i encontrado!\n", resultado->valor);
    };

    return 0;
}