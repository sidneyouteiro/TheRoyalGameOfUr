#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TX 43 /*Tamanho do tabuleiro horizontal*/
#define TY 10 /*Tamanho do tabuleiro vertical*/

int draw(int tabuleiro[TY][TX]);
int init_tabuleiro(int tabuleiro[TY][TX]);
int delay(unsigned int milliseconds);
int dados();

int main()
{
  srandom(time(NULL));
  int tabuleiro[TY][TX]; /* array que guarda o tabuleiro*/
  init_tabuleiro(tabuleiro);
  draw(tabuleiro);
  dados();
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

/* Inicia o vetor tabuleiro*/
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

int dados()
{
  int d1 = random() % 2;
  int d2 = random() % 2;
  int d3 = random() % 2;
  int d4 = random() % 2;
  int total = d1 + d2 + d3 + d4;

  delay(250);
  printf("%d\n", d1);
  delay(250);
  printf("%d\n", d2);
  delay(250);
  printf("%d\n", d3);
  delay(250);
  printf("%d\n", d4);
  delay(250);

  printf("\n%d\n", total);

  return total;

}

int delay(unsigned int milliseconds)
{
    long delay; //tempo que o programa fica parado
    clock_t t0,tn; //t0 é o tempo de inicio do delay, tn é o tempo atual

    delay = milliseconds*(CLOCKS_PER_SEC/1000);

    t0 = tn = clock();

    while( (tn-t0) < delay )
        tn = clock();

    return 0;
}
