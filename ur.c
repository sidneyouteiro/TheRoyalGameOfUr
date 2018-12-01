#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "textos.c"

/*-------------------Macros-------------------*/

#define TX 43 /*Tamanho do tabuleiro horizontal*/
#define TY 10 /*Tamanho do tabuleiro vertical*/
#define INTT 16 // tamanho do tabuleiro interno
#define ROSA_1 ((x > 1  && x < 5 ) && (y > 0 && y < 3))
#define ROSA_2 ((x > 1  && x < 5 ) && (y > 6 && y < 9))
#define ROSA_3 ((x > 15 && x < 20) && (y > 3 && y < 6))
#define ROSA_4 ((x > 30 && x < 35) && (y > 0 && y < 3))
#define ROSA_5 ((x > 30 && x < 35) && (y > 6 && y < 9))


char tabuleiro[TY][TX]; /* array que guarda o tabuleiro*/
int placarP1 = 0;
int placarP2 = 0;

typedef struct _casa
{
  int cordenada_x;
  int cordenada_y1;
  int cordenada_y2;
  int pecaP1;  // 0 < vazia
  int pecaP2; // 0 < vazia
  int rosa;  // 0 = nao é rosa, 1 = rosa
} casa;

casa tab_interno[INTT];

typedef struct _pec
{
  int id; /*numero de peças*/
  struct _casa* Prox_casa;

} peca;

char jogador1[21];
char jogador2[21];

peca pecasP1[7];
peca pecasP2[7];

void draw(int player); //funciona
void init_tabuleiro();//funciona
int  delay(unsigned int milliseconds);//funciona
int  dados();//funciona
void jogar();
void init_jogador(); //funciona
void init_peca(); //
void init_caminhos();//att
void desenhar_peca(int id_peca,int y, int x);//funciona
void desenhar_sempeca(int y,int x,int rosa);//funciona
void init(); //funciona
void tela_vitoria(int ply);//att
int  loading(unsigned int milliseconds);//funciona
void historia();//funciona
int  instrucao();//funciona
int  print_tit();//funciona
void creditos();
int verificamov(int dado, int jogador);
int valida(char* c,int var);
int  verifica_vitoria();
void mostrapeca();
int atualiza(int valorDado, int indice, int jogador);
//tranquilo
int main()
{
  int menu;
  while(1){
   system("clear");
   print_tit();
   printf("\n\n\n");
   printf("\n1-Jogar\n2-Regras\n3-historia\n4-Creditos\n5-Sair\n\n->");
   scanf("%d",&menu);
   switch (menu) {
     case 1: jogar();
             break;
     case 2: instrucao();
             break;
     case 3: historia();
             break;
     case 4: creditos();
             break;
     case 5: return 0;

     default:printf("Escolha uma das opções, por favor");
   }
   menu=0;
   }
   return 0;
}


