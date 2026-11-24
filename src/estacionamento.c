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


static int lerInteiro(const char *mensagem, int *valor)
{
    char buf[16];
    char *fim;
    long v;

    printf("%s", mensagem);
    if (lerLinha(buf, (int)sizeof(buf)) != 1) {
        return 0;
    }
    v = strtol(buf, &fim, 10);
    if (fim == buf || *fim != '\0') {
        return 0; 
    }
    if (v < -32768 || v > 32767) {
        return 0;
    }
    *valor = (int)v;
    return 1;
}


int cadastrarVeiculo(struct Colecao *c, int mapa[FILEIRAS][COLUNAS])
{
    struct Veiculo novo;
    char entrada[64];
    char descricao[62]; 
    int categoria, fileira, coluna;
    struct Veiculo *destino;

    if (c->quantidade >= TOTAL_VAGAS) {
        printf("Estacionamento lotado. Cadastro recusado.\n");
        return 0;
    }

    
    printf("Identificador (7 letras/numeros): ");
    if (lerLinha(entrada, (int)sizeof(entrada)) != 1 ||
        !validarIdentificador(entrada)) {
        printf("Identificador invalido. Cadastro cancelado.\n");
        return 0;
    }
    if (buscarVeiculo(c, entrada) != -1) {
        printf("Identificador ja cadastrado. Cadastro cancelado.\n");
        return 0;
    }
    strcpy(novo.id, entrada); 

    
    printf("Descricao (1 a 60 caracteres): ");
    if (lerLinha(descricao, (int)sizeof(descricao)) != 1 ||
        strlen(descricao) == 0) {
        printf("Descricao invalida (vazia ou maior que 60). Cadastro cancelado.\n");
        return 0;
    }
    strcpy(novo.descricao, descricao);

   
    if (!lerInteiro("Categoria (1 = carro, 2 = moto): ", &categoria) ||
        (categoria != 1 && categoria != 2)) {
        printf("Categoria invalida. Cadastro cancelado.\n");
        return 0;
    }
    novo.categoria = categoria;

    
    if (!lerInteiro("Fileira (1 a 4): ", &fileira) ||
        !lerInteiro("Coluna (1 a 5): ", &coluna) ||
        !posicaoValida(fileira, coluna)) {
        printf("Posicao invalida. Cadastro cancelado.\n");
        return 0;
    }
    if (!vagaLivre(mapa, fileira, coluna)) {
        printf("Vaga ocupada. Cadastro cancelado.\n");
        return 0;
    }
    novo.fileira = fileira;
    novo.coluna = coluna;

    
    if (c->quantidade == c->capacidade) {
        if (!expandirColecao(c)) {
            printf("Erro de memoria. Cadastro cancelado.\n");
            return 0;
        }
    }

    
    destino = &c->dados[c->quantidade];
    *destino = novo;
    c->quantidade++;
    ocuparVaga(mapa, fileira, coluna);

    printf("Veiculo %s cadastrado na vaga F%d/C%d.\n", novo.id, fileira, coluna);
    return 1;
}