#include<stdio.h>
#include<stdlib.h>

typedef struct No{
    int valor;
    struct No *proximo;
}No;

typedef struct{
    No *inicio;
    int tam; //geralmente nao se usa tam
}Lista;

void iniciarLista(Lista *lista){
    lista->inicio = NULL;
    lista->tam = 0;
};

void imprimirLista(Lista *lista){
    No *p;
    for(p = lista->inicio; p != NULL; p = p->proximo)
        printf("%d ", p->valor);
    printf("\n");
};

void inserirInicio(Lista *lista, int valor){
    No *novo = malloc(sizeof(No));
    novo->valor = valor;
    novo->proximo = lista->inicio; //o proximo do primeiro elemento é o primeiro anterior, que agr eh o segundo
    lista->inicio = novo;
    lista->tam++;
};

void inserirFim(Lista *lista, int valor){
    No *no, *novo = malloc(sizeof(No));
    novo->valor = valor;
    novo->proximo = NULL;

    if(lista->inicio == NULL){
        lista->inicio = novo;
    } else {
        while(no->proximo != NULL)
            no = no->proximo;
        no->proximo = novo;
    };

    lista->tam++;
};

void inserirOrdenado(Lista *lista, int num) {
    No *aux, *novo = malloc(sizeof(No));

    //se a lista estiver vazia, inicio aponta para o novo compromisso  
    novo->valor = num;
    if(lista->inicio == NULL){
        novo->proximo = NULL;
        lista->inicio = novo;
    }//verifica se o novo eh anterior ao primeiro compromisso
    else if (novo->valor < lista->inicio->valor){
        novo->proximo = lista->inicio;
        lista->inicio = novo;
    }
    else {
        aux = lista->inicio;
        while(aux->proximo && novo->valor > aux->proximo->valor)
            aux = aux->proximo;
        novo->proximo = aux->proximo;
        aux->proximo = novo;
    };
}

int main(){
    Lista lista;
    int op, valor;

    iniciarLista(&lista);

    do{
        printf("0\tinserir no inicio\n1\tinserir no final\n2\tinserir ordenado\n3\tlistar os numeros\n4\tsair\n");
        scanf("%d", &op);
        switch (op){
            case (0):{
                printf("\nDigite o valor que deseja inserir no inicio: ");
                scanf("%d", &valor);
                inserirInicio(&lista, valor);
                printf("\nValor %d inserido no inicio da lista!\n\n", valor);
            } 
            break;
            case (1):{
                printf("Digite o valor que deseja inserir no final da lista: ");
                scanf("%d", &valor);
                inserirFim(&lista, valor);
                printf("\nvalor %d inserido no final da lista!\n\n", valor);
            }
            case (2):{
                printf("Digite o valor que deseja inserir ordenadamente: ");
                scanf("%d", &valor);
                inserirOrdenado(&lista, valor);
                printf("\nvalor %d inserido na lista!\n", valor);
            }
            break;
            case (3):{
                imprimirLista(&lista);
            }
            break;
            case (4):{
                printf("Saindo...\n");
                exit(1);
            }
        }
    } while (op != 3);
    return 0;
}

/*
    -- imprimir lista recursivo --
    No *p;
    for(p = lista->inicio; p != NULL; p = p->proximo)
        printf("%d ", p->valor);
    printf("\n");
*/