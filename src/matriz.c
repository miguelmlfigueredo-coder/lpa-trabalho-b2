#include <stdio.h>
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
void listarVeiculos(struct Colecao *c) {
    int i;

    if (c == NULL || c->quantidade == 0) {
        printf("\nNenhum veiculo cadastrado.\n");
        return;
    }

    printf("\n===== VEICULOS CADASTRADOS =====\n");

    for (i = 0; i < c->quantidade; i++) {
        printf("\nVeiculo %d\n", i + 1);
        printf("Identificador: %s\n", c->dados[i].id);
        printf("Descricao: %s\n", c->dados[i].descricao);
        printf("Categoria: %d\n", c->dados[i].categoria);
        printf("Fileira: %d\n", c->dados[i].fileira + 1);
        printf("Coluna: %d\n", c->dados[i].coluna + 1);
    }
}