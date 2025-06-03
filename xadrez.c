#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM 8

char tabuleiro[TAM][TAM];

void inicializarTabuleiro() {
    char linha1[] = {'r','n','b','q','k','b','n','r'};
    char linha2[] = {'p','p','p','p','p','p','p','p'};
    char linha7[] = {'P','P','P','P','P','P','P','P'};
    char linha8[] = {'R','N','B','Q','K','B','N','R'};

    for (int i = 0; i < TAM; i++) {
        tabuleiro[0][i] = linha1[i];   // jogador B
        tabuleiro[1][i] = linha2[i];   // jogador B
        tabuleiro[6][i] = linha7[i];   // jogador A
        tabuleiro[7][i] = linha8[i];   // jogador A
        for (int j = 2; j < 6; j++) {
            tabuleiro[j][i] = ' ';
        }
    }
}

void imprimirTabuleiro() {
    printf("\n  a b c d e f g h\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", 8 - i);
        for (int j = 0; j < TAM; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("%d\n", 8 - i);
    }
    printf("  a b c d e f g h\n");
}

int posicaoValida(int x, int y) {
    return x >= 0 && x < TAM && y >= 0 && y < TAM;
}

int moverPeca(char* origem, char* destino, int turnoA) {
    int o_col = origem[0] - 'a';
    int o_lin = 8 - (origem[1] - '0');
    int d_col = destino[0] - 'a';
    int d_lin = 8 - (destino[1] - '0');

    if (!posicaoValida(o_lin, o_col) || !posicaoValida(d_lin, d_col)) {
        printf("Posição inválida.\n");
        return 0;
    }

    char peca = tabuleiro[o_lin][o_col];

    if (peca == ' ') {
        printf("Nenhuma peça na origem.\n");
        return 0;
    }

    if ((turnoA && islower(peca)) || (!turnoA && isupper(peca))) {
        printf("Não é sua peça.\n");
        return 0;
    }

    tabuleiro[d_lin][d_col] = peca;
    tabuleiro[o_lin][o_col] = ' ';
    return 1;
}

int main() {
    char origem[3], destino[3];
    int turno = 1;

    inicializarTabuleiro();

    while (1) {
        imprimirTabuleiro();
        printf("Jogador %c, digite o movimento (ex: e2 e4): ", turno ? 'A' : 'B');
        scanf("%s %s", origem, destino);

        if (strlen(origem) != 2 || strlen(destino) != 2) {
            printf("Entrada inválida.\n");
            continue;
        }

        if (moverPeca(origem, destino, turno)) {
            turno = !turno;
        }
    }

    return 0;
}
