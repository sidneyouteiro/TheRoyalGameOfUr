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
/*-1 vazio, id da peca*/
int sconfronto_p1[6]; /* vetor do caminho proprio do jogador 1*/
int sconfronto_p2[6]; /* vetor do caminho proprio do jogador 2*/
int cconfronto[8]; /* vetor do caminho em que ambos jogadores podem usar*/

typedef struct _jog{
  char nome[21];
  int pecas_ganhas; /*elemento usado pra checar a condicao de vitoria*/
}player;

typedef struct _pec{
  int imunidade; /* 0 pode ser tomada, 1 nao pode ser tomada*/
  char id; /* jogador 1 tem pecas com id impar, jogador 2 par*/
  int no_jogo; /* mostra se a peca esta ou nao no tabuleiro. 1 esta, 0 nao esta*/
}peca;

void draw();
void init_tabuleiro();
int delay(unsigned int milliseconds);
int dados();
void jogar();
void init_jogador(player* play1,player* play2);/*pega as informacoes dos jogadores*/
void init_peca(peca* p1,peca* p2); /*inicializa as pecas de cada jogador*/
void init_caminhos();
void desenhar_peca(player* ply,char id_peca,int x, int y);


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
}
}

void jogar(){
  srandom(time(NULL));
  player* jogador1 = (player*) malloc(sizeof(player));
  player* jogador2 = (player*) malloc(sizeof(player));
  peca jg1[7];
  peca jg2[7];
  init_jogador(jogador1,jogador2);
  init_peca(jg1,jg2);
  init_tabuleiro();
  init_caminhos();
  while (1)
  {
    /*verificar movimentos
      atualizar tabuleiro
      desenhar peças
      verificar vitoria
      tela vitoria(?)
      casa flor*/
    draw();
    dados();
    desenhar_peca(jogador1,'2',1,17);
    draw();
    dados();
    delay(10000);
    break;

  }
  free(jogador1);
  free(jogador2);
}

void init_jogador(player* play1,player* play2){/*erro de segmentacao na hora de ler o nome*/
  printf("Nome do jogador 1:\n");
  scanf("%s", &play1->nome);
  printf("Nome do jogador 2:\n");
  scanf("%s", &play2->nome);
  (play1->pecas_ganhas) = 0;
  (play2->pecas_ganhas) = 0;
  }

void init_peca(peca* p1,peca* p2){
  int i,id1,id2;
  id1=1;
  id2=0;
  for(i=0;i<7;i++){
    (p1[i].imunidade)=0;
    (p1[i].no_jogo)=0;
    (p1[i].id)=id1+'0'; //somar '0' transforma um inteiro em char
    id1+=2;
  }
  for(i=0;i<7;i++){
    (p2[i].imunidade)=0;
    (p2[i].no_jogo)=0;
    (p2[i].id)=id2+'0';
    id2+=2;
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

void init_caminhos(){
 int i;
   for(i=0;i<8;i++){
     cconfronto[i]=-1;
     if(i<6){
       sconfronto_p1[i]=-1;
       sconfronto_p2[i]=-1;
     }
   }

}
void desenhar_peca(player* ply,char id_peca,int x, int y){
  tabuleiro[x][y]=id_peca;
  tabuleiro[x+1][y]=(ply->nome[0]);
  tabuleiro[x][y+1]=(ply->nome[0]);
  tabuleiro[x+1][y+1]=(ply->nome[0]);
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

fileira do meio - l=4 e c=2+5*k, sendo k um inteiro nao negativo
fileira superior esquerda - l=1 , c=2+5k, //
fileira inferior esquerda - l=7 , //

coordenadas da rosa:
 superior esquerda = [1][2]
 superior direita = [1][37]
 meio = [4][17]
 inferior esquerdo = [7][2]
 inferior direito = [7][37]
*/
