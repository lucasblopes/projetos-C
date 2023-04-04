typedef struct Nodo {
    struct Nodo *prox;
    int dado;
}Nodo;

typedef struct Pilha {
    struct Nodo *topo;
}Pilha;

Pilha* newStack();
void push();
Nodo* pop();
void show();
void destruir();
