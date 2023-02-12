#include<stdio.h>
#include<stdlib.h>
#include "libPilha.h"

Pilha *newStack(){
    Pilha *pilha = malloc(sizeof(*pilha));
    if (pilha == NULL) 
        return NULL;
        
    pilha->topo = NULL;
    return pilha;
}

void show(Pilha *p){
    Nodo *tmp;
    if(p->topo == NULL)
        printf("A pilha está vazia!\n");
    else {
        tmp = p->topo;
        while(tmp){
            printf("%d ", tmp->dado);
            tmp = tmp->prox;
        }
        printf("\n");
    }
}

void push(Pilha *p, int num){
    Nodo *novo = malloc(sizeof(*novo));
    novo->dado = num;

    if(p->topo == NULL){
        novo->prox = NULL;
        p->topo = novo;
    }
    else {
    novo->prox = p->topo;
    p->topo = novo;
    }
    printf("%d adicionado no topo da pilha!\n", novo->dado);
}

Nodo* pop(Pilha *p){
    Nodo *aux = p->topo;
    p->topo = p->topo->prox;
    return aux;
}

void destruir(Pilha *p){
    if(p->topo){
        Nodo *prox,
             *atual = p->topo;
        while(atual){
            prox = atual->prox;
            free(atual);
            atual = prox;
        }
        printf("Pilha destruída! Memória liberada\n");
        p->topo = NULL;
    }
    else{
        printf("A pilha já está vazia!\n");
    }       
}
