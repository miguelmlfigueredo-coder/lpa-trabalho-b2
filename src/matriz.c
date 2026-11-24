#include "estacionamento.h"

int posicaoValida(int fileira, int coluna) {
    if (fileira >= 0 && fileira < FILEIRAS &&
        coluna >= 0 && coluna < COLUNAS) {
        return 1;
    }

    return 0;
}

void inicializarMapa(int mapa[FILEIRAS][COLUNAS]) {
    int i, j;

    for (i = 0; i < FILEIRAS; i++) {
        for (j = 0; j < COLUNAS; j++) {
            mapa[i][j] = 0;
        }
    }
}

int vagaLivre(int mapa[FILEIRAS][COLUNAS], int fileira, int coluna) {
    if (!posicaoValida(fileira, coluna)) {
        return 0;
    }

    if (mapa[fileira][coluna] == 0) {
        return 1;
    }

    return 0;
}

void ocuparVaga(int mapa[FILEIRAS][COLUNAS], int fileira, int coluna) {
    if (posicaoValida(fileira, coluna) && vagaLivre(mapa, fileira, coluna)) {
        mapa[fileira][coluna] = 1;
    }
}


void liberarVaga(int mapa[FILEIRAS][COLUNAS], int fileira, int coluna) {
    if (posicaoValida(fileira, coluna)) {
        mapa[fileira][coluna] = 0;
    }
} 
void exibirMapa(int mapa[FILEIRAS][COLUNAS]) {
    int i, j;

    printf("\n===== MAPA DO ESTACIONAMENTO =====\n\n");

    for (i = 0; i < FILEIRAS; i++) {
        printf("Fileira %d: ", i + 1);

        for (j = 0; j < COLUNAS; j++) {
            if (mapa[i][j] == 0) {
                printf("[L] ");
            } else {
                printf("[O] ");
            }
        }

        printf("\n");
    }

    printf("\n[L] = Livre | [O] = Ocupada\n");
}