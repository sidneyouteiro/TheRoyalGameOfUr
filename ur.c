#include <stdio.h>
#include <stdlib.h>

#define TX 43 /*Tamanho do tabuleiro horizontal*/
#define TY 10 /*Tamanho do tabuleiro vertical*/

int draw(int tabuleiro[TY][TX]);
int init_tabuleiro(int tabuleiro[TY][TX]);

int main()
{
  int tabuleiro[TY][TX]; /* array que guarda o tabuleiro*/
  init_tabuleiro(tabuleiro);
  draw(tabuleiro);
  return 0;
}


int draw(int tabuleiro[TY][TX])
{
  int y;
  int x;
  printf("\033[2J\033[1;1H"); //mantem o tabuleiro no topo da tela
  for (y = 0; y < TY; y++)
  {
    for (x = 0; x < TX; x++)
    {
      printf("%c", tabuleiro[y][x]);
    }
  }
  printf("\n");

  return 0;
}

int init_tabuleiro(int tabuleiro[TY][TX])
{
  FILE* tabuleiro_a; /* arquivo que guarda o tabuleiro*/

  if((tabuleiro_a = fopen("Ur_Tabuleiro.txt","r")) == NULL)
  {
    printf("Não foi possivel inicializar o tabuleiro\n");
    return 1;
  }
  
  int y;
  int x;

  for (y = 0; y < TY; y++ )
  {
    for (x = 0; x < TX; x++)
    {
      tabuleiro[y][x] = fgetc(tabuleiro_a);
    }
  }
  return 0;
}
