#include <stdio.h>
#include <stdlib.h>
 
#define LINESIZE 1024
 
int main ()
{
  FILE *arq ;
  char c ;
 
  // abre o arquivo em leitura
  arq = fopen ("dados.txt", "r") ;
  if ( ! arq )
  {
     perror ("Erro ao abrir arquivo") ;
     exit (1) ;
  }
 
  // lê os caracteres até o fim do arquivo
  c = fgetc (arq) ;		// tenta ler um caractere
  while (c != EOF)		// não é o fim do arquivo
  {
    printf ("%c ", c) ;		// tenta ler o próximo
    c = fgetc (arq) ;
  }
 
  // fecha o arquivo
  fclose (arq) ;
}