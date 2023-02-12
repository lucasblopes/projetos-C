#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "pedidos.h"
#include "receitas.h"
#include "tipos.h"

//inicia a lista de pedidos
struct Lista* criarLista(){

    struct Lista* lista = malloc(sizeof *lista);
    if (!lista){
        printw("Erro de alocação de memória na função criarLista()\n");
        exit(1);
    }
        
    lista->cabeca = NULL;
    lista->cauda = NULL;
    return lista;
}

//gera pedidos aleatórios
void gerarPedidos(struct Lista *lista, int clientes){

    for(int i = 0; i < clientes; i++){
        struct Pedido *novo = malloc(sizeof *novo);
            if(!novo){
                printw("Erro de alocação de memória na função gerarPedido()\n");
                exit(1);
            }

        //se a lista estiver vazia será o primeiro cliente
        if(!lista->cabeca)
            novo->clienteID = 1;
        else 
            novo->clienteID = lista->cauda->clienteID + 1;
        
        novo->refID = rand() % 6;

        insereCauda(lista, novo);
    }
}

void insereCauda(struct Lista *lista, struct Pedido *novo){

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
}

//verifica a receita e retorna a quantidade de pontos de acordo com o pedido
int validarReceita(struct Receita* atual, int id, struct Receita* cardapio){

    //errou a receita
    if (verificarReceita(atual, &cardapio[id]) == 0)
        return -1;
    
    switch (id){
        //x-salada e x-burguer valem 4 pontos
        case 0:
        case 1:
            return 4;
        //combo1 e combo2 valem 6 pontos
        case 2:
        case 3:
            return 6;
        //vegetariano vale 5 pontos
        case 4:
            return 5;
        //vegano vale 3 pontos
        case 5:
            return 3;
    }
    return 0;
}

void imprimirPedidos(struct Lista* lista){
    
    if(!lista->cabeca){
        //printw("Lista de pedidos vazia!\n");
        return;
    } 
    
    char* pedido;
    for(struct Pedido* tmp = lista->cabeca; tmp; tmp = tmp->prox){
        switch (tmp->refID){
            case 0:
                pedido = "X-burger";
                break;
            case 1:
                pedido = "X-salada";
                break;
            case 2:
                pedido = "Combo 1";
                break;
            case 3:
                pedido = "Combo 2";
                break;
            case 4:
                pedido = "Vegetariano";
                break;
            case 5:
                pedido = "Vegano";
                break;
        }

        printw("[cliente %d | %11s]\n", tmp->clienteID, pedido);
    }
    printw("\n");
}

//remove a cabeça da fila
struct Pedido* pop(struct Lista* lista){

    if(!lista->cabeca) return NULL;

    struct Pedido* tmp = lista->cabeca;
    lista->cabeca = lista->cabeca->prox;

    return tmp;
}

//libera memória de uma lista
struct Lista* destruirLista(struct Lista* lista){

    if(!lista) return NULL;

    struct Pedido* remover = malloc(sizeof *remover),
                 *tmp = lista->cabeca;
    while(tmp){
        remover = pop(lista);
        tmp = tmp->prox;
        free(remover);
    }

    free(lista);
    return NULL;
}
