#ifndef ESTACIONAMENTO_H
#define ESTACIONAMENTO_H

#define FILEIRAS 4
#define COLUNAS 5
#define TOTAL_VAGAS 20
#define CAPACIDADE_INICIAL 2

struct Veiculo {
    char id[8];          
    char descricao[61];  
    int categoria;       
    int fileira;         
    int coluna;          
};

struct Colecao {
    struct Veiculo *dados;
    int quantidade;
    int capacidade;
};

// Miguel: registros e memoria 
int lerLinha(char *destino, int tamanho);
int criarColecao(struct Colecao *c);
void liberarColecao(struct Colecao *c);
int expandirColecao(struct Colecao *c);
int validarIdentificador(char *id);
int buscarVeiculo(struct Colecao *c, const char *id);
int cadastrarVeiculo(struct Colecao *c, int mapa[FILEIRAS][COLUNAS]);
void consultarVeiculo(struct Colecao *c);
int atualizarVeiculo(struct Colecao *c);
int removerVeiculo(struct Colecao *c, int mapa[FILEIRAS][COLUNAS]);

// Willian: matriz e posicoes 
void inicializarMapa(int mapa[FILEIRAS][COLUNAS]);
int posicaoValida(int fileira, int coluna);
int vagaLivre(int mapa[FILEIRAS][COLUNAS], int fileira, int coluna);
void ocuparVaga(int mapa[FILEIRAS][COLUNAS], int fileira, int coluna);
void liberarVaga(int mapa[FILEIRAS][COLUNAS], int fileira, int coluna);
void exibirMapa(int mapa[FILEIRAS][COLUNAS]);
int moverVeiculo(struct Colecao *c, int mapa[FILEIRAS][COLUNAS]);
void listarVeiculos(struct Colecao *c);
void gerarRelatorio(struct Colecao *c, int mapa[FILEIRAS][COLUNAS]);

#endif