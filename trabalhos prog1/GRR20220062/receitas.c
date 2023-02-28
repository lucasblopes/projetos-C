#include <stdlib.h>
#include <ncurses.h>
#include "receitas.h"
#include "tipos.h"

//inicia uma pilha Refeição
struct Receita* novaReceita(){

    struct Receita* nova = malloc(sizeof *nova );
        if(!nova) return NULL;

    nova->primeiro = NULL;

    return nova;
}

//0: errou; 1: acertou
int verificarReceita(struct Receita *nova, struct Receita *pedido){

    struct Ingrediente *tmp1, *tmp2;
    tmp1 = nova->primeiro;
    tmp2 = pedido->primeiro;

    if(!tmp1) return 0;

    while(tmp1){
        if(tmp1->id != tmp2->id)
            return 0;
        tmp1 = tmp1->prox;
        tmp2 = tmp2->prox;
    }

    return 1;
}

//adiciona um elemento na cabeça da pilha
void push(struct Receita *ref, char c){

    struct Ingrediente *novo = malloc(sizeof *novo);
        if(!novo){
            printw("Erro de alocação de memória em novoCardapio()\n");
            exit(1);
        }
    novo->id = c;

    //se for o primeiro Ingrediente
    if(!ref->primeiro){
        ref->primeiro = novo;
        ref->primeiro->prox = NULL;
        return;
    }
    //caso ja tenha um Ingrediente
    novo->prox = ref->primeiro;
    ref->primeiro = novo;
}

//imprime os ingredientes de tras para frente
void imprimirIngredientes(struct Ingrediente* ingrediente){

    if(!ingrediente) return;
    imprimirIngredientes(ingrediente->prox);
    printw("%c ", ingrediente->id);
}

//imprime a receita na tela
void imprimirReceita(struct Receita *ref){

    struct Ingrediente *tmp = ref->primeiro;

    printw("[Receita: ");
    imprimirIngredientes(tmp);
    printw("]\n\n");
}

//adiciona as receitas do restaurante no vetor cardapio
struct Receita* novoCardapio(){

    struct Receita* cardapio = malloc(6 * sizeof *cardapio);
        if(!cardapio){
            printw("Erro de alocação de memória em novoCardapio()\n");
            exit(1);
        }

    //xBurguer na posição 0
    push(&cardapio[0], 'p');
    push(&cardapio[0], 'H');
    push(&cardapio[0], 'Q');
    push(&cardapio[0], 'P');
   
    //xSalada na posição 1
    push(&cardapio[1], 'p');
    push(&cardapio[1], 'H');
    push(&cardapio[1], 'S');
    push(&cardapio[1], 'P');

    //combo1 na posição 2
    push(&cardapio[2], 'p');
    push(&cardapio[2], 'H');
    push(&cardapio[2], 'Q');
    push(&cardapio[2], 'P');
    push(&cardapio[2], 'F');
    push(&cardapio[2], 'R');

    //combo2 na posição 3
    push(&cardapio[3], 'p');
    push(&cardapio[3], 'H');
    push(&cardapio[3], 'S');
    push(&cardapio[3], 'P');
    push(&cardapio[3], 'F');
    push(&cardapio[3], 'R');

    //vegetariano na posição 4
    push(&cardapio[4], 'p');
    push(&cardapio[4], 'Q');
    push(&cardapio[4], 'P');
    push(&cardapio[4], 'F');
    push(&cardapio[4], 'R');

    //vegano na posição 5
    push(&cardapio[5], 'S');
    push(&cardapio[5], 'F');
    push(&cardapio[5], 'R');
    
    return cardapio;
}

//libera memoria no cardapio
struct Receita* destruirCardapio(struct Receita* cardapio){

    if(!cardapio) return NULL;
    
    for(int i = 0; i < 6; i++)
        destruirReceita(&cardapio[i]);
        
    free(cardapio);
    
    return NULL;
}

//libera memória na pilha
struct Receita* destruirReceita(struct Receita* ref){
    
    if(!ref->primeiro)
        return NULL;
    
    struct Ingrediente *prox,
                       *atual = ref->primeiro;
    while(atual){
        prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(ref);
    return NULL;
}




