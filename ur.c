#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "textos.c"

/*-------------------Macros-------------------*/

#define TX 43 /*Tamanho do tabuleiro horizontal*/
#define TY 10 /*Tamanho do tabuleiro vertical*/
#define INTT 22 // tamanho do tabuleiro interno
#define ROSA_1 ((x > 1  && x < 5 ) && (y > 0 && y < 3))
#define ROSA_2 ((x > 1  && x < 5 ) && (y > 6 && y < 9))
#define ROSA_3 ((x > 15 && x < 20) && (y > 3 && y < 6))
#define ROSA_4 ((x > 30 && x < 35) && (y > 0 && y < 3))
#define ROSA_5 ((x > 30 && x < 35) && (y > 6 && y < 9))


char tabuleiro[TY][TX]; /* array que guarda o tabuleiro*/


typedef struct _cas
{
  int cordenada_x;
  int cordenada_y1;
  int cordenada_y2;
  int pecaP1;  // 0 > vazia
  int pecaP2; // 0 > vazia
  int rosa;  // 0 = nao é rosa, 1 = rosa
} casa;

casa tab_interno[INTT];

typedef struct _pec
{
  int id; /*numero de peças*/
  casa* Pcasa;

} peca;

char jogador1[21];
char jogador2[21];

peca pecasP1[7];
peca pecasP2[7];

void draw(); //funciona
void init_tabuleiro();//funciona
int  delay(unsigned int milliseconds);//funciona
int  dados();//funciona
void jogar();
void init_jogador(); //funciona
void init_peca(); //
void init_caminhos();//att
void desenhar_peca(int id_peca,int x, int y);//funciona
void desenhar_sempeca(int x,int y,int rosa);//funciona
void init(); //funciona
int  verifica_vitoria();//att
void tela_vitoria(int ply);//att
int  loading(unsigned int milliseconds);//funciona
int  atualiza(int valorDado, peca pecaMovida,int jogador);
void historia();//funciona
int  instrucao();//funciona
int  print_tit();//funciona
int  verificamov(int Dado,peca* pc);

int main()
{
  int menu;
  while(1){
   system("clear");
   print_tit();
   printf("\n\n\n");
   printf("\n1-Jogar\n2-Regras\n3-historia\n4-Sair\n");
   scanf("%d",&menu);
   switch (menu) {
     case 1: jogar();
             break;
     case 2: instrucao();
             break;
     case 3: historia();
             break;
     case 4: return 0;

     default:printf("Escolha uma das opções, por favor");
   }
   menu=0;
   }
   return 0;
}


void draw()
{
  int y;
  int x;
  printf("\033[2J\033[1;1H"); //mantem o tabuleiro no topo da tela
  for (y = 0; y < TY; y++)
  {
    for (x = 0; x < TX; x++)
    {
      if (ROSA_1 || ROSA_2 || ROSA_3 || ROSA_4 || ROSA_5)
        printf(RED "%c" RESET, tabuleiro[y][x]);
      else
        printf("%c", tabuleiro[y][x]);
    }
  }
  printf("\n");
  int placarP1 = 0;
  int placarP2 = 0;
  for(int j = 0; j < 7; j++)
  {
    placarP1 += pecasP1[j].pontuada;
    placarP2 += pecasP2[j].pontuada;
  }
  printf("Placar: p1-%d p2-%d", placarP1, placarP2);
}

