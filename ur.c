#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*-------------------Macros*/
#define TX 43 /*Tamanho do tabuleiro horizontal*/
#define TY 10 /*Tamanho do tabuleiro vertical*/
#define ROSA_1 (x < 6 && y < 4)
#define ROSA_2 (x < 6 && y > 5)
#define ROSA_3 ((x > 14 && x < 21) && (y > 2 && y < 7))
#define ROSA_4 (x > 33 && y < 4)
#define ROSA_5 (x > 33 && y > 5)
#define VITORIA (jogador1->pecas_ganhas==7 || jogador2->pecas_ganhas==7)

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
/*v vazio,r rival, id da peca*/
/*char caminho_p1[16];  vetor do caminho proprio do jogador 1
char caminho_p2[16];  vetor do caminho proprio do jogador 2*/

typedef struct _pec
{
  int id; /*numero de peças*/
  int pontuada;
  casa* Pcasa;
}peca;

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
char jogador1[21];
char jogador2[21];

peca pecasP1[7];
peca pecasP2[7];

casa inicialp1[4];
casa inicialp2[4];

casa meio[8];

casa finalp1[2];
casa finalp2[2];

void draw();
void init_tabuleiro();
int delay(unsigned int milliseconds);
int dados();
void jogar();
void init_jogador(); //att
void init_peca(); //att
void init_caminhos();//att
void desenhar_peca(char id_peca,int x, int y);//att
char verificamov(int dado);
int validamov(int i, int dice,int p);
void movp1(char mov,int dice);
void movp2(char mov,int dice);
void desenhar_sempeca(int posic,int ply);
void init();

void pecachegada(char id);
void tela_vitoria();

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
  int totdado;
  char escolha;
  init();
  while (1)
  {
    draw();//turno do jogador 1
    totdado=dados();
    escolha=verificamov(totdado,jg1);
    if(escolha!='n') movp1(escolha,jg1,totdado);
    else delay(5000);
    if(VITORIA){
       tela_vitoria(jogador1);
       break;}
    draw();//turno do jogador 2
    totdado=dados();
    escolha=verificamov(totdado,jg2);
    if(escolha!='n') movp2(escolha,jg2,totdado);
    else delay(5000);
    if(VITORIA){
      tela_vitoria();
      break;
}
  }
  free(jogador1);
  free(jogador2);
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
    (pecasP2[i].Pcasa)=NULL;
    (pecasP2[i].no_jogo)=0;
    (pecasP2[i].id)=id2+'0';
    id2--;
  }
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

void init_caminhos()
{
  //inicia o caminho inicial p1
  for (int i = 0; i < 4; i++)
  {
    inicialp1[i]->cordenada_x = 1;
    inicialp1[i]->cordenada_y = 17-5*i;
    inicialp1[i]->peca = 0;
    if(i = 3)
    {
      inicialp1[i]->rosa = 1;
      inicialp1[i]->finalVetor = 1;
      inicialp1[i]->p_casa = meio;
    }
    else
    {
      inicialp1[i]->rosa = 0;
      inicialp1[i]->finalVetor = 0;
      inicialp1[i]->p_casa = NULL;
    }
    inicialp1[i]->p1_casa = NULL;
    inicialp1[i]->p2_casa = NULL;
  }

  //inicia o caminho inicial p2
  for (int i = 0; i < 4; i++)
  {
    inicialp2[i]->cordenada_x = 7;
    inicialp2[i]->cordenada_y = 17-5*i;
    inicialp2[i]->peca = 0;
    if(i = 3)
    {
      inicialp2[i]->rosa = 1;
      inicialp2[i]->finalVetor = 1;
      inicialp2[i]->p_casa = meio;
    }
    else
    {
      inicialp2[i]->rosa = 0;
      inicialp2[i]->finalVetor = 0;
      inicialp2[i]->p_casa = NULL;
    }
    inicialp2[i]->p1_casa = NULL;
    inicialp2[i]->p2_casa = NULL;
  }
/*

int cordenada_x;
int cordenada_y;
int peca; // 0 = vazia, positivo p1, negativo p2
int rosa; // 0 = nao é rosa, 1 = rosa
int finalVetor;
struct casa *p_casa;
struct casa *p1_casa;
struct casa *p2_casa;

casa inicialp1[4];
casa inicialp2[4];

casa meio[8];

casa finalp1[2];
casa finalp2[2];
*/

}

