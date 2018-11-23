#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*-------------------Macros*/
#define TX 43 /*Tamanho do tabuleiro horizontal*/
#define TY 10 /*Tamanho do tabuleiro vertical*/
#define ROSA_1 (x < 6 && y < 4)
#define ROSA_2 (x < 6 && y > 5)
#define ROSA_3 ((x > 14 && x < 21) && (y > 2 && y < 7))
#define ROSA_4 ((x > 29 && x < 36) && y < 4)
#define ROSA_5 ((x > 29 && x < 36) && y > 5)


/* cores para uso no terminal*/
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"


char tabuleiro[TY][TX]; /* array que guarda o tabuleiro*/

typedef struct _cas{
  int cordenada_x;
  int cordenada_y;
  int peca; // 0 = vazia, positivo p1, negativo p2
  int rosa; // 0 = nao é rosa, 1 = rosa
  int finalVetor;
  struct casa *p_casa;
  struct casa *p1_casa;
  struct casa *p2_casa;
}casa;

typedef struct _pec
{
  int id; /*numero de peças*/
  int pontuada; //0 n pontuada, 1 pontuada
  casa* Pcasa;
}peca;

char jogador1[21];
char jogador2[21];

peca pecasP1[7];
peca pecasP2[7];

casa inicialp1[4];
casa inicialp2[4];

casa meio[8];

casa finalp1[3];
casa finalp2[3];

void draw();
void init_tabuleiro();
int delay(unsigned int milliseconds);
int dados();
void jogar();
void init_jogador(); //att
void init_peca(); //att
void init_caminhos();//att
void desenhar_peca(int id_peca,int x, int y);//att
void desenhar_sempeca(int x,int y);//att
void init(); //att
int verifica_vitoria();//att
void tela_vitoria(int ply);//att
int loading(unsigned int milliseconds);
void atualiza(int valorDado, peca* pecaMovida);

