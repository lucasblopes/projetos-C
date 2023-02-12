#ifndef ORDENACAO_H_
#define ORDENACAO_H_
#define MAX_CHAR_NOME 50

void getNome(char nome[]);

unsigned int getGRR();

int buscaSequencial(int vetor[], int tam, int valor, int* numComparacoes);

int buscaBinaria(int vetor[], int tam, int valor, int* numComparacoes);

int insertionSort(int vetor[], int tam);

int selectionSort(int vetor[], int tam);

int mergeSort(int vetor[], int tam);

int quickSort(int vetor[], int tam);

int heapSort(int vetor[], int tam);

#endif // ORDENACAO_H_