#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* cores para uso no terminal*/
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

int print_tit(){
printf(GRN "     _   _____   _____   _____        _____    _____       ___   _            _____   _____        _   _   _____   \n" RESET);
printf(GRN "    | | /  _  \\ /  ___| /  _  \\      |  _  \\  | ____|     /   | | |          |  _  \\ | ____|      | | | | |  _  \\  \n" RESET);
printf(GRN "    | | | | | | | |     | | | |      | |_| |  | |__      / /| | | |          | | | | | |__        | | | | | |_| |\n" RESET);
printf(GRN " _  | | | | | | | |  _  | | | |      |  _  /  |  __|    / / | | | |          | | | | |  __|       | | | | |  _  /\n" RESET);
printf(GRN "| |_| | | |_| | | |_| | | |_| |      | | \\ \\  | |___   / /  | | | |___       | |_| | | |___       | |_| | | | \\ \\\n" RESET);
printf(GRN "\\_____/ \\_____/ \\_____/ \\_____/      |_|  \\_\\ |_____| /_/   |_| |_____|      |_____/ |_____|      \\_____/ |_|  \\_\\\n" RESET);
return 0;
}

int instrucao()
{
  printf("Para jogar o Jogo Real de Ur são necessários 2 jogadores:\n\n");
  printf("Cada Jogador possui 7 peças que devem percorrer o caminho inteiro do tabuleiro ");
  printf("e quem o fizer primeiro ganha.\n\n");
  printf("Cada turno é composto de duas ações: \n\n");
  printf("1- O jogador rola 4 dados que possuim valor 1 e 0, a soma dos dados é o numero de movimentos que ele faz.\n\n");
  printf("2- O jogador escolhe mover uma peça que esta no tabuleiro ou coloca uma peça nova.\n ");
  printf("  Essa peça então se movera o numero de espaços que foi tirado no dado\n\n");
  printf("Se a casa para a qual a peça se move esta ocupada por uma peça do adversário");
  printf(" o adversario retira sua peça do tabuleiro sem pontuar.\n");
  printf("Não é permitido mover uma peça sua para uma casa já ocupada por você.\n\n");
  printf("Se uma peça cai numa casa marcada por um X vermelho o jogador ganha outro movimento e essa peça fica imune ate sair da casa.\n\n");
  printf("Para pontuar é necessário movimentar uma peça exatamente uma casa a mais do que o fim do tabuleiro\n\n");
  printf("Pressione ENTER para continuar\n");
  getchar();
  getchar();
  return 0;
}

void historia()
{
  system("clear");
  printf("\nThe Royal Game of Ur ou O Jogo Real de Ur, foi popular em todo o Oriente Médio no terceiro milênio A.C\n");
  printf("tabuleiros foram encontrados no Irã, Síria, Egito, Líbano, Sri Lanka, Chipre e Creta.\n\nO Jogo de Ur eventualmente adquiriu significado\n");
  printf("supersticioso fornecendo previsões vagas para o futuro dos jogadores que pousarem em certas casas do tabuleiro,");
  printf("\ncomo você encontrará um amigo ou você se tornará poderoso como um leão.\n\nO jogo possui esse nome devido ao seu redescobrimento");
  printf("em uma das escavações do arqueologo Sir Leonard Woolley no cemiterio real de ur. \n\nEntretanto mais tarde arqueologos descobririam copias do jogo em varias localidade do Oriente Medio.\n\n");
  printf("As regras só foram redescobertas em 1980, pelo historiador Irving Finkel através de placas de barro cuneiforme escritas por um escriba babiloniano.\n");
  printf("\nPressione ENTER para continuar\n");
  getchar();
  getchar();
}

void creditos()
{
  system("clear");
  print_tit();
  printf("\n\n\nCriadores:\n\n");
  printf("Raphael Novello: https://github.com/RaphaelAN\n\n");
  printf("Sidney Outeiro:  https://github.com/sidneyouteiro");
  printf("\n\nPressione ENTER para continuar\n");
  getchar();
  getchar();
}
