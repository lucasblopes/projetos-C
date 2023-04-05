#include <stdio.h>
#include <stdlib.h>
 
//cria um arquivo tabuada.txt
int main ()
{
  FILE *arq ;
  int i, j ;
 
  // abre o arquivo em escrita
  arq = fopen ("tabuada.txt", "w+") ;
  if ( ! arq )
  {
     perror ("Erro ao abrir/criar arquivo") ;
     exit (1) ;
  }
 
  // escreve o cabeçalho
  fprintf (arq, "Tabuada:\n") ;
 
  fprintf (arq, "       ") ;
  for (j=0; j<= 10; j++)
      fprintf (arq, "%4d", j) ;
  fprintf (arq, "\n") ;
 
  fprintf (arq, "       ") ;
  for (j=0; j<= 10; j++)
      fprintf (arq, "----") ;
  fprintf (arq, "\n") ;
 
  // escreve as linhas de valores
  for (i=0; i<= 10; i++)
  {
    fprintf (arq, "%4i | ", i) ;
    for (j=0; j<= 10; j++)
      fprintf (arq, "%4d", i*j) ;
    fprintf (arq, "\n") ;
  }
 
  // fecha o arquivo
  fclose (arq) ;
}