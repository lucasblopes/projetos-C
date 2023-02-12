struct nodo {
    int dado;
    struct nodo *prox;
    struct nodo *prev;
};

struct lista {
    struct nodo *cabeca;
    struct nodo *cauda;
};

struct nodo* pop();

struct lista* criarLista();

void insereCabeca();

void insereCauda();

void insereOrdenado();

void show();

int busca();

void destruir();
