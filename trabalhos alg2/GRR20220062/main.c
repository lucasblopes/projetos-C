#include <stdlib.h>
#include <stdio.h>

struct presentes{

    int valor;
    int peso;
};

struct saco {

    int valorTotal;
    int pesoTotal;
    int qtd;
    int *id;
};

// libera a memoria alocada 
void liberarMemoria(struct saco* sacoIdeal, struct presentes* presentes, int* vetorPermutacoes){

    free(sacoIdeal->id);
    free(sacoIdeal);
    free(presentes);
    free(vetorPermutacoes);
}

// aloca memoria para o sacoIdeal
struct saco *novoSaco (int n){

    struct saco *saco = malloc(sizeof(*saco));
        if (!saco) {
            printf("Erro de malloc!\n");
            exit(1);
        }

    // aloca memoria para ate n presentes no saco
    saco->id = malloc(n * sizeof(saco->id));
        if (!saco->id) {
            printf("Erro de malloc!\n");
            exit(1);
        }

    saco->pesoTotal = 0;
    saco->valorTotal = 0;
    saco->qtd = 0;

    return saco;
}

// insere os dados do input no vetor de struct presentes
struct presentes* novosPresentes(int n){

    struct presentes* dados = malloc(n * sizeof(*dados));
        if(!dados){
            printf("Erro de malloc!\n");
            exit(1);
        }

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &dados[i].valor, &dados[i].peso);
    }
    return dados;
}

// imprime o resultado final
void imprimirResultado(struct saco *sacoIdeal){

    for (int i = 0; i < sacoIdeal->qtd; i++) {
        printf("%d ", sacoIdeal->id[i] + 1);
    }
    printf("\n");

    printf("%d\n", sacoIdeal->valorTotal);
}

// verifica quais sao os melhores presentes para o problema
void escolherPresentes(int* v, struct presentes* presentes, struct saco* sacoIdeal, int n, int pesoLimite){
    
    int peso  = 0,  // contadores 
        valor = 0,
        qtd   = 0,  // quantidade de presentes
        idAux[n];   // vetor auxilizar para salvar o id dos presentes

        for (int i = 0; i < n; i++) {
            if (v[i] == 1) {
                idAux[qtd] = i;
                peso += presentes[i].peso;
                valor += presentes[i].valor;           
                qtd++;
            }
        }

        if (peso <= pesoLimite && valor > sacoIdeal->valorTotal) {
            sacoIdeal->valorTotal = valor;
            sacoIdeal->qtd = qtd;
            for (int i = 0; i < qtd; i++)
                sacoIdeal->id[i] = idAux[i];
        }
}

void resolver(int* v, struct presentes* presentes, struct saco *sacoIdeal, int i, int n, int pesoLimite){

        if (i == n){
            escolherPresentes(v, presentes, sacoIdeal, n, pesoLimite);
            return;
        }
        v[i] = 0;
        resolver(v, presentes, sacoIdeal, i + 1, n, pesoLimite);
        v[i] = 1;
        resolver(v, presentes, sacoIdeal, i + 1, n, pesoLimite);
}

int main(){

        int n, pesoLimite;
        scanf("%d %d", &n, &pesoLimite);

        struct presentes *presentes = novosPresentes(n);
        struct saco *sacoIdeal = novoSaco(n);

        int* vetorPermutacoes = malloc(n * sizeof(int));
            if(!vetorPermutacoes){
                printf("Erro de malloc!\n");
                exit(1);
            }

        resolver(vetorPermutacoes, presentes, sacoIdeal, 0, n, pesoLimite);
        imprimirResultado(sacoIdeal);
        liberarMemoria(sacoIdeal, presentes, vetorPermutacoes);

        return 0;
}