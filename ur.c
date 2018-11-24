#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*-------------------Macros*/
#define TX 43 /*Tamanho do tabuleiro horizontal*/
#define TY 10 /*Tamanho do tabuleiro vertical*/
#define ROSA_1 ((x > 1  && x < 5 ) && (y > 0 && y < 3))
#define ROSA_2 ((x > 1  && x < 5 ) && (y > 6 && y < 9))
#define ROSA_3 ((x > 15 && x < 20) && (y > 3 && y < 6))
#define ROSA_4 ((x > 30 && x < 35) && (y > 0 && y < 3))
#define ROSA_5 ((x > 30 && x < 35) && (y > 6 && y < 9))


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
  int disAtePonto; //distancia ate o fim do tabuleiro, se 0 não é possivel pontuar
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

void draw(); //funciona
void init_tabuleiro();//funciona
int delay(unsigned int milliseconds);//funciona
int dados();//funciona
void jogar();
void init_jogador(); //funciona
void init_peca(); //
void init_caminhos();//att
void desenhar_peca(int id_peca,int x, int y);//att
void desenhar_sempeca(int x,int y,int rosa);//att
void init(); //funciona
int verifica_vitoria();//att
void tela_vitoria(int ply);//att
int loading(unsigned int milliseconds);//funciona
int atualiza(int valorDado, peca* pecaMovida,int posic);
void historia();//funciona
int instrucao();//funciona
int print_tit();//funciona
int verificamov(int valorDado, peca* pecasJogador, int jogador);

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
  int placarP1 = 0;
  int placarP2 = 0;
  for(int j = 0; j < 7; j++)
  {
    placarP1 += pecasP1[j].pontuada;
    placarP2 += pecasP2[j].pontuada;
  }
  printf("Placar: p1-%d p2-%d", placarP1, placarP2);
}

