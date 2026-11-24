#include <stdio.h>
#include <stdlib.h>
#include "estacionamento.h"

static void exibirMenu(void)
{
    printf("\n========== ESTACIONAMENTO ==========\n");
    printf("1 - Cadastrar veiculo\n");
    printf("2 - Consultar veiculo por identificador\n");
    printf("3 - Atualizar descricao ou categoria\n");
    printf("4 - Mover veiculo para outra vaga\n");
    printf("5 - Remover veiculo\n");
    printf("6 - Listar veiculos cadastrados\n");
    printf("7 - Exibir mapa de vagas\n");
    printf("8 - Exibir relatorio da ocupacao\n");
    printf("0 - Encerrar\n");
    printf("===================================\n");
    printf("Opcao: ");
}

int main(void)
{
    int mapa[FILEIRAS][COLUNAS];
    struct Colecao colecao;
    char entrada[16];
    int opcao = -1;
    int status;

    inicializarMapa(mapa);

    if (!criarColecao(&colecao)) {
        printf("Erro: nao foi possivel alocar memoria.\n");
        return 1;
    }

    do {
        exibirMenu();
        status = lerLinha(entrada, (int)sizeof(entrada));
        if (status == 0) {
            break; 
        }
        if (status == -1 || sscanf(entrada, "%d", &opcao) != 1) {
            opcao = -1;
        }

        switch (opcao) {
        case 1: cadastrarVeiculo(&colecao, mapa); break;
        case 2: consultarVeiculo(&colecao); break;
        case 3: atualizarVeiculo(&colecao); break;
        case 4: moverVeiculo(&colecao, mapa); break;
        case 5: removerVeiculo(&colecao, mapa); break;
        case 6: listarVeiculos(&colecao); break;
        case 7: exibirMapa(mapa); break;
        case 8: gerarRelatorio(&colecao, mapa); break;
        case 0: printf("Encerrando...\n"); break;
        default: printf("Opcao invalida. Tente novamente.\n"); break;
        }
    } while (opcao != 0);

    liberarColecao(&colecao);
    return 0;
}