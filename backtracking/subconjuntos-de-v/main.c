#include <stdio.h>
#include <stdlib.h>

struct conjunto{

    int n;
    int *resultado;
    int *binario;
    int *aux;
};

struct conjunto* liberarMemoria(struct conjunto *c){

    free(c->resultado);
    free(c->binario);
    free(c->aux);
    return NULL;
}

struct conjunto* novoConjunto(int n){

    struct conjunto* novo = malloc(sizeof *novo);
        if (!novo) return NULL;

    novo->n = n;

    novo->resultado = malloc(n * sizeof(int));
        if (!novo->resultado) return NULL; 

    novo->binario = malloc(n * sizeof(int));
        if(!novo->binario) return NULL;

    novo->aux = malloc(n * sizeof(int));
        if(!novo->aux) return NULL;

    for(int i = 0; i < n; i++)
        (novo->aux)[i] = i+1;

    return novo;
}

void imprimirVetor(int* v, int n){

    int i;
    for(i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void multiplicarVetores(struct conjunto* c){

    int i;
    for(i = 0; i < c->n; i++)
        (c->resultado)[i] = (c->binario)[i]*(c->aux)[i];
}

void gerarSubConjuntos(struct conjunto* c, int i){

    if (i == c->n){
        multiplicarVetores(c);
        imprimirVetor(c->resultado, c->n);
        return;
    }
    (c->binario)[i] = 0;
    gerarSubConjuntos(c, i+1);
    (c->binario)[i] = 1;
    gerarSubConjuntos(c, i+1);
}

int main(){

    int n = 0,
        i = 0;

    printf("n = ");
    scanf("%d", &n);
    struct conjunto* conjunto = novoConjunto(n);
    
    gerarSubConjuntos(conjunto, i);

    conjunto = liberarMemoria(conjunto);

    return 0;
}