void desenhar_peca(char id_peca,int x, int y){
    if(id_peca>0){
      tabuleiro[x][y]=id_peca;
      tabuleiro[x+1][y]=jogador1[0];
      tabuleiro[x][y+1]=jogador1[0];
      tabuleiro[x+1][y+1]=jogador1[0];
    }
    else{
      tabuleiro[x][y]=id_peca;
      tabuleiro[x+1][y]=jogador2[0];
      tabuleiro[x][y+1]=jogador2[0];
      tabuleiro[x+1][y+1]=jogador2[0];
  }
}

char verificamov(int dado,peca* jg){
  char peca_movivel[7]={"nnnnnnn"};
  char opcao;
  int k=0;
  int i;
  printf("\nMovimentos possiveis:");
  if(jg[0].id=='1'){//player1
    for(i=1;i<15;i++){
      if(caminho_p1[i]!='v' && caminho_p1[i]!='r')
        if(validamov(i,dado,1)==1){
          printf(" %c",caminho_p1[i]);
          peca_movivel[k]=caminho_p1[i];
          k++;
      }

    }
    if(caminho_p1[dado]=='v' && peca_movivel[6]=='n'){
      printf(" (A)dicionar peca.");
      peca_movivel[6]='a';
      k++;
 }}
   else{
     for(i=1;i<15;i++){
       if(caminho_p2[i]!='v' && caminho_p2[i]!='r')
         if(validamov(i,dado,2)==1){
           printf(" %c",caminho_p2[i]);
           peca_movivel[k]=caminho_p2[i];
           k++;}
     }
     if(caminho_p2[dado]=='v' && peca_movivel[6]=='n'){
       printf(" (A)dicionar peca.");
       peca_movivel[6]='a';
       k++;
     }
    }
   if(k==0){
    printf(" Nao existe movimentos possiveis");
    return 'n';
  }
   else{
     while (1) {
     printf("\nSelecione o movimento desejado: ");
     scanf("%c",&opcao);
     for(i=0;i<7;i++)
       if(peca_movivel[i]==opcao)
        return opcao;
     printf("\nMovimento impossivel");
   }

}
}

int validamov(int i, int dice,int p){
  if(p==1){
    if(caminho_p1[i+dice]='v' || (caminho_p1[i+dice]='r' && (i+dice)!=8))
      return 1;
    else
      return 0;}
  else{
    if(caminho_p2[i+dice]='v' || (caminho_p2[i+dice]='r' && (i+dice)!=8))
      return 1;
    else
      return 0;
}}


void movp1(char mov,peca* jg1,int dice,player* ply1){
   int k=0;
   if(mov!='a'){
     while(mov!=caminho_p1[k]) k++;
     caminho_p1[k+dice]=caminho_p1[k];
     caminho_p1[k]='v';
     if(4<k<=12) caminho_p2[k]='v';
     if(4<k+dice<=12) caminho_p2[k+dice]='r';
     if(k+dice==15){
       pecachegada(mov,jg1);
       ply1->pecas_ganhas++;}
     else desenhar_peca(ply1,mov,k+dice,1);
     desenhar_sempeca(k,1);
   }
   else{
     int z=0;
     while(jg1[z].no_jogo!=0) z++;
     caminho_p1[dice]=jg1[z].id;
     jg1[z].no_jogo=1;
     desenhar_peca(ply1,jg1[z].id,dice,1);
   }
}

void movp2(char mov,peca* jg2,int dice,player* ply2){
  int k=0;
  if(mov!='a'){
    while(mov!=caminho_p2[k]) k++;
    caminho_p2[k+dice]=caminho_p2[k];
    caminho_p2[k]='v';
    if(4<k<=12) caminho_p1[k]='v';
    if(4<k+dice<=12) caminho_p1[k+dice]='r';
    if(k+dice==15){
      pecachegada(mov,jg2);
      ply2->pecas_ganhas++;}
    else desenhar_peca(ply2,mov,k+dice,2);
    desenhar_sempeca(k,2);
  }
  else{
    int z=0;
    while(jg2[z].no_jogo!=0) z++;
    caminho_p2[dice]=jg2[z].id;
    jg2[z].no_jogo=1;
    desenhar_peca(ply2,jg2[z].id,dice,2);
  }
}

