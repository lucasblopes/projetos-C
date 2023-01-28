#include "ordenacao.h"

#include <string.h>

void getNome(char nome[]){
	//substitua por seu nome
	strncpy(nome, "Lucas Gabriel Batista Lopes", MAX_CHAR_NOME);
	nome[MAX_CHAR_NOME-1] = '\0';//adicionada terminação manual para caso de overflow
}

//a função a seguir deve retornar o seu número de GRR
unsigned int getGRR(){
	return 20220062;
}

int buscaSequencial(int vetor[], int tam, int valor, int* numComparacoes){
	if (tam == 0) 
		return -1;

    (*numComparacoes)++;
	if (valor >= vetor[tam-1]) 
		return tam-1;

	return buscaSequencial(vetor, tam-1, valor, numComparacoes);
}

int buscaBinariaInicioFinal(int vetor[], int inicio, int final, int valor, int *numComparacoes){
	if(inicio > final)
		return -1;

	int m = floor((inicio + final)/2);

	(numComparacoes)++;
	if (valor == vetor[m])
		return m;

	(numComparacoes)++;
	if (valor < vetor[m])
		return buscaBinariaInicioFinal(vetor, inicio, m-1, valor, numComparacoes);

	return buscaBinariaInicioFinal(vetor, m+1, final, valor, numComparacoes);
}

int buscaBinaria(int vetor[], int tam, int valor, int* numComparacoes){
	int inicio = 0;
	int final = tam-1;

	return buscaBinariaInicioFinal(vetor, inicio, final, valor, *numComparacoes);
}

int insertionSort(int vetor[], int tam){	
	vetor[0] = 99;
	return -1;
}

int selectionSort(int vetor[], int tam){
	vetor[0] = 99;
	return -1;
}

int mergeSort(int vetor[], int tam){
	vetor[0] = 99;
	return -1;
}

int quickSort(int vetor[], int tam){
	vetor[0] = 99;
	return -1;
}

int heapSort(int vetor[], int tam){
	vetor[0] = 99;
	return -1;
}