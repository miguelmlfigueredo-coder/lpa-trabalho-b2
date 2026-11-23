#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "estacionamento.h"


int lerLinha(char *destino, int tamanho)
{
    size_t len;
    int c;

    if (fgets(destino, tamanho, stdin) == NULL) {
        return 0;
    }
    len = strlen(destino);
    if (len > 0 && destino[len - 1] == '\n') {
        destino[len - 1] = '\0';
        return 1;
    }
   
    while ((c = getchar()) != '\n' && c != EOF) {
    }
    return -1;
}


int criarColecao(struct Colecao *c)
{
    c->quantidade = 0;
    c->capacidade = 0;
    c->dados = malloc(CAPACIDADE_INICIAL * sizeof(struct Veiculo));
    if (c->dados == NULL) {
        return 0;
    }
    c->capacidade = CAPACIDADE_INICIAL;
    return 1;
}


void liberarColecao(struct Colecao *c)
{
    free(c->dados);
    c->dados = NULL;
    c->quantidade = 0;
    c->capacidade = 0;
}


int expandirColecao(struct Colecao *c)
{
    struct Veiculo *novo;

    novo = realloc(c->dados, (size_t)c->capacidade * 2 * sizeof(struct Veiculo));
    if (novo == NULL) {
        return 0; 
    }
    c->dados = novo;
    c->capacidade *= 2;
    return 1;
}


int validarIdentificador(char *id)
{
    size_t i;
    size_t n = strlen(id);

    if (n != 7) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        if (!isalnum((unsigned char)id[i])) {
            return 0;
        }
    }
    for (i = 0; i < n; i++) {
        id[i] = (char)toupper((unsigned char)id[i]);
    }
    return 1;
}


int buscarVeiculo(struct Colecao *c, const char *id)
{
    int i;

    for (i = 0; i < c->quantidade; i++) {
        if (strcmp(c->dados[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}