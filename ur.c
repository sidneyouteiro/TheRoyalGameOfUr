#include <stdio.h>
#include <stdlib.h>


int main()
{
  FILE* tabuleiro;
  int c;
  if((tabuleiro = fopen("Ur_Tabuleiro.txt","r")) == NULL)
  {
    printf("Não foi possivel inicializar o tabuleiro\n");
    return 1;
  }
  printf("\n");
  while(1)
  {
    c = fgetc(tabuleiro);
    if (feof(tabuleiro))
    {
      break;
    }
    printf("%c", c);
  }

  return 0;
}
