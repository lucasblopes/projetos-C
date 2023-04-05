#include <stdio.h>
#include <stdlib.h>

int main ()
{
  FILE *arq ;
  int i, ret;
  float value ;

  // abre o arquivo em leitura
  arq = fopen ("numeros.txt", "r") ;
  if ( ! arq )
  {
     perror ("Erro ao abrir arquivo") ;
     exit (1) ;
  }

  // lê os 10 primeiros valores do arquivo
i = 0 ;
while (i < 10)
{
  ret = fscanf (arq, "%f", &value) ;
 
  // fim de arquivo ou erro?
  if (ret == EOF)
    break ;
 
  // houve leitura?
  if (ret > 0)
  {
    printf ("%d: %f\n", i, value) ;
    i++ ;
  }
  // não houve, tira um caractere e tenta novamente
  else
    fgetc (arq) ; // fgetc le o proximo caractere do stream 
}

  // fecha o arquivo
  fclose (arq) ;
}