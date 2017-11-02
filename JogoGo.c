#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define DIM 11
int vez;
int menu(void);   //Abre o menu
void resetaTabuleiro(int tabuleiro[][DIM]);  //Zera todos os elementos da matriz.
void exibirTabuleiro(int tabuleiro[][DIM]);  //Monta o tabuleiro.
void jogar(int tabuleiro[][DIM]);
int checaLocal(int tabuleiro[][DIM], int linha, int coluna); //Confere se o local ja esta ocupado.
int checaVitoria(int tabuleiro[][DIM]); //Calcula quem ganhou.
int checaTermino(int tabuleiro[][DIM], int vez); //Quando nao tem mais casas vazias acaba o jogo.
void jogada(int tabuleiro[][DIM]); //Faz as jogadas(nessa função quando uma peça eh colocada no meio de outras 4 ela eh eliminada,
                                                    //mas quando as peças cercam outra ela nao eh eliminada.)

int main(void)
{
    int tabuleiro[DIM][DIM],
        continuar;
    //int pontuacao;

    do
    {
        vez=1;
        continuar = menu();
        if(continuar == 1)
            jogar(tabuleiro);
        //else if(continuar == 2)
          //  pontuacao;

    }while(continuar);

    return 0;
}

int menu(void)
{
    int opcao;
    printf("1. Jogar\n");
    printf("2. Pontuacao\n");
    printf("0. Sair\n");
    printf("Escolha sua opcao: ");
    do{
    printf("Digite sua opcao: ");
    scanf("%d", &opcao);
    } while(opcao < 0 || opcao > 2);
    return opcao;
}

void resetaTabuleiro(int tabuleiro[][DIM])
{
    int linha, coluna;
    for(linha = 0 ; linha < DIM ; linha++)
        for(coluna = 0 ; coluna < DIM ; coluna++)
            tabuleiro[linha][coluna] = 0;
}


void exibirTabuleiro(int tabuleiro[][DIM])
{
    int linha, coluna;
    printf("\n");

    for(linha = 0 ; linha < DIM ; linha++)
    {
        for(coluna = 0 ; coluna < DIM ; coluna++)
        {
            if(tabuleiro[linha][coluna] == 0)
                printf("|   ");
            else if(tabuleiro[linha][coluna] == 1)
                printf("| X ");
            else if(tabuleiro[linha][coluna] == 2)
                printf("| O ");
        }
        printf("|");
        printf("\n");
    }
    printf("\n");
}

void jogar(int tabuleiro[][DIM])
{
    resetaTabuleiro(tabuleiro);

    do
    {
        system("cls");
        exibirTabuleiro(tabuleiro);
        jogada(tabuleiro);

    }while(checaTermino(tabuleiro, vez) != 1);
}

int checaPosicao(int tabuleiro[][DIM], int linha, int coluna)
{
    if(linha < 0 || linha > (DIM-1) || coluna < 0 || coluna > (DIM-1) || tabuleiro[linha][coluna] != 0)
        return 0;
    else
        return 1;
}

int posicaoValida(int linha, int coluna)
{
    if(linha < 0 || linha > (DIM-1) || coluna < 0 || coluna > (DIM-1))
        return 0;
    else
        return 1;
}

int posicaoCercada(int tabuleiro[][DIM], int linha, int coluna, int ameaca)
{
    if (posicaoValida(linha, coluna) == 0)
        return 0;
    else if ((posicaoValida(linha-1, coluna) == 1) && (tabuleiro[linha-1][coluna] == ameaca)
        && (posicaoValida(linha+1, coluna) == 1) && (tabuleiro[linha+1][coluna] == ameaca)
        && (posicaoValida(linha, coluna-1) == 1) && (tabuleiro[linha][coluna-1] == ameaca)
        && (posicaoValida(linha, coluna+1) == 1) && (tabuleiro[linha][coluna+1] == ameaca))
        return 1;
    else
        return 0;
}

int somaMatriz(int tabuleiro[][DIM])
{
    int i, j,
    soma = 0;
    for(i = 0; i < DIM; i++)
        for(j = 0; j < DIM; j++)
         soma = soma + tabuleiro[i][j];
    return 1;
}

int checaVitoria(int tabuleiro[][DIM])
{
    int linha, coluna;
    int pecasJogador[] = { 0, 0 };
    for(linha = 0 ; linha < DIM ; linha++)
    {
        for(coluna = 0; coluna < DIM; coluna++)
        {
            if(tabuleiro[linha][coluna] == 0)
                return 0;
            pecasJogador[tabuleiro[linha][coluna]]++;
        }
    }

    if (pecasJogador[0] > pecasJogador[1])
    {
        exibirTabuleiro(tabuleiro);
        printf("Jogador 1 venceu!\n\n");
    }
    else if (pecasJogador[0] < pecasJogador[1])
    {
        exibirTabuleiro(tabuleiro);
        printf("Jogador 2 venceu!\n\n");
    }
    else
    {
        exibirTabuleiro(tabuleiro);
        printf("Houve EMPATE!\n\n");
    }

    return 1;
}

int checaTermino(int tabuleiro[][DIM], int vez)
{
    if(checaVitoria(tabuleiro))
    {
        exibirTabuleiro(tabuleiro);
        return 1;
    }
    return 0;
}

void jogada(int tabuleiro[][DIM])
{
    int linha, coluna, jogador, adversario;
    vez++;
    jogador = (vez % 2) + 1;
    adversario = (jogador%2) + 1;
    printf("\n--> Jogador %d \n", jogador) ;

    do
    {
        printf("Linha(11 linhas): ");
        scanf("%d", &linha);
        linha--;

        printf("Coluna(11 colunas): ");
        scanf("%d", &coluna);
        coluna--;

        if(checaPosicao(tabuleiro, linha, coluna) == 0)
            printf("Posicao ocupada ou inexistente, escolha outra.\n");

    } while (checaPosicao(tabuleiro, linha, coluna) == 0);

    tabuleiro[linha][coluna] = jogador;

    // Testa se o jogador jogou uma peça numa célula já cercada

    if (posicaoCercada(tabuleiro, linha, coluna, adversario) == 1)
        tabuleiro[linha][coluna] = adversario;

    // Testa se o jogador terminou de cercar alguma célula que estava com o adversário

    if ((tabuleiro[linha-1][coluna] == adversario) && (posicaoCercada(tabuleiro, linha-1, coluna, jogador) == 1))
        tabuleiro[linha-1][coluna] = jogador;

    if ((tabuleiro[linha+1][coluna] == adversario) && (posicaoCercada(tabuleiro, linha+1, coluna, jogador) == 1))
        tabuleiro[linha+1][coluna] = jogador;

    if ((tabuleiro[linha][coluna-1] == adversario) && (posicaoCercada(tabuleiro, linha, coluna-1, jogador) == 1))
        tabuleiro[linha][coluna-1] = jogador;

    if ((tabuleiro[linha][coluna+1] == adversario) && (posicaoCercada(tabuleiro, linha, coluna+1, jogador) == 1))
        tabuleiro[linha][coluna+1] = jogador;

}