void desenhar_sempeca(int posic,int ply){
 int x,y;
 if(ply==1)
 {
   if(posic==4)
   {
     tabuleiro[1][2]="\\";
     tabuleiro[2][2]="/";
     tabuleiro[1][3]="/";
     tabuleiro[2][3]="\\";
   }

   if(posic==13)
   {
   tabuleiro[1][37]="\\";
   tabuleiro[2][37]="/";
   tabuleiro[1][38]="/";
   tabuleiro[2][38]="\\";
   }

   if(posic==8)
   {
     tabuleiro[4][17]="\\";
     tabuleiro[5][17]="/";
     tabuleiro[4][18]="/";
     tabuleiro[5][18]="\\";
   }

   if(posic<4)
   {
     x=1;
     y=17-posic*5;
     tabuleiro[x][y]=" ";
     tabuleiro[x+1][y]=" ";
     tabuleiro[x][y+1]=" ";
     tabuleiro[x+1][y+1]=" ";
   }

   if(4<posic<8)
   {
     x=4;
     y=2+5*(posic-4);
     tabuleiro[x][y]=" ";
     tabuleiro[x+1][y]=" ";
     tabuleiro[x][y+1]=" ";
     tabuleiro[x+1][y+1]=" ";
   }

   if(8<posic<13)
   {
     x=4;
     y=2+5*(posic-4);
     tabuleiro[x][y]=" ";
     tabuleiro[x+1][y]=" ";
     tabuleiro[x][y+1]=" ";
     tabuleiro[x+1][y+1]=" ";
   }

   if(posic==14)
   {
     x=1;y=32;
     tabuleiro[x][y]=" ";
     tabuleiro[x+1][y]=" ";
     tabuleiro[x][y+1]=" ";
     tabuleiro[x+1][y+1]=" ";
   }
  }
  else
  {
    if(posic==4)
    {
      tabuleiro[7][2]="\\";
      tabuleiro[8][2]="/";
      tabuleiro[7][3]="/";
      tabuleiro[8][3]="\\";
    }

    if(posic==13)
    {
      tabuleiro[7][37]="\\";
      tabuleiro[8][37]="/";
      tabuleiro[7][38]="/";
      tabuleiro[8][38]="\\";
    }

    if(posic==8)
    {
      tabuleiro[4][17]="\\";
      tabuleiro[5][17]="/";
      tabuleiro[4][18]="/";
      tabuleiro[5][18]="\\";
    }

    if(posic<4)
    {
      x=7;
      y=17-posic*5;
      tabuleiro[x][y]=" ";
      tabuleiro[x+1][y]=" ";
      tabuleiro[x][y+1]=" ";
      tabuleiro[x+1][y+1]=" ";
    }

    if(4<posic<8)
    {
      x=4;
      y=2+5*(posic-4);
      tabuleiro[x][y]=" ";
      tabuleiro[x+1][y]=" ";
      tabuleiro[x][y+1]=" ";
      tabuleiro[x+1][y+1]=" ";
    }

    if(8<posic<13)
    {
      x=4;
      y=2+5*(posic-4);
      tabuleiro[x][y]=" ";
      tabuleiro[x+1][y]=" ";
      tabuleiro[x][y+1]=" ";
      tabuleiro[x+1][y+1]=" ";
    }

    if(posic==14)
    {
      x=7;y=32;
      tabuleiro[x][y]    = " ";
      tabuleiro[x+1][y]  = " ";
      tabuleiro[x][y+1]  = " ";
      tabuleiro[x+1][y+1]= " ";
    }
  }
 }

void pecachegada(char id, peca* jg)
{
   int i=0;
   while (jg[i].id != id) i++;
   jg[i].no_jogo=10;
}

void tela_vitoria(player* jg)
{
  system("clear");
  printf("Parabens %s",jg->nome);
  delay(5000);
}

void init(){
  void init_tabuleiro();
  void init_jogador();
  void init_peca();
  void init_caminhos();
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