void historia(){
  system("clear");
  printf("\nThe Royal Game of Ur ou Game of Ur, foi popular em todo o Oriente Médio no terceiro milênio A.C e tabuleiros para ele");
  printf(" foram encontrados no Irã, Síria, Egito, Líbano, Sri Lanka, Chipre e Creta. Jogo de Ur eventualmente adquiriu significado\n");
  printf(" supersticioso fornecendo previsões vagas para o futuro dos jogadores se eles pousarem em certas casas do tabuleiro,");
  printf(" como \nVocê encontrará um amigo\n ou \nVocê se tornará poderoso como um leão.\n\nO jogo possui esse nome devido ao seu redescobrimento");
  printf(" em uma das escavações do arqueologo Sir Leonard Woolley no cemiterio real de ur. Entretanto mais tarde arqueologos descobririam copias do jogo em varias localidade do Oriente Medio.\n");
  printf(" E as regras só foram redescobertas em 1980, pelo historiador Irving Finkel através de placa de barro escritas por um escriba babiloniano\n");
  printf("Pressione ENTER key para continuar\n");
  getchar();
  getchar();
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
  int escolha;
  init();
  while (1)
  {
    //draw()->dado();->vericar movimentos possiveis->input do jogador->
    //->atualizar tabuleiro

    draw();
    printf("\nTurno de %s\n",jogador1);
    totdado=dados();
    if(totdado){
      escolha=verificamov(totdado,pecasP1, 1);
      atualiza(totdado, pecasP1, escolha);
    }
    else{
      printf("\nPerdeu o turno");
      delay(5000);
    }

    vencedor=verifica_vitoria();
    if(vencedor){
      tela_vitoria(vencedor);
      break;
    }
    draw();
    printf("\nTurno de %s\n",jogador2);
    totdado=dados();
    if(totdado){
      escolha=verificamov(totdado,pecasP1, 2);
      atualiza(totdado, pecasP1, escolha);
    }
    else{
      printf("\nPerdeu o turno");
      delay(5000);
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

void init_peca(){
  int i,id1,id2;
  id1=1;
  id2=-1;
  for(i=0;i<7;i++)
  {
    (pecasP1[i].Pcasa)=NULL;
    (pecasP1[i].pontuada)=0;
    (pecasP1[i].id)=id1; //somar '0' transforma um inteiro em char
    id1++;
  }
  for(i=0;i<7;i++){
    pecasP2[i].Pcasa=NULL;
    pecasP2[i].pontuada=0;
    pecasP2[i].id=id2;
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
    inicialp1[i].disAtePonto = 0;
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
      inicialp1[i].p_casa = &inicialp1[i+1];
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
    inicialp1[i].disAtePonto = 0;
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
      inicialp2[i].p_casa = &inicialp2[i+1];
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
    finalp1[i].disAtePonto = 2 - i;
    if(i == 1)
    {
      finalp1[i].rosa = 1;
      finalp1[i].finalVetor = 0;
      finalp1[i].p_casa  = &finalp1[i+1];
    }
    else if (i == 2)
    {
      finalp1[i].finalVetor = 1;
      finalp1[i].p_casa = NULL;
    }
    else
    {
      finalp1[i].rosa = 0;
      finalp1[i].finalVetor = 0;
      finalp1[i].p_casa  = &finalp1[i+1];
    }
    finalp1[i].p1_casa = NULL;
    finalp1[i].p2_casa = NULL;
  }

  /* inicializa caminho final p2*/
  for (int i = 0; i < 3; i++)
  {
    finalp2[i].cordenada_x = 7;
    finalp2[i].cordenada_y = 37-5*i;
    finalp1[i].peca = 0;
    finalp1[i].disAtePonto = 2 - i;
    if(i == 1)
    {
      finalp2[i].rosa = 1;
      finalp2[i].finalVetor = 0;
      finalp2[i].p_casa  = &finalp2[i+1];
    }
    else if (i == 2)
    {
      finalp2[i].finalVetor = 1;
      finalp2[i].p_casa = NULL;
    }
    else
    {
      finalp2[i].rosa = 0;
      finalp2[i].finalVetor = 0;
      finalp2[i].p_casa  = &finalp2[i+1];
    }
    finalp2[i].p1_casa = NULL;
    finalp2[i].p2_casa = NULL;
  }

  /*Inicializa o caminho do meio*/
  for (int i = 0; i < 8; i++)
  {
    meio[i].cordenada_x = 4;
    meio[i].cordenada_y = 2 + 5*i;
    meio[i].peca = 0;
    if (i > 5)
    {
      meio[i].disAtePonto = 10 - i;
    }
    else
    {
      meio[i].disAtePonto = 0;
    }

    if(i == 3)
    {
      meio[i].rosa = 1;
      meio[i].finalVetor = 0;
      meio[i].p_casa  = &meio[i+1];
      meio[i].p1_casa = NULL;
      meio[i].p2_casa = NULL;
    }

    else if(i == 7)
    {
      meio[i].rosa = 0;
      meio[i].finalVetor = 1;
      meio[i].p_casa  = NULL;
      meio[i].p1_casa = finalp1;
      meio[i].p2_casa = finalp2;
    }

    else
    {
      meio[i].rosa = 0;
      meio[i].finalVetor = 0;
      meio[i].p_casa  = &meio[i+1];
      meio[i].p1_casa = NULL;
      meio[i].p2_casa = NULL;
    }
  }
}

void desenhar_peca(int id_peca,int x, int y){
    if(id_peca>0)
    {
      tabuleiro[x][y]=id_peca-'0';
      tabuleiro[x+1][y]=jogador1[0];
      tabuleiro[x][y+1]=jogador1[0];
      tabuleiro[x+1][y+1]=jogador1[0];
    }
    else
    {
      tabuleiro[x][y]=fabs(id_peca)-'0';
      tabuleiro[x+1][y]=jogador2[0];
      tabuleiro[x][y+1]=jogador2[0];
      tabuleiro[x+1][y+1]=jogador2[0];
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
  for(int i=0;i<7;i++)//verifica se há vencedor
    if(pecasP1[i].pontuada!=1 && pecasP2[i].pontuada!=1)
      return 0;
  for(int i=0;i<7;i++)
  {//identifica o vencedor
    if(pecasP1[i].pontuada==0)
      return 2;
    if(pecasP2[i].pontuada==0)
      return 1;
  }
  return 0;
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

int atualiza(int valorDado, peca* pecaMovida,int posic)
{
  int segundoDado,escolha,idrival,r;

  if(pecaMovida[posic].Pcasa != NULL)
  {
    desenhar_sempeca(pecaMovida[posic].Pcasa->cordenada_x,pecaMovida[posic].Pcasa->cordenada_y,pecaMovida[posic].Pcasa->rosa);
  }
  for (int i = 0; i < valorDado; i++)
  {
    if(pecaMovida[posic].Pcasa == NULL)
    {
      if(pecaMovida[posic].id > 0)
      {
        pecaMovida[posic].Pcasa = inicialp1;
      }
      else
      {
        pecaMovida[posic].Pcasa = inicialp2;
      }
    }
    else
    {
      if(pecaMovida[posic].Pcasa->cordenada_x == meio[7].cordenada_x && pecaMovida[posic].Pcasa->cordenada_y == meio[7].cordenada_y)
      {
        if(pecaMovida[posic].id>0)
        {
          pecaMovida[posic].Pcasa = pecaMovida[posic].Pcasa->p1_casa;
        }
        else
        {
          pecaMovida[posic].Pcasa = pecaMovida[posic].Pcasa->p2_casa;
        }
      }
      else
      {
        pecaMovida[posic].Pcasa = pecaMovida[posic].Pcasa->p_casa;
      }
    }
  }
  if(pecaMovida[posic].Pcasa->peca!=0){
    idrival=pecaMovida[posic].Pcasa->peca;
    if(idrival>0){
      while(idrival!=pecasP1[r].id) r++;
      pecasP1[r].Pcasa=NULL;
    }
    else{
      while(idrival!=pecasP2[r].id) r++;
      pecasP2[r].Pcasa=NULL;
    }

  }
  pecaMovida[posic].Pcasa->peca = pecaMovida[posic].id;
  desenhar_peca(pecaMovida[posic].id,pecaMovida[posic].Pcasa->cordenada_x,pecaMovida[posic].Pcasa->cordenada_y);
  if(pecaMovida[posic].Pcasa->rosa==1){
    draw();
    segundoDado=dados();
    if(!segundoDado)
      return 0;
    if(pecaMovida->id > 0)
    {
      printf("\nTurno de %s\n",jogador1);
      escolha=verificamov(segundoDado,pecaMovida, 1);
      if(escolha!=0)
      {
        atualiza(segundoDado, pecasP1, escolha);
      }
    }
    else
    {
      printf("\nTurno de %s\n",jogador2);
      escolha=verificamov(segundoDado,pecaMovida, 2);
      if(escolha!=0)
      {
        atualiza(segundoDado, pecasP2, escolha);
      }
    }

  }
  return 0;
}

int verificamov(int valorDado, peca* pecasJogador, int jogador)
{
  int pecasValidas[7]={1,1,1,1,1,1,1};
  int cont=0,k=0,escolha;
  int j = 0; //contador
  int pcganha;
  casa* auxCasa = NULL;
  for (int i = 0; i < 7; i++)
  {

    if(pecasJogador[i].pontuada == 1)
    {
      pecasValidas[i] = 0;
      continue;
    }

    if(pecasJogador[i].Pcasa == NULL)
    {
      if(jogador == 1)
      {
        auxCasa = inicialp1;
      }
      else
      {
        auxCasa = inicialp2;
      }
      goto jump;
    }

    if((pecasJogador[i].Pcasa->disAtePonto != 0) && (pecasJogador[i].Pcasa->disAtePonto != valorDado))
    {
      pecasValidas[i] = 0;
      continue;
    }
    if((pecasJogador[i].Pcasa->disAtePonto != 0) && (pecasJogador[i].Pcasa->disAtePonto == valorDado))
      pcganha=i;

    auxCasa = pecasJogador[i].Pcasa;
    jump:
    for (j = 0; j < valorDado; j++)
    {
      if (pecasJogador[i].Pcasa == NULL)
      {
        j++;
        goto jump2;
      }
      if(pecasJogador[i].Pcasa->cordenada_x == meio[7].cordenada_x && pecasJogador[i].Pcasa->cordenada_y == meio[7].cordenada_y)
      {
        if(jogador == 1)
        {
          auxCasa = auxCasa->p1_casa;
        }
        else
        {
          auxCasa = auxCasa->p2_casa;
        }
      }
      else
      {
        auxCasa = auxCasa->p_casa;
      }
    }
    jump2:
    if(jogador == 1)
    {
      if(auxCasa->peca > 0)
      {
        pecasValidas[i] = 0;
        continue;
      }
    }
    else
    {
      if(auxCasa->peca < 0)
      {
        pecasValidas[i] = 0;
        continue;
      }
    }
  }
  printf("\nMovimentos validos: ");
  while(k!=7){
    if(pecasValidas[k]!=0)
      cont++;
    k++;
  }
  if(cont==0){
    printf("\nNao existe movimentos validos");
    return 0;
  }
  else{
   k=0;
   while(k!=7){
     if(pecasValidas[k]!=0)
       printf("%d ", k + 1);
     k++;
   }
   while(1){
      k=0;

      printf("\nQual sera seu movimento? ");
      scanf("%d",&escolha);
      while(k!=7){
        if(pecasValidas[k] == 1 && escolha == k + 1)
        {
          return escolha-1;
        }
          k++;
        }


      }
      printf("Movimento invalido");
   }
  }

int instrucao()
{
  printf("Para jogar o Jogo Real de Ur são necessários 2 jogadores:\n\n");
  printf("Cada Jogador possui 7 peças que devem percorrer o caminho inteiro do tabuleiro ");
  printf("e quem o fizer primeiro ganha.\n\n");
  printf("Cada turno é composto de duas ações: \n\n");
  printf("1- O jogador rola 4 dados que possuim valor 1 e 0, a soma dos dados é o numero de movimentos que ele faz.\n");
  printf("2- O jogador escolhe mover uma peça que esta no tabuleiro ou coloca uma peça nova. ");
  printf("Essa peça então se movera o numero de espaços que foi tirado no dado\n\n");
  printf("Se a casa para a qual a peça se move esta ocupada por uma peça do adversário");
  printf(" o adversario retira sua peça do tabuleiro sem pontuar.\n");
  printf("Não é permitido mover uma peça sua para uma casa já ocupada por você.\n\n");
  printf("Se uma peça cai numa casa marcada por um X vermelho o jogador ganha outro movimento e essa peça fica imune ate sair da casa.\n\n");
  printf("Para pontuar é necessário movimentar uma peça exatamente uma casa a mais do que o fim do tabuleiro\n\n");
  printf("Pressione ENTER key para continuar\n");
  getchar();
  getchar();
  return 0;
}

int print_tit(){
printf("     %s_   _____   _____   _____        _____    _____       ___   _            _____   _____        _   _   _____  %s \n", MAG, RESET);
printf ("%s    | | /  _  \\ /  ___| /  _  \\      |  _  \\  | ____|     /   | | |          |  _  \\ | ____|      | | | | |  _  \\ %s \n", MAG, RESET);
printf ("%s    | | | | | | | |     | | | |      | |_| |  | |__      / /| | | |          | | | | | |__        | | | | | |_| |%s\n", MAG, RESET);
printf (" %s_  | | | | | | | |  _  | | | |      |  _  /  |  __|    / / | | | |          | | | | |  __|       | | | | |  _  /%s\n", MAG, RESET);
printf ("%s| |_| | | |_| | | |_| | | |_| |      | | \\ \\  | |___   / /  | | | |___       | |_| | | |___       | |_| | | | \\ \\%s\n", MAG, RESET);
printf ("%s\\_____/ \\_____/ \\_____/ \\_____/      |_|  \\_\\ |_____| /_/   |_| |_____|      |_____/ |_____|      \\_____/ |_|  \\_\\%s\n", MAG, RESET);
return 0;
}

/*
+----+----+----+----+         +----+----+
| \/ |    |    |    |         |    | \/ |
| /\ |    |    |    |  1P     |    | /\ |
+------------------------+--------------+
|    |    |    | \/ |    |    |    |    |atom://teletype/portal/5d0389b5-c486-490f-99e2-6a19e9a63735
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
