#include <stdio.h>
#include <stdlib.h>
#include "estacionamento.h"
int posicaoValida(int fileira, int coluna) {
    if (fileira >= 1 && fileira <= FILEIRAS &&
        coluna >= 1 && coluna <= COLUNAS) {
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

    if (mapa[fileira - 1][coluna - 1] == 0) {
        return 1;
    }

    return 0;
}

void ocuparVaga(int mapa[FILEIRAS][COLUNAS], int fileira, int coluna) {
    if (posicaoValida(fileira, coluna) && vagaLivre(mapa, fileira, coluna)) {
        mapa[fileira - 1][coluna - 1] = 1;
    }
}

void liberarVaga(int mapa[FILEIRAS][COLUNAS], int fileira, int coluna) {
    if (posicaoValida(fileira, coluna)) {
        mapa[fileira - 1][coluna - 1] = 0;
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
        printf("Fileira: %d\n", c->dados[i].fileira);
        printf("Coluna: %d\n", c->dados[i].coluna);
    }
}
static int lerInteiroMatriz(const char *mensagem, int *valor, int maximo) {
    char entrada[16];
    char *fim;
    long numero;

    printf("%s", mensagem);

    if (lerLinha(entrada, sizeof(entrada)) != 1) {
        return 0;
    }

    numero = strtol(entrada, &fim, 10);

    if (fim == entrada || *fim != '\0' ||
        numero < 1 || numero > maximo) {
        return 0;
    }

    *valor = (int)numero;
    return 1;
}
int moverVeiculo(struct Colecao *c, int mapa[FILEIRAS][COLUNAS]) {
    char id[64];
    int indice;
    int novaFileira;
    int novaColuna;
    struct Veiculo *v;

    if (c == NULL || c->dados == NULL || c->quantidade == 0) {
        printf("\nNenhum veiculo cadastrado.\n");
        return 0;
    }

    printf("\nIdentificador do veiculo: ");

    if (lerLinha(id, sizeof(id)) != 1 ||
        !validarIdentificador(id)) {
        printf("Identificador invalido.\n");
        return 0;
    }

    indice = buscarVeiculo(c, id);

    if (indice == -1) {
        printf("Veiculo nao encontrado.\n");
        return 0;
    }

    v = &c->dados[indice];

    printf("\nVaga atual: Fileira %d, Coluna %d\n",
           v->fileira, v->coluna);

    if (!lerInteiroMatriz("Nova fileira (1 a 4): ",
                          &novaFileira, FILEIRAS)) {
        printf("Fileira invalida.\n");
        return 0;
    }

    if (!lerInteiroMatriz("Nova coluna (1 a 5): ",
                          &novaColuna, COLUNAS)) {
        printf("Coluna invalida.\n");
        return 0;
    }

    if (v->fileira == novaFileira &&
        v->coluna == novaColuna) {
        printf("O veiculo ja esta nessa vaga.\n");
        return 0;
    }

    if (!vagaLivre(mapa, novaFileira, novaColuna)) {
        printf("A vaga escolhida esta ocupada.\n");
        return 0;
    }

    liberarVaga(mapa, v->fileira, v->coluna);
    ocuparVaga(mapa, novaFileira, novaColuna);

    v->fileira = novaFileira;
    v->coluna = novaColuna;

    printf("\nVeiculo movido com sucesso!\n");
    printf("Nova vaga: Fileira %d, Coluna %d\n",
           v->fileira, v->coluna);

    return 1;
}