#ifndef RECEITAS_H
#define RECEITAS_H

struct Receita* novaReceita();

struct Receita* vegano();

int verificarReceita();

void push(struct Receita* ref, char c);

void imprimirReceita(struct Receita* ref);

struct Receita* novoCardapio();

struct Receita* destruirReceita();

struct Receita* destruirCardapio(struct Receita* cardapio);

#endif /* RECEITAS_H */