void init_tabuleiro()
{
  FILE* tabuleiro_a; /* arquivo que guarda o tabuleiro*/

  if((tabuleiro_a = fopen("Ur_Tabuleiro.txt","r")) == NULL)
  {
     printf("Não foi possivel inicializar o tabuleiro\n");
  }

  else
  {
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
  fclose(tabuleiro_a);
}

void jogar()
{
  srandom(time(NULL));
  int totdado,vencedor;
  int escolha;
  init();
  while (1)
  {
    //draw()->dado();->vericar movimentos possiveis->input do jogador->
    //->atualizar tabuleiro

    draw();
    printf("\nTurno de %s\n",jogador1);
    totdado = dados();
    if(totdado)
    {
      escolha = verificamov(totdado,pecasP1);
      if(escolha != -1)
      {
        atualiza(totdado, pecasP1[escolha], 1);
      }
    }
    else{
      printf("\nPerdeu o turno");
      delay(2000);
    }

    vencedor=verifica_vitoria();
    if(vencedor){
      tela_vitoria(vencedor);
      break;
    }
    draw();
    printf("\nTurno de %s\n",jogador2);
    totdado=dados();
    if(totdado)
    {
      escolha=verificamov(totdado,pecasP2);
      if(escolha != -1)
      {
        atualiza(totdado,pecasP2[escolha],2);
      }
    }
    else
    {
      printf("\nPerdeu o turno");
      delay(2000);
    }
    vencedor=verifica_vitoria();
    if(vencedor)
    {
      tela_vitoria(vencedor);
      break;
    }

  }
}

void init_jogador(){
  printf("Nome do jogador 1:\n");
  scanf("%s", jogador1);
  printf("Nome do jogador 2:\n");
  scanf("%s", jogador2);
  }

void init_peca()
{
  int i,id1,id2;
  id1 = 0;
  id2 = 0;
  for(i = 0; i < 7; i++)
  {
    pecasP1[i].Pcasa = &tab_interno[0].pecaP1;
    pecasP1[i].id = id1;
    id1++;
  }
  for(i=0;i<7;i++)
  {
    pecasP1[i].Pcasa = &tab_interno[0].pecaP2;
    pecasP2[i].id = id2;
    id2++;
  }
}

int dados()
{
  srandom(time(NULL));
  int d1 = random() % 2;
  int d2 = random() % 2;
  int d3 = random() % 2;
  int d4 = random() % 2;
  int total = d1 + d2 + d3 + d4;

  loading(240);
  printf("%d  ", d1);
  fflush(stdout);

  loading(240);
  printf("%d  ", d2);
  fflush(stdout);

  loading(240);
  printf("%d  ", d3);
  fflush(stdout);

  loading(240);
  printf("%d  ", d4);
  fflush(stdout);
  delay(250);

  printf("\n\n%d\n", total);

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

int loading(unsigned int milliseconds)
{
  unsigned int delayT = milliseconds / 240;
  for (int t = 0; t <= delayT; t++)
  {
    for(int i = 0; i < 4; i++)
    {
      switch (i)
      {
        case 0:
        printf("|");
        break;

        case 1:
        printf("/");
        break;

        case 2:
        printf("-");
        break;

        case 3:
        printf("\\");
        break;

      }
      fflush(stdout);

      delay(60);
      printf("\b \b");
    }
  }
  return 0;
}

void init_caminho()
{
  //inicia o caminho inicial
  for (int i = 0; i < 5; i++)
  {
    tab_interno[i].cordenada_x = 17 - 5*i;
    tab_interno[i].cordenada_y1 = 1;
    tab_interno[i].cordenada_y2 = 7;
    tab_interno[i].pecaP1 = -1;
    tab_interno[i].pecaP2 = -1;

    if(i == 4)
    {
      tab_interno[i].rosa = 1;
    }
    else
    {
      tab_interno[i].rosa = 0;
    }
  }

  /*Inicializa o caminho do meio*/
  for (int i = 5; i < 12; i++)
  {
    tab_interno[i].cordenada_x = 2 + 5*i;
    tab_interno[i].cordenada_y1 = 4;
    tab_interno[i].cordenada_y2 = 4;
    tab_interno[i].cordenada_y2 = 4;
    tab_interno[i].pecaP1 = -1;
    tab_interno[i].pecaP2 = -1;

    if(i == 8)
    {
      tab_interno[i].rosa = 1;
    }
    else
    {
      tab_interno[i].rosa = 0;
    }
  }

  /*inicializa caminho final*/
  for (int i = 12; i < 22; i++)
  {
    tab_interno[i].cordenada_x = 37 - 5*i;
    tab_interno[i].cordenada_y1 = 1;
    tab_interno[i].cordenada_y2 = 7;
    tab_interno[i].pecaP1 = -1;
    tab_interno[i].pecaP2 = -1;

    if(i == 20)
    {
      tab_interno[i].rosa = 1;
    }
    else
    {
      tab_interno[i].rosa = 0;
    }
  }
}

void desenhar_peca(int id_peca,int x, int y)
{
    if(id_peca > 0)
    {
      tabuleiro[x][y] = id_peca + '0';
      tabuleiro[x+1][y] = jogador1[0];
      tabuleiro[x][y+1] = jogador1[0];
      tabuleiro[x+1][y+1] = jogador1[0];
    }
    else
    {
      tabuleiro[x][y] = id_peca + '0';
      tabuleiro[x+1][y] = jogador2[0];
      tabuleiro[x][y+1] = jogador2[0];
      tabuleiro[x+1][y+1] = jogador2[0];
    }
}

void desenhar_sempeca(int x,int y,int rosa){
   if(rosa==1)
   {
     tabuleiro[x][y]    = '\\';
     tabuleiro[x+1][y]  =  '/';
     tabuleiro[x][y+1]  =  '/';
     tabuleiro[x+1][y+1]= '\\';
   }
   else
   {
      tabuleiro[x][y]    =' ';
      tabuleiro[x+1][y]  =' ';
      tabuleiro[x][y+1]  =' ';
      tabuleiro[x+1][y+1]=' ';
   }
}

int verifica_vitoria()
{
  for(int i=0; i<7; i++)//verifica se há vencedor
    if(pecasP1[i].pontuada != 1 && pecasP2[i].pontuada != 1)
      return 0;
  for(int i=0; i<7; i++)
  {//identifica o vencedor
    if(pecasP1[i].pontuada == 0)
      return 2;
    if(pecasP2[i].pontuada==0)
      return 1;
  }
  return 0;
}

void init()
{
  init_tabuleiro();
  init_jogador();
  init_peca();
  init_caminhos();
}

int atualiza(int valorDado, peca pecaMovida, int jogador)
{
}

int verificamov(int dado, peca *pc, int jogador)
{
}

void tela_vitoria(int ply)
{
  system("clear");
  if(ply==1) printf("Parabens %s",jogador1);
  else printf("Parabens %s",jogador2);
  delay(5000);
}
