#ifndef PEDIDOS_H
#define PEDIDOS_H

struct Pedido* pop();

struct Lista* criarLista();

void gerarPedidos();

void insereCauda();

int validarReceita();

void imprimirPedidos();

struct Lista* destruirLista();

#endif /* PEDIDOS_H */