int main()
{
  int menu;
  while(1){
   system("clear");
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
 }


void draw(){
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
}


void init_tabuleiro(){
  FILE* tabuleiro_a; /* arquivo que guarda o tabuleiro*/

  if((tabuleiro_a = fopen("Ur_Tabuleiro.txt","r")) == NULL)
     printf("Não foi possivel inicializar o tabuleiro\n");
  else{
  int y;
  int x;

  for (y = 0; y < TY; y++ )
  {
    for (x = 0; x < TX; x++)
    {
      tabuleiro[y][x] = fgetc(tabuleiro_a);
    }
  }
} fclose(tabuleiro_a);
}

void jogar(){
  srandom(time(NULL));
  int totdado,vencedor;
  char escolha;
  init();
  while (1)
  {
    //draw()->dado();->vericar movimentos possiveis->input do jogador->
    //->atualizar tabuleiro

    draw();//turno do jogador 1
    totdado=dados();
    //verifica
    //peca* pecaMovida = &pecasP1[n];
    //atualiza(totdado, pecaMovida);

    if(vencedor=verifica_vitoria()) tela_vitoria(vencedor);
    draw();//turno do jogador 2
    totdado=dados();
    //verifica
    //peca* pecaMovida = &pecasP1[n];
    //atualiza(totdado, pecaMovida);

    if(vencedor=verifica_vitoria()) tela_vitoria(vencedor);

      }
}

void init_jogador(){
  printf("Nome do jogador 1:\n");
  scanf("%s", jogador1);
  printf("Nome do jogador 2:\n");
  scanf("%s", jogador2);
  }

void init_peca(){
  int i,id1,id2;
  id1=1;
  id2=-1;
  for(i=0;i<7;i++){
    (pecasP1[i].Pcasa)=NULL;
    (pecasP1[i].pontuada)=0;
    (pecasP1[i].id)=id1+'0'; //somar '0' transforma um inteiro em char
    id1++;
  }
  for(i=0;i<7;i++){
    pecasP2[i].Pcasa=NULL;
    pecasP2[i].pontuada=0;
    pecasP2[i].id=id2+'0';
    id2--;
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

void init_caminhos()
{
  //inicia o caminho inicial p1
  for (int i = 0; i < 4; i++)
  {
    inicialp1[i].cordenada_x = 1;
    inicialp1[i].cordenada_y = 17-5*i;
    inicialp1[i].peca = 0;
    if(i == 3)
    {
      inicialp1[i].rosa = 1;
      inicialp1[i].finalVetor = 1;
      inicialp1[i].p_casa = meio;
    }
    else
    {
      inicialp1[i].rosa = 0;
      inicialp1[i].finalVetor = 0;
      inicialp1[i].p_casa = NULL;
    }
    inicialp1[i].p1_casa = NULL;
    inicialp1[i].p2_casa = NULL;
  }

  //inicia o caminho inicial p2
  for (int i = 0; i < 4; i++)
  {
    inicialp2[i].cordenada_x = 7;
    inicialp2[i].cordenada_y = 17-5*i;
    inicialp2[i].peca = 0;
    if(i == 3)
    {
      inicialp2[i].rosa = 1;
      inicialp2[i].finalVetor = 1;
      inicialp2[i].p_casa = meio;
    }
    else
    {
      inicialp2[i].rosa = 0;
      inicialp2[i].finalVetor = 0;
      inicialp2[i].p_casa = NULL;
    }
    inicialp2[i].p1_casa = NULL;
    inicialp2[i].p2_casa = NULL;
  }

  /* inicializa caminho final p1*/
  for (int i = 0; i < 3; i++)
  {
    finalp1[i].cordenada_x = 1;
    finalp1[i].cordenada_y = 37-5*i;
    finalp1[i].peca = 0;
    if(i == 2)
    {
      finalp1[i].rosa = 1;
      finalp1[i].finalVetor = 1;
    }
    else
    {
      finalp1[i].rosa = 0;
      finalp1[i].finalVetor = 0;
    }
    finalp1[i].p_casa  = NULL;
    finalp1[i].p1_casa = NULL;
    finalp1[i].p2_casa = NULL;
  }

  /* inicializa caminho final p2*/
  for (int i = 0; i < 3; i++)
  {
    finalp2[i].cordenada_x = 7;
    finalp2[i].cordenada_y = 37-5*i;
    finalp2[i].peca = 0;
    if(i == 2)
    {
      finalp2[i].rosa = 1;
      finalp2[i].finalVetor = 1;
    }
    else
    {
      finalp2[i].rosa = 0;
      finalp2[i].finalVetor = 0;
    }
    finalp2[i].p_casa  = NULL;
    finalp2[i].p1_casa = NULL;
    finalp2[i].p2_casa = NULL;
  }

  /*Inicializa o caminho do meio*/
  for (int i = 0; i < 8; i++)
  {
    meio[i].cordenada_x = 4;
    meio[i].cordenada_y = 2 + 5*i;
    meio[i].peca = 0;

    if(i == 3)
    {
      meio[i].rosa = 1;
    }

    if(i == 7)
    {
      meio[i].rosa = 0;
      meio[i].finalVetor = 1;
      meio[i].p1_casa = finalp1;
      meio[i].p2_casa = finalp2;
    }

    else
    {
      meio[i].rosa = 0;
      meio[i].finalVetor = 0;
      meio[i].p1_casa = NULL;
      meio[i].p2_casa = NULL;
    }
    meio[i].p_casa  = NULL;
  }
}

void desenhar_peca(int id_peca,int x, int y){
    if(id_peca>0){
      tabuleiro[x][y]=id_peca;
      tabuleiro[x+1][y]=jogador1[0];
      tabuleiro[x][y+1]=jogador1[0];
      tabuleiro[x+1][y+1]=jogador1[0];
    }
    else{
      tabuleiro[x][y]=fabs(id_peca);
      tabuleiro[x+1][y]=jogador2[0];
      tabuleiro[x][y+1]=jogador2[0];
      tabuleiro[x+1][y+1]=jogador2[0];
  }
}

void desenhar_sempeca(int x,int y){
   if(ROSA_1||ROSA_2||ROSA_3||ROSA_4||ROSA_5){
     tabuleiro[x][y]="\\";
     tabuleiro[x+1][y]="/";
     tabuleiro[x][y+1]="/";
     tabuleiro[x+1][y+1]="\\";
   }
   else{
      tabuleiro[x][y]    = " ";
      tabuleiro[x+1][y]  = " ";
      tabuleiro[x][y+1]  = " ";
      tabuleiro[x+1][y+1]= " ";
    }
}

int verifica_vitoria(){
  for(int i=0;i<7;i++)//verifica se há vencedor
    if(pecasP1[i].pontuada!=1 && pecasP2[i].pontuada!=1)
      return 0;
  for(int i=0;i<7;i++){//identifica o vencedor
    if(pecasP1[i].pontuada==0)
      return 2;
    if(pecasP2[i].pontuada==0)
      return 1;
  }
}

void tela_vitoria(int ply)
{
  system("clear");
  if(ply==1) printf("Parabens %s",jogador1);
  else printf("Parabens %s",jogador2);
  delay(5000);
}

void init(){
  init_tabuleiro();
  init_jogador();
  init_peca();
  init_caminhos();
}

int verificamov(int dado,int ply){
 int v[7]={0,0,0,0,0,0,0};
 int k;
 int j;

 if(ply==1){
   for(int i=0;i<7;i++){
     if(pecasP1[i].Pcasa!=NULL)
       for(j=0;j<dado;i++) pecasP1[i].Pcasa.

   }
}
}
 else{

 }

 if(v[0]==0) printf("Nao ha movimentos possiveis");

}

void atualiza(int valorDado, peca* pecaMovida)
{
  for (int i = 0; i < valorDado; i++)
  {
   pecaMovida.Pcasa=pecaMovida.Pcasa.p_casa;
  }
  desenhar_peca(pecaMovida.id,pecaMovida.Pcasa.cordenada_x,pecaMovida.Pcasa.cordenada_y);
}
/*
+----+----+----+----+         +----+----+
| \/ |    |    |    |         |    | \/ |
| /\ |    |    |    |  1P     |    | /\ |
+------------------------+--------------+
|    |    |    | \/ |    |    |    |    |
|    |    |    | /\ |    |    |    |    |
+------------------------+--------------+
| \/ |    |    |    |  2P     |    | \/ |
| /\ |    |    |    |         |    | /\ |
+----+----+----+----+         +----+----+
fileira superior  - l=1 , c=2+5k, //
fileira do meio - l=4 e c=2+5*k, sendo k um inteiro nao negativo
fileira inferior- l=7 , //

coordenadas da rosa:
 superior esquerda = [1][2]
 superior direita = [1][37]
 meio = [4][17]
 inferior esquerdo = [7][2]
 inferior direito = [7][37]
*/