void draw(int player)
{
  int y;
  int x;
  printf("\033[2J\033[1;1H"); //mantem o tabuleiro no topo da tela
  /*mostrapeca();*/
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
  printf("Placar: p1-%d p2-%d", placarP1, placarP2);
  if(player==1)
  {
    printf("\nTurno de %s\n",jogador1);
  }
  else{
    printf("\nTurno de %s\n",jogador2);
  }
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

    /*turno do jogador 1*/
    draw(1);
    totdado = dados();
    if(totdado)
    {
     escolha=verificamov(totdado, 1);
     if(escolha < 0)
     {
       printf("\nNão há movimentos possiveis");
       delay(3000);
     }
     else
     {
       atualiza(totdado,escolha,1);
       mostrapeca();
     }
    }
    else
    {
      printf("\nPerdeu a vez");
      delay(5000);
    }
    draw(2);
     //turno do jogador2
    totdado = dados();
    if(totdado)
    {
     escolha=verificamov(totdado, 2);
     if(escolha < 0)
     {
       printf("\n\n\nNão há movimentos possiveis");
       delay(3000);
     }
     else
     {
       atualiza(totdado,escolha,2);
       mostrapeca();
     }
    }
    else
    {
      printf("\n\n\nPerdeu a vez");
      delay(5000);
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
  id1 = 1;
  id2 = 1;
  for(i = 0; i < 7; i++)
  {
    pecasP1[i].Prox_casa = &tab_interno[0];
    pecasP1[i].id = id1;
    id1++;
  }
  for(i=0;i<7;i++)
  {
    pecasP1[i].Prox_casa = &tab_interno[0];
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

  for (register int i = 0; i < INTT; i++)
  {
    if(i<5)
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
    else
     if(i<13)
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
     else
     {
       tab_interno[i].cordenada_x = 37 - 5*i;
       tab_interno[i].cordenada_y1 = 1;
       tab_interno[i].cordenada_y2 = 7;
       tab_interno[i].pecaP1 = -1;
       tab_interno[i].pecaP2 = -1;

       if(i == 14)
       {
         tab_interno[i].rosa = 1;
       }
       else
       {
         tab_interno[i].rosa = 0;
       }
     }
  }
}

void desenhar_peca(int id_peca,int y, int x)
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

void desenhar_sempeca(int y,int x,int rosa){
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


void init()
{
  init_tabuleiro();
  init_jogador();
  init_peca();
  init_caminho();
}

int atualiza(int valorDado, int indice, int jogador)
{
   int idRival1, idRival2;
   if(jogador == 1)
   {

     pecasP1[indice].Prox_casa = (pecasP1[indice].Prox_casa) + valorDado;
     pecasP1[indice].Prox_casa->pecaP1 = pecasP1[indice].id;
     if(pecasP1[indice].Prox_casa->cordenada_x == 4 && pecasP1[indice].Prox_casa->pecaP2 > 0)
     {
       idRival2 = pecasP1[indice].Prox_casa->pecaP2;
       pecasP2[idRival2].Prox_casa = NULL;
       pecasP1[indice].Prox_casa->pecaP2 = -1;
     }
     if(pecasP1[indice].Prox_casa == &tab_interno[15])
     {
       placarP1++;
     }
   }
   else
   {
     pecasP2[indice].Prox_casa = (pecasP2[indice].Prox_casa) + valorDado;
     pecasP2[indice].Prox_casa->pecaP2 = pecasP2[indice].id;
     if(pecasP2[indice].Prox_casa->cordenada_x == 4 && pecasP2[indice].Prox_casa->pecaP2 > 0)
     {
       idRival1=pecasP2[indice].Prox_casa->pecaP2;
       pecasP1[idRival1].Prox_casa = NULL;
       pecasP2[indice].Prox_casa->pecaP2 = -1;
     }
     if(pecasP2[indice].Prox_casa==&tab_interno[15])
     {
       placarP2++;
     }
   }
   return 0;
}

int verifica_vitoria()
{
  if(tab_interno[15].pecaP1 == 28)
  {
    return 1;
  }
  if(tab_interno[15].pecaP2 == 28)
  {
    return 2;
  }
  return 0;
}


int verificamov(int dado, int jogador)
{
  casa *casaQueVai;
  int pecasJogaveis[7];
  if(jogador == 1)
  {
    for(int i = 0; i < 7; i++)
    {
      pecasJogaveis[i] = 1;
      casaQueVai = (pecasP1[i].Prox_casa) + dado;
      if(casaQueVai > &tab_interno[15] || pecasP1[i].Prox_casa == &tab_interno[15])
      {
        pecasJogaveis[i] = 0;
        continue;
      }
      if(casaQueVai->pecaP1 > 0 && !(casaQueVai == &tab_interno[15]))
      {
        pecasJogaveis[i] = 0;
        continue;
      }
      if(casaQueVai->rosa == 1 && casaQueVai->pecaP2 > 0)
      {
        pecasJogaveis[i] = 0;
        continue;
      }
    }
  }
  else
  {
    for(int i = 0; i < 7; i++)
    {
      pecasJogaveis[i] = 1;
      casaQueVai = (pecasP2[i].Prox_casa) + dado;
      if(casaQueVai > &tab_interno[15] || pecasP2[i].Prox_casa == &tab_interno[15])
      {
        pecasJogaveis[i] = 0;
        continue;
      }
      if(casaQueVai->pecaP2 > 0 && !(casaQueVai == &tab_interno[15]))
      {
        pecasJogaveis[i] = 0;
        continue;
      }
      if(casaQueVai->rosa == 1 && casaQueVai->pecaP1 > 0)
      {
        pecasJogaveis[i] = 0;
        continue;
      }
    }
  }

  int numeroDeMovimentosPossiveis = 0;
  for(int i = 0; i < 7; i++)
  {
    numeroDeMovimentosPossiveis += pecasJogaveis[i];
  }
  if(numeroDeMovimentosPossiveis == 0)
  {
    return -1;
  }

  int escolha;
  printf("\nPeças disponiveis: ");
  for(int i = 0; i < 7; i++)
  {
    if(pecasJogaveis[i] == 1)
    {
      printf("%d ", i + 1 );
    }
  }
  char c[20];
  while(1)
  {
    printf("\n\n");
    escolha=valida(c,escolha);
    if(pecasJogaveis[escolha - 1] == 1)
    {
      break;
    }
    else
    {
      printf("\nEscolha invalida\n");
      printf("Escolha outra peça");
    }
  }

  return (escolha - 1);
}

void tela_vitoria(int ply)
{
  system("clear");
  if(ply==1) printf("Parabens %s",jogador1);
  else printf("Parabens %s",jogador2);
  delay(5000);
}


int valida(char* c,int var)
{

  while(1)
  {
    gets(c);
    if((sscanf(c,"%d",&var))==1)
      break;

  }
  return var;
}

void mostrapeca()
{
  for(register int i=0;i<16;i++)
  {
    if(i==0 || i==15)
    {
      continue;
    }
    if(tab_interno[i].pecaP1==-1 && tab_interno[i].pecaP2==-1)
    {
      desenhar_sempeca(tab_interno[i].cordenada_x,tab_interno[i].cordenada_y1,tab_interno[i].rosa);
      desenhar_sempeca(tab_interno[i].cordenada_x,tab_interno[i].cordenada_y2,tab_interno[i].rosa);
    }
    if(tab_interno[i].pecaP1!=-1 && tab_interno[i].pecaP2==-1)
    {
      desenhar_sempeca(tab_interno[i].cordenada_x,tab_interno[i].cordenada_y2,tab_interno[i].rosa);
      desenhar_peca(tab_interno[i].pecaP1,tab_interno[i].cordenada_x,tab_interno[i].cordenada_y1);
    }
    if(tab_interno[i].pecaP2!=-1 && tab_interno[i].pecaP1==-1)
    {
      desenhar_sempeca(tab_interno[i].cordenada_x,tab_interno[i].cordenada_y1,tab_interno[i].rosa);
      desenhar_peca(tab_interno[i].pecaP2,tab_interno[i].cordenada_x,tab_interno[i].cordenada_y2);
    }
    if(tab_interno[i].pecaP1!=-1 && tab_interno[i].pecaP2!=-1 && (i<5 || i>13))
    {
      desenhar_peca(tab_interno[i].pecaP1,tab_interno[i].cordenada_x,tab_interno[i].cordenada_y1);
      desenhar_peca(tab_interno[i].pecaP2,tab_interno[i].cordenada_x,tab_interno[i].cordenada_y2);
    }
  }
}
