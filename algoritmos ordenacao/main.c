#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ordenacao.h"

//tamanho do vetor
#define MAX 20000

//cria um vetor com MAX elementos de aleatoriedade MAX
int *criarVetorRandom(int tam) {

	int *vetor = malloc(tam * sizeof(*vetor));

	if(vetor == NULL) {
		printf("Falha fatal. Impossível alocar memoria para o vetor aleatório.\n");
		exit(1);
	}
	for(int i = 0; i < tam; i++)
		vetor[i] = rand() % 200000;

	return vetor;
}

//vetor1 recebe uma copia dos elementos do vetor 2
void clonarVetor(int vetor1[], int vetor2[], int tam){

	for (int i = 0; i < tam; i++)
		vetor1[i] = vetor2[i];
}

//cria um vetor ordenado ao contrário
int *criarVetorDecrescente(int tam) {
	int *vetor = malloc(tam * sizeof(*vetor));
	if(vetor == NULL) {
		printf("Falha fatal. Impossível alocar memoria para o vetor reverso.\n");
		exit(1);
	}

	for(int i = 0; i < tam; i++)
        vetor[i] = tam-i-1;

	return vetor;
}

int main(){
	
	char nome[MAX_CHAR_NOME];
	int idxBusca,
		numComp,
		tam = MAX;

	int *vetorAux = malloc(tam * sizeof(*vetorAux));
	if(vetorAux == NULL){
		printf("Falha fatal. Impossível alocar memoria para o vetorAux.\n");
		return 1;
	}

	int *vetorReverso = criarVetorDecrescente(tam);
	int *vetor = criarVetorRandom(tam);
	clonarVetor(vetorAux, vetor, tam);

	getNome(nome);
	printf("\nTrabalho de %s\n", nome);
	printf("GRR %u\n\n", getGRR());

	clock_t start, end;
    double total;

	printf("-=-=-= Insertion Sort =-=-=-\n\n");

	printf("-Vetor Decrescente: \n");
	start = clock();
	numComp = insertionSort(vetorReverso, tam);
	end = clock();
	total = ((double)end - start)/CLOCKS_PER_SEC;
	printf("Número de Comparações: %d\n", numComp);
	printf("Tempo total: %f\n\n", total);

	printf("-Vetor Aleatório: \n");
	start = clock();
	numComp = insertionSort(vetor, tam);
	end = clock();
	total = ((double)end - start)/CLOCKS_PER_SEC;
	printf("Número de Comparações: %d\n", numComp);
	printf("Tempo total: %f\n\n", total);

	free(vetorReverso);
	vetorReverso = criarVetorDecrescente(tam);
	clonarVetor(vetor, vetorAux, tam);
	printf("-=-=-= Selection Sort =-=-=-\n\n");

	printf("-Vetor Decrescente: \n");
	start = clock();
	numComp = selectionSort(vetorReverso, tam);
	end = clock();
	total = ((double)end - start)/CLOCKS_PER_SEC;
	printf("Número de Comparações: %d\n", numComp);
	printf("Tempo total: %f\n\n", total);

	printf("-Vetor Aleatório: \n");
	start = clock();
	numComp = selectionSort(vetor, tam);
	end = clock();
	total = ((double)end - start)/CLOCKS_PER_SEC;
	printf("Número de Comparações: %d\n", numComp);
	printf("Tempo total: %f\n\n", total);

	free(vetorReverso);
	vetorReverso = criarVetorDecrescente(tam);
	clonarVetor(vetor, vetorAux, tam);
	printf("-=-=-= Merge Sort =-=-=-\n\n");

	printf("-Vetor Decrescente: \n");
	start = clock();
	numComp = mergeSort(vetorReverso, tam);
	end = clock();
	total = ((double)end - start)/CLOCKS_PER_SEC;
	printf("Número de Comparações: %d\n", numComp);
	printf("Tempo total: %f\n\n", total);

	printf("-Vetor Aleatório: \n");
	start = clock();
	numComp = mergeSort(vetor, tam);
	end = clock();
	total = ((double)end - start)/CLOCKS_PER_SEC;
	printf("Número de Comparações: %d\n", numComp);
	printf("Tempo total: %f\n\n", total);

	free(vetorReverso);
	vetorReverso = criarVetorDecrescente(tam);
	clonarVetor(vetor, vetorAux, tam);
	printf("-=-=-= Quick Sort =-=-=-\n\n");

	printf("-Vetor Decrescente: \n");
	start = clock();
	numComp = quickSort(vetorReverso, tam);
	end = clock();
	total = ((double)end - start)/CLOCKS_PER_SEC;
	printf("Número de Comparações: %d\n", numComp);
	printf("Tempo total: %f\n\n", total);

	printf("-Vetor Aleatório: \n");
	start = clock();
	numComp = quickSort(vetor, tam);
	end = clock();
	total = ((double)end - start)/CLOCKS_PER_SEC;
	printf("Número de Comparações: %d\n", numComp);
	printf("Tempo total: %f\n\n", total);
	
	free(vetorReverso);
	vetorReverso = criarVetorDecrescente(tam);
	clonarVetor(vetor, vetorAux, tam);
	printf("-=-=-= Heap Sort =-=-=-\n\n");

	printf("-Vetor Decrescente: \n");
	start = clock();
	numComp = heapSort(vetorReverso, tam);
	end = clock();
	total = ((double)end - start)/CLOCKS_PER_SEC;
	printf("Número de Comparações: %d\n", numComp);
	printf("Tempo total: %f\n\n", total);

	start = clock();
	numComp = heapSort(vetor, tam);
	end = clock();
	total = ((double)end - start)/CLOCKS_PER_SEC;
	printf("Número de Comparações: %d\n", numComp);
	printf("Tempo total: %f\n\n", total);
	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");

	//x é o elemento que ele vai buscar no vetor
	int x = rand() % 10000;
	printf("-=-=-= Busca Sequencial =-=-=-\n\n");
	start = clock();
	idxBusca = buscaSequencial(vetor, tam, x, &numComp);
	end = clock();
	total = ((double)end - start)/CLOCKS_PER_SEC;
	printf("Elemento que irá buscar: %d\n", x);
	printf("Índice de Busca: %d\n", idxBusca);
	printf("Número de Comparações: %d\n", numComp);
	printf("Tempo total: %f\n\n", total);

	printf("-=-=-= Busca Binária =-=-=-\n\n");
	start = clock();
	idxBusca = buscaBinaria(vetor, tam, x, &numComp);
	end = clock();
	total = ((double)end - start)/CLOCKS_PER_SEC;
	printf("Elemento que irá buscar: %d\n", x);
	printf("Índice de Busca: %d\n", idxBusca);
	printf("Número de Comparações: %d\n", numComp);
	printf("Tempo total: %f\n\n", total);
	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");

	free(vetor);
	free(vetorAux);
	free(vetorReverso);

	return 0;
}
