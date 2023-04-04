#include <stdio.h>
#include <stdlib.h>
#include "libLista.h"

struct lista* criarLista(){
    struct lista* lista = malloc(sizeof(*lista));
    if (lista == NULL) 
        return NULL;
        
    lista->cabeca = NULL;
    lista->cauda = NULL;
    return lista;
}

void insereCabeca(struct lista* lista, int num){
    struct nodo* novo = malloc(sizeof(*novo));
    novo->dado = num;
    novo->prev = NULL;

    //se a lista estiver vazia
    if(!lista->cabeca){
        lista->cabeca = lista->cauda = novo;
        novo->prox = NULL;
    } else {
    lista->cabeca->prev = novo;
    novo->prox = lista->cabeca;
    lista->cabeca = novo;
    }
    printf("%d inserido na cabeça da lista.\n", novo->dado);
}

void insereCauda(struct lista *lista, int num){
    struct nodo* novo = malloc(sizeof(*novo));
    novo->dado = num;
    novo->prox = NULL;

    //se nao tiver cabeca
    if(!lista->cabeca) {
        lista->cabeca = lista->cauda = novo;
        novo->prev = NULL;
    } else {
        lista->cauda->prox = novo;
        novo->prev = lista->cauda;
        lista->cauda = novo;
    }

    printf("%d foi inserido na cauda!\n", novo->dado);
}

void insereOrdenado(struct lista *lista, int num){
    //caso a lista esteja vazia ou num seja menor que a cabeça
    if(!lista->cabeca || num < lista->cabeca->dado){
        insereCabeca(lista, num);
        return;
    }
    //caso seja maior que a cauda
    if(num > lista->cauda->dado){
        insereCauda(lista, num);
        return;
    }
    struct nodo* novo = malloc(sizeof(*novo)),
                 *tmp = lista->cabeca->prox;

    novo->dado = num;
    while(novo->dado > tmp->dado)
        tmp = tmp->prox;

    tmp->prev->prox = novo;
    novo->prev = tmp->prev;
    tmp->prev = novo;
    novo->prox = tmp;

    printf("%d foi inserido na fila!\n", novo->dado);
}

void show(struct lista* lista){
    if(lista->cabeca == NULL){
        printf("Lista vazia!\n");
        return;
    } 
    
    printf("\nLista:\n");
    for(struct nodo* tmp = lista->cabeca; tmp; tmp = tmp->prox)
        printf("%d ", tmp->dado);
    printf("\n");
}

//remove a cabeça da fila
struct nodo* pop(struct lista* lista){
    if(!lista->cabeca){
        printf("A fila está vazia!\n");
        return NULL;
    }

    struct nodo* tmp = lista->cabeca;
    lista->cabeca = lista->cabeca->prox;

    return tmp;
}

int busca(struct lista* lista, int num){
    struct nodo* tmp = lista->cabeca;
    int i = 0;

    while(tmp){
        if(tmp->dado == num)
            return i;

        tmp = tmp->prox;
        i++;
    }
    
    return -1;
}

void destruir(struct lista* lista){
    struct nodo* remover = malloc(sizeof(*remover)),
                 *tmp = lista->cabeca;
    while(tmp){
        remover = pop(lista);
        tmp = tmp->prox;
        free(remover);
    }
}
