#include <stdlib.h>
#include <stdio.h>

struct presente {

    int *valor;
    int *peso;
};

struct saco {

    int valorMax;
    int pesoMax;
    int n;
    int *id;
    struct presente *presente;
};

// aloca memoria as estruturas
struct saco *novoSaco (int n, int pesoMax){

    struct saco *saco = malloc(sizeof(*saco));
        if (!saco) {
            printf("Erro de malloc!\n");
            exit(1);
        }

    saco->presente = malloc(sizeof(*saco->presente));
        if (!saco->presente) {
            printf("Erro de malloc!\n");
            exit(1);
        }

    saco->presente->valor = malloc(n * sizeof(saco->presente->valor));
        if (!saco->presente->valor) {
            printf("Erro de malloc!\n");
            exit(1);
        }

    saco->presente->peso = malloc(n * sizeof(saco->presente->peso));
        if (!saco->presente->peso) {
            printf("Erro de malloc!\n");
            exit(1);
        }

    saco->id = malloc(n * sizeof(saco->id));
        if (!saco->id) {
            printf("Erro de malloc!\n");
            exit(1);
        }

    saco->pesoMax = pesoMax;
    saco->valorMax = 0;
    saco->n = n;

    return saco;
}

// libera a memoria alocada 
void liberarMemoria(struct saco *saco){

    free(saco->presente->peso);
    free(saco->presente->valor);
    free(saco->presente);
    free(saco->id);
    free(saco);
}

// insere os dados do input na struct saco
void lerEntradas(struct saco *saco){

    for (int i = 0; i < saco->n; i++) {
        scanf("%d %d", &saco->presente->valor[i], &saco->presente->peso[i]);
    }
}

//imprime o resultado final
void imprimirResultado(struct saco *sacoIdeal){

    for (int i = 0; i < sacoIdeal->n; i++) {
        printf("%d ", sacoIdeal->id[i] + 1);
    }
    printf("\n");

    printf("%d\n", sacoIdeal->valorMax);
}

// verifica quais sao os melhores presentes para o problema
void escolherPresentes(int* v, struct saco* sacoAtual, struct saco* sacoIdeal){
    
    int peso = 0, // contadores 
        valor = 0,
        j = 0;  // j sera a quantidade de presentes

        for (int i = 0; i < sacoAtual->n; i++) {
            if (v[i] == 1) {
                sacoAtual->id[j] = i;
                peso += sacoAtual->presente->peso[i];
                valor += sacoAtual->presente->valor[i];           
                j++;
            }
        }

        if (peso <= sacoIdeal->pesoMax && valor > sacoIdeal->valorMax) {
            sacoIdeal->valorMax = valor;
            sacoIdeal->n = j;
            for (int i = 0; i < j; i++)
                sacoIdeal->id[i] = sacoAtual->id[i];
        }
}

void resolver(int* v, int i, struct saco *sacoAtual, struct saco *sacoIdeal){

        if (i == sacoAtual->n){
            escolherPresentes(v, sacoAtual, sacoIdeal);
            return;
        }
        v[i] = 0;
        resolver(v, i + 1, sacoAtual, sacoIdeal);
        v[i] = 1;
        resolver(v, i + 1, sacoAtual, sacoIdeal);
}

int main (){

        int pesoMax, n, i = 0;

        scanf("%d %d", &n, &pesoMax);

        struct saco *sacoAtual = novoSaco(n, pesoMax);
        struct saco *sacoIdeal = novoSaco(n, pesoMax);
        int* vetorPermutacoes = malloc(n * sizeof(int));
            if(!vetorPermutacoes){
                printf("Erro de malloc!\n");
                exit(1);
            }

        lerEntradas(sacoAtual);

        resolver(vetorPermutacoes, i, sacoAtual, sacoIdeal);

        imprimirResultado(sacoIdeal);

        liberarMemoria(sacoAtual);
        liberarMemoria(sacoIdeal);
        free(vetorPermutacoes);

        return 0;
}