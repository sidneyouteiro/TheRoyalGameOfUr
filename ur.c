#include <stdio.h>
#include <stdlib.h>
#include <time.h>
<<<<<<< HEAD
/*V-------------------Macros*/
#define TX 43 /*Tamanho do tabuleiro horizontal*/
#define TY 10 /*Tamanho do tabuleiro vertical*/

int tabuleiro[TY][TX]; /* array que guarda o tabuleiro*/
int sconfronto_p1[6]; /*vetor do caminho proprio do jogador 1*/
int sconfronto_p2[6]; /*vetor do caminho proprio do jogador 2*/
int cconfronto[8]; /*vetor do caminho em que ambos jogadores podem usar*/

typedef struct _jog{
  char nome[21];
  int pecas_ganhas; /*elemento usado pra checar a condicao de vitoria*/
}player;

typedef struct _pec{
  int imunidade; /*0 pode ser tomada, 1 nao pode ser tomada*/
  int id; /*jogador 1 tem pecas com id impar, jogador 2 par*/
  int no_jogo; /*mostra se a peca esta ou nao no tabuleiro. 1 esta, 0 nao esta*/
}peca;

void draw();
void init_tabuleiro();
int delay(unsigned int milliseconds);
int dados();
int delay(unsigned int milliseconds);
void jogar();
void init_jogador(player* play1,player* play2);/*pega as informacoes dos jogadores*/
void init_peca(peca* p1,peca* p2); /*inicializa as pecas de cada jogador*/


int main()
{
  int menu;
  while(1){
   printf("\n1-Jogar\n2-Sair\n");
   scanf("%d",&menu);
   switch (menu) {
     case 1:jogar();
            break;
     case 2:return 0;
     default:printf("Escolha uma das opçoes, por favor");
   }
   menu=0;
   }
   return 0;
=======

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
>>>>>>> 8a2e98600bd7d06d0eda02bb40afacd66a6246b8
}


void draw(){
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
}

<<<<<<< HEAD
void init_tabuleiro(){
  FILE* tabuleiro_a; /* arquivo que guarda o tabuleiro*/

  if((tabuleiro_a = fopen("Ur_Tabuleiro.txt","r")) == NULL)
     printf("Não foi possivel inicializar o tabuleiro\n");
  else{
=======
/* Inicia o vetor tabuleiro*/
int init_tabuleiro(int tabuleiro[TY][TX])
{
  FILE* tabuleiro_a; /* arquivo que guarda o tabuleiro*/

  if((tabuleiro_a = fopen("Ur_Tabuleiro.txt","r")) == NULL)
  {
    printf("Não foi possivel inicializar o tabuleiro\n");
    return 1;
  }
>>>>>>> 8a2e98600bd7d06d0eda02bb40afacd66a6246b8

  int y;
  int x;

  for (y = 0; y < TY; y++ )
  {
    for (x = 0; x < TX; x++)
    {
      tabuleiro[y][x] = fgetc(tabuleiro_a);
    }
  }
}
}

void jogar(){
  srandom(time(NULL));
  player* jogador1;
  player* jogador2;
  peca jg1[7];
  peca jg2[7];
  init_jogador(jogador1,jogador2);
  init_peca(jg1,jg2);
  init_tabuleiro();
  draw();
  while (1) {
    /*jogo*/
  }
}

void init_jogador(player* play1,player* play2){/*erro de segmentacao na hora de ler o nome*/
  printf("Nome do jogador 1:\n");
  scanf("%s",play1->nome);
  printf("Nome do jogador 2:\n");
  scanf("%s",play2->nome);
  (play1->pecas_ganhas)=0;
  (play2->pecas_ganhas)=0;
  }

void init_peca(peca* p1,peca* p2){/*ainda nao foi testa em conjunto com as outras funcoes*/
  int i,id1,id2;
  id1=1;
  id2=0;
  for(i=0;i<7;i++){
    (p1[i].imunidade)=0;
    (p1[i].no_jogo)=0;
    (p1[i].id)=id1;
    id1+=2;
  }
  for(i=0;i<7;i++){
    (p2[i].imunidade)=0;
    (p2[i].no_jogo)=0;
    (p2[i].id)=id2;
    id2+=2;
  }
}

int dados(){
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

int delay(unsigned int milliseconds){
    long delay; //tempo que o programa fica parado
    clock_t t0,tn; //t0 é o tempo de inicio do delay, tn é o tempo atual
     delay = milliseconds*(CLOCKS_PER_SEC/1000);
     t0 = tn = clock();
     while( (tn-t0) < delay )tn = clock();
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
