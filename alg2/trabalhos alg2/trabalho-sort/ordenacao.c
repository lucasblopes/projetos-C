#include "ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void getNome(char nome[]){
	strncpy(nome, "Lucas Gabriel Batista Lopes", MAX_CHAR_NOME);
	nome[MAX_CHAR_NOME-1] = '\0';
}

unsigned int getGRR(){
	return 20220062;
}

// ------ Busca Sequencial ------

int _buscaSequencial(int vetor[], int a, int b, int valor, int *numComparacoes){
	if (a > b)
		return -1;

	(*numComparacoes)++;
	if (valor == vetor[b])
		return b;

	return _buscaSequencial(vetor, a, b-1, valor, numComparacoes);
}

int buscaSequencial(int vetor[], int tam, int valor, int* numComparacoes){
    (*numComparacoes) = 0;	

	return _buscaSequencial(vetor, 0, tam-1, valor, numComparacoes);
}

// ------ Busca Binária ------

int _buscaBinaria(int vetor[], int a, int b, int valor, int *numComparacoes){
	if(a > b)
		return -1;

	int m = (a + b)/2;

	(*numComparacoes)++;
	if (valor == vetor[m])
		return m;

	(*numComparacoes)++;
	if (valor < vetor[m])
		return _buscaBinaria(vetor, a, m-1, valor, numComparacoes);

	return _buscaBinaria(vetor, m+1, b, valor, numComparacoes);
}

int buscaBinaria(int vetor[], int tam, int valor, int *numComparacoes){
	(*numComparacoes) = 0;

	return _buscaBinaria(vetor, 0, tam-1, valor, numComparacoes);
}

void troca(int vetor[], int a, int b){
	int aux = vetor[a];
	vetor[a] = vetor[b];
	vetor[b] = aux;
}

// ------ Insertion Sort ------

void Insere(int vetor[], int a, int b, int *numComparacoes){
	int i = b-1,
        aux = vetor[b];

	while (i >= a && vetor[i] > aux){
		(*numComparacoes)++;
		vetor[i+1] = vetor[i];
		i--;
	}
    vetor[i+1] = aux;
}

void _insertionSort(int vetor[], int a, int b, int *numComparacoes){
	if(a >= b)
		return;
	_insertionSort(vetor, a, b-1, numComparacoes);
	Insere(vetor, a, b, numComparacoes);

	return;
}

int insertionSort(int vetor[], int tam){
	int numComparacoes = 0;

	_insertionSort(vetor, 0, tam-1, &numComparacoes);
	
	return numComparacoes;	
}

// ------ Selection Sort ------

int minimo(int *vetor, int a, int b, int *numComparacoes){
	if (a == b) 
		return a;

	int min = minimo(vetor, a, b-1, numComparacoes);

	(*numComparacoes)++;
	if (vetor[b] < vetor[min])
			min = b;
	
	return min;
}

void _selectionSort(int vetor[], int a, int b, int *numComparacoes){
	if (a >= b)
		return;

	troca(vetor, a, minimo(vetor, a, b, numComparacoes));
	_selectionSort(vetor, a+1, b, numComparacoes);
}

int selectionSort(int vetor[], int tam){
	int numComparacoes = 0;

	_selectionSort(vetor, 0, tam-1, &numComparacoes);

	return numComparacoes;
}

// ------ Merge Sort ------

void intercala(int vetor[], int a, int m, int b, int *numComparacoes){
	if (a >= b) 
		return;

	int tam = b - a + 1,
		*v = malloc(tam * sizeof(*v)),
		i = a,
		j = m + 1;

	for(int k = 0; k < tam; k++) {
		if((j > b) || ((*numComparacoes += 1) && i <= m && vetor[i] < vetor[j])) {
			v[k] = vetor[i];
			i++;
		} else {
			v[k] = vetor[j];
			j++;
		}
		
	}
		for (int k = 0; k < tam; k++)
				vetor[a+k] = v[k];

		free(v);
}

void _mergeSort(int vetor[], int a, int b, int *numComparacoes){
	if (a >= b)
		return;

	int m = (a+b)/2;

	_mergeSort(vetor, a, m, numComparacoes);
	_mergeSort(vetor, m + 1, b, numComparacoes);

	intercala(vetor, a, m, b, numComparacoes);
}

int mergeSort(int vetor[], int tam){
	int numComparacoes = 0;

	_mergeSort(vetor, 0, tam-1, &numComparacoes);

	return numComparacoes;
}

// ------ Quick Sort ------

int particiona(int vetor[], int a, int b, int valor, int *numComparacoes) {
	int m = a - 1;

	for(int i = a; i <= b; i++) {
		(*numComparacoes)++;
		if(vetor[i] <= valor) {
			m++;
			troca(vetor, m, i);
		}
	}

	return m;
}

void _quickSort(int vetor[], int a, int b, int *numComparacoes){
	if (a >= b)
		return;
	
	int m = particiona(vetor, a, b, vetor[b], numComparacoes);
	_quickSort(vetor, a, m-1, numComparacoes);
	_quickSort(vetor, m+1, b, numComparacoes);
}

int quickSort(int vetor[], int tam){
	int numComparacoes = 0;

	_quickSort(vetor, 0, tam-1, &numComparacoes);

	return numComparacoes;
}

// ------ Heap Sort ------

int direita(int i){
	return 2*i + 2;
}

int esquerda(int i){
	return 2*i + 1;
}

void maxHeapify(int vetor[], int i, int n, int *numComparacoes){
	int esq, dir, maior;

	dir = direita(i);
	esq = esquerda(i);

	(*numComparacoes)++;
	if(esq < n && vetor[esq] > vetor[i])
		maior = esq;
	else
		maior = i;

	(*numComparacoes)++;
	if(dir < n && vetor[dir] > vetor[maior])
		maior = dir;

	if(maior != i){
		troca(vetor, i, maior);
		maxHeapify(vetor, maior, n, numComparacoes);
	}
}

void buildMaxHeap(int vetor[], int n, int *numComparacoes) {
	for(int i = n/2 - 1; i >= 0; i--)
		maxHeapify (vetor, i, n, numComparacoes);
}

int heapSort (int vetor[], int tam){
	int numComparacoes = 0;

	buildMaxHeap (vetor, tam-1, &numComparacoes);

	for (int i = tam-1; i >= 0; i--){
		troca(vetor, 0, i);
		maxHeapify(vetor, 0, i, &numComparacoes);
	}
	return numComparacoes;
}