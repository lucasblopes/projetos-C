#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef enum { NOP, ENCODE, DECODE } Modo_t;

#define BUFFER_SIZE 10

// PROTÓTIPOS

// Função que comprime 'fIn', gravando o resultado da compressão em 'fOut'
void Encode (FILE *fIn, FILE *fOut);

// Função que descomprime 'fIn', gravando o resultado da descompressão em 'fOut'
void Decode (FILE *fIn, FILE *fOut);

// Função  ser  usada  no  programa para  chamar  Encode()  ou  Decode()
void rle (FILE *fIn, FILE *fOut, void (*func) (FILE *, FILE *));

// PROGRAMA PRINCIPAL
int main(int argc, char *argv[])
{

  int opt;
  char *input = NULL;
  char *output = NULL;
  Modo_t modo = NOP;
  
  while ((opt = getopt(argc, argv, "dei:o:")) != -1) {
    switch (opt) {
    case 'i':
      input = strdup(optarg);
      break;
    case 'o':
      output = strdup(optarg);
      break;
    case 'e':
      modo |= ENCODE;
      break;
    case 'd':
      modo |= DECODE;
      break;
    default:
      fprintf(stderr, "Forma de uso: ./rle [-e | -d] -i <arq_in> -o <arq_out>\n");
      exit(1);
    }		
  }

  // Erro se:
  //  * não forneceu os dois arquivos
  //  * não forneceu uma das opções '-e' ou '-d',
  //  * forneceu as opções '-e' e '-d' na mesma linha de comando
  if ( ! input || ! output || modo == NOP || modo & (modo-1) ) {
    fprintf(stderr, "Forma de uso: ./rle [-e | -d] -i <arq_in> -o <arq_out>\n");
    exit(2);
  }
  
  /* COMPLEMENTE O CÓDIGO PARA DESENVOLVER O PROGRAMA PRINCIPAL A PARTIR DESTE PONTO */

  FILE *fIn = fopen(input, "r");
  if (!fIn)
    exit(1);
  
  FILE *fOut = fopen(output, "w");
  if (!fOut)
    exit(1);

  if (modo == ENCODE )
    rle(fIn, fOut, Encode);
  else if (modo == DECODE)
    rle(fIn, fOut, Decode);

  fclose(fIn);
  fclose(fOut);

  return 0 ;

}

/* DEFINA ABAIXO O CÓDIGO DAS FUNÇÕES Encode(), Decode() e rle()  */

// Função ser usada no programa principal para chamar Encode() ou Decode()
void rle (FILE *fIn, FILE *fOut, void (*func) (FILE *, FILE *))
{
  func(fIn, fOut);
}

// Função que comprime 'fIn', gravando o resultado da compressão em 'fOut'
void Encode (FILE *fIn, FILE *fOut)
{
  unsigned int count = 1;
  char prev, new;

  fread(&prev, sizeof(char), 1, fIn);
  while (fread(&new, sizeof(char), 1, fIn) != 0) {
    if (new == prev && count < BUFFER_SIZE) {
      count++;
    } else {
      fwrite(&prev, sizeof(char), 1, fOut);
      fwrite(&count, sizeof(unsigned int), 1, fOut);
      count = 1;
    }
    prev = new;
  }

  fwrite(&prev, sizeof(char), 1, fOut);
  fwrite(&count, sizeof(unsigned int), 1, fOut);
}

// Função que descomprime 'fIn', gravando o resultado da descompressão em 'fOut'
void Decode(FILE* fIn, FILE* fOut) 
{
    int bytes_read;
    char c, buffer[BUFFER_SIZE];

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, fIn)) != 0) {
        for (int i = 0; i < bytes_read; i += 2) {
            c = buffer[i];
            unsigned int count = (unsigned char)buffer[i+1];
            printf("%c%d\n", c, count);
            for (unsigned int j = 0; j < count; j++) {
                fwrite(&c, 1, 1, fOut);
            }
        }
    }
}

/* void Decode (FILE *fIn, FILE *fOut)
{
  int count;
  char c;

  while (fread(&c, 1, 1, fIn) != 0) {
    fread(&count, sizeof(int), 1, fIn);
    for(int i = 0; i < count; i++)
      fwrite(&c, 1, 1, fOut);
  }
}
*/

