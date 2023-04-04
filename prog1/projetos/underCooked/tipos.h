#ifndef TIPOS_H
#define TIPOS_H

#include <stdlib.h>

struct Ingrediente {
    char id;
    struct Ingrediente* prox;
};

struct Receita {
    struct Ingrediente* primeiro;
};

struct Pedido {
    int clienteID;
    int refID;
    struct Pedido *prox;
    struct Pedido *prev;
};

struct Lista {
    struct Pedido *cabeca;
    struct Pedido *cauda;
};

struct Mapa{
    int linhas, colunas;
    char** matriz;
};

struct Personagem{
    int fase, pontos, vidas, x, y;
    struct Receita* receita; //receita atual
    char skin;
};

struct Game{
    struct Personagem* boneco;
    struct Mapa* mapa;
    int clientes;
    struct Receita* cardapio;
    struct Lista* pedidos;
};

#endif  