# lpa-trabalho-b2

Sistema de Gestão de Estacionamento
1. Identificação
Disciplina: Lógica de Programação e Algoritmos
Semestre: 2026/2
Trabalho: 2º Bimestre - Sistema de Gestão de Estacionamento
Integrantes:
Miguel Medeiros Lima Figueredo(Integrante 1) - GitHub: miguelmlfigueredo-coder
Willian Ferreira da Silva Nunes (Integrante 2)GitHub:
WillianFerreiradaSilvaNunes 
Repositório: https://github.com/miguelmlfigueredo-coder/lpa-trabalho-b2


2. Descrição do sistema
Programa em linguagem C, executado no terminal, que simula o gerenciamento de um estacionamento fictício com 4 fileiras e 5 colunas (20 vagas). O programa começa sem veículos, recebe operações por um menu e mantém os dados apenas enquanto está aberto (não há gravação em arquivos).

O ponto central do sistema é manter sincronizados o mapa de vagas (matriz) e os registros dos veículos (vetor dinâmico), de modo que, a qualquer momento:

veículos ativos = células com valor 1 na matriz = vagas ocupadas no relatório

Todos os identificadores e descrições usados nos testes são fictícios.
3. Funcionalidades
Menu disponível:

========== ESTACIONAMENTO ==========
1 - Cadastrar veiculo
2 - Consultar veiculo por identificador
3 - Atualizar descricao ou categoria
4 - Mover veiculo para outra vaga
5 - Remover veiculo
6 - Listar veiculos cadastrados
7 - Exibir mapa de vagas
8 - Exibir relatorio da ocupacao
0 - Encerrar
===================================

Opção
Funcionalidade
1
Cadastra veículo (identificador, descrição, categoria, fileira e coluna) com todas as validações
2
Consulta os dados completos de um veículo pelo identificador
3
Altera descrição e/ou categoria, preservando identificador e vaga
4
Move o veículo para outra vaga livre, atualizando mapa e registro
5
Remove o veículo, libera a vaga e reorganiza o vetor sem lacunas
6
Lista todos os veículos ativos (mensagem específica se estiver vazio)
7
Exibe o mapa de vagas com legenda
8
Exibe total de vagas, ocupadas, livres, percentual (2 casas decimais), carros e motos
0
Encerra o programa liberando a memória dinâmica


Regras de validação implementadas:

Identificador com exatamente 7 caracteres (A-Z e 0-9), sem espaços ou símbolos; minúsculas são convertidas para maiúsculas e a duplicidade é verificada sem distinção de caixa.
Descrição não vazia, com no máximo 60 caracteres, sem truncar.
Categoria 1 (carro) ou 2 (moto).
Fileira de 1 a 4 e coluna de 1 a 5, validadas antes de acessar a matriz.
Vaga ocupada recusa cadastro e movimentação.
Cadastro recusado com 20 veículos (lotação).
Falha no realloc cancela o cadastro sem perder dados.
Leitura com fgets (nunca gets), descartando o excedente do buffer.
4. Estruturas utilizadas
Matriz de vagas (4 x 5)
int mapa[FILEIRAS][COLUNAS];

0 = vaga livre e 1 = vaga ocupada. Todas as posições começam em 0. O usuário informa fileira e coluna a partir de 1; a conversão para índice (menos 1) é feita dentro das funções de posição (posicaoValida, vagaLivre, ocuparVaga, liberarVaga). O percorrimento da matriz usa laços aninhados.
Struct do veículo
struct Veiculo {
    char id[8];
    char descricao[61];
    int categoria;
    int fileira;
    int coluna;
};

O registro guarda fileira e coluna na mesma numeração que o usuário digita (1 a 4 e 1 a 5).
Coleção dinâmica
struct Colecao {
    struct Veiculo *dados;
    int quantidade;
    int capacidade;
};

quantidade: veículos efetivamente cadastrados.
capacidade: registros que o vetor comporta sem ampliar.
Alocação inicial com malloc (capacidade 2).
Quando quantidade == capacidade, a capacidade é duplicada com realloc, usando ponteiro temporário para não perder a referência original em caso de falha (sequência de capacidades: 2, 4, 8, 16, 32).
O limite de 20 veículos é verificado separadamente da capacidade de memória.
A remoção desloca os registros seguintes e não reduz a capacidade.
free é chamado uma única vez no encerramento.
mapa e colecao são declarados na main e passados por parâmetro (sem variáveis globais de estado).
5. Modularização
Arquivo
Conteúdo
src/estacionamento.h
Constantes, structs e declarações das funções
src/estacionamento.c
Registros e memória: lerLinha, criarColecao, liberarColecao, expandirColecao, validarIdentificador, buscarVeiculo, cadastrarVeiculo, consultarVeiculo, atualizarVeiculo, removerVeiculo
src/matriz.c
Matriz e posições: inicializarMapa, posicaoValida, vagaLivre, ocuparVaga, liberarVaga, exibirMapa, moverVeiculo, listarVeiculos, gerarRelatorio
src/main.c
Menu principal, laço de repetição e encerramento

6. Compilação e execução
Compilação (C11):

gcc -std=c11 -Wall -Wextra -pedantic src/main.c src/estacionamento.c src/matriz.c -o estacionamento

Execução:

./estacionamento

No Windows (PowerShell): .\estacionamento.exe
7. Testes realizados


Teste
Entrada / operação
Resultado esperado
Resultado observado
Situação
T01
Abrir o programa e usar as opções 7, 6 e 8
Mapa todo livre, listagem vazia com mensagem específica, 20 vagas livres e 0,00%
O mapa é inicializado com todas as 20 posições livres. A listagem apresenta a mensagem "Nenhum veiculo cadastrado." e o relatório informa 20 vagas livres, nenhuma ocupada e 0,00% de ocupação.
EXECUTADO
T02
Cadastrar ABC1D23, "Carro azul", categoria 1, F1/C1
Veículo cadastrado, aparece na consulta/listagem, F1/C1 ocupada
O cadastro de ABC1D23 é aceito. O sistema apresenta "Veiculo ABC1D23 cadastrado na vaga F1/C1.". O veículo pode ser consultado e aparece na listagem, com a vaga F1/C1 ocupada.
EXECUTADO
T03
Cadastrar abc1d23 depois de ABC1D23
Cadastro recusado por duplicidade, nada alterado
O identificador digitado em letras minúsculas é convertido para maiúsculas. O sistema reconhece a duplicidade e apresenta "Identificador ja cadastrado. Cadastro cancelado.". Nenhum novo registro é criado.
EXECUTADO
T04
Cadastrar em vaga ocupada e com fileira 5
Ambos recusados sem alteração do mapa nem dos registros
O cadastro em vaga ocupada apresenta "Vaga ocupada. Cadastro cancelado.". A tentativa com fileira 5 apresenta "Posicao invalida. Cadastro cancelado.". Nenhuma das operações altera os registros ou o mapa.
EXECUTADO
T05
Cadastrar o 3º veículo
Capacidade da coleção passa de 2 para 4, registros preservados
Ao cadastrar o terceiro veículo, a capacidade da coleção dinâmica é ampliada de 2 para 4 registros por meio de realloc. Os dois registros anteriores são preservados e o terceiro é armazenado corretamente.
EXECUTADO
T06
Atualizar descrição e categoria de ABC1D23
Dados alterados, sem duplicar registro, vaga mantida
A descrição de ABC1D23 é atualizada para "Carro azul atualizado". O sistema apresenta "Veiculo ABC1D23 atualizado.". O identificador, a categoria e a localização permanecem preservados.
EXECUTADO
T07
Mover ABC1D23 de F1/C1 para F2/C3 (livre)
F1/C1 livre, F2/C3 ocupada, registro atualizado
A tentativa de movimentação para F1/C2 é recusada com a mensagem "A vaga escolhida esta ocupada.". A movimentação para F2/C3 é realizada com sucesso. A vaga F1/C1 é liberada e F2/C3 passa a ficar ocupada.
EXECUTADO
T08
Remover XYZ9K87
Registro removido sem lacuna, vaga liberada
O veículo XYZ9K87 é removido. O sistema apresenta "Veiculo XYZ9K87 removido. Vaga F1/C2 liberada.". O registro é retirado da coleção, os registros seguintes são reorganizados e a vaga é liberada.
EXECUTADO
T09
Cadastrar 20 veículos e tentar o 21º
21º cadastro recusado por lotação
Após o cadastro de 20 veículos, a tentativa de cadastrar o 21º é recusada com "Estacionamento lotado. Cadastro recusado.". A quantidade de veículos permanece em 20.
EXECUTADO
T10
Escolher a opção 0
Programa encerra liberando a memória da coleção
o selecionar a opção 0, o programa apresenta "Encerrando..." e executa a função liberarColecao, que utiliza free para liberar a memória dinâmica.
EXECUTADO


Cenário completo do roteiro (após T01 a T08):
Resultado observado:
Após a execução das operações de cadastro, atualização, movimentação e remoção, permanecem 2 veículos cadastrados no estacionamento:
ABC1D23 — Carro azul atualizado, categoria carro, localizado na F2/C3.
LPA2026 — Carro branco, categoria carro, localizado na F4/C5.
O relatório apresenta os seguintes valores:
Total de vagas: 20.
Vagas ocupadas: 2.
Vagas livres: 18.
Percentual de ocupação: 10,00%.
Quantidade de carros: 2.
Quantidade de motos: 0.
.

8. Divisão de responsabilidades
Miguel (Integrante 1): struct e coleção dinâmica, malloc/realloc/free, leitura segura, validação e busca por identificador, cadastro, consulta, atualização, remoção e menu principal (main.c). Branch: integrante1-registros.

Willian (Integrante 2): matriz 4 x 5, validação de posições, exibição do mapa, movimentação, listagem e relatório de ocupação. Branch: integrante2-matriz.

Em conjunto: definição da struct e das assinaturas das funções (estacionamento.h), integração das branches, testes e README.
9. Integração das branches
A integração do projeto foi realizada utilizando a branch principal main.
Inicialmente, a branch main foi atualizada com as alterações disponíveis no repositório remoto por meio de uma atualização do tipo Fast-forward.
Em seguida, foi realizada a integração da branch integrante2-matriz, utilizando o comando:
git merge origin/integrante2-matriz
O Git realizou a integração automaticamente utilizando a estratégia ort, sem apresentar conflitos de merge.
Durante essa integração, o arquivo src/matriz.c foi adicionado à branch principal, contendo a implementação da funcionalidade de matriz.
Não foi necessária resolução manual de conflitos no arquivo src/estacionamento.h ou nos demais arquivos durante esse merge.
Após a integração, o projeto foi compilado para verificar possíveis erros. Como a compilação não apresentou mensagens de erro, as alterações foram enviadas ao GitHub utilizando:
git push
A integração foi concluída com sucesso e as alterações passaram a fazer parte da branch main.

10. Declaração individual de autoria e uso de IA
Miguel
Miguel (Miguel de Medeiros Lima Figueredo)

Funcionalidades em que atuei: struct Veiculo e struct Colecao, coleção dinâmica (malloc, realloc, free), leitura segura de strings, validação e busca por identificador, cadastro, consulta, atualização, remoção e menu principal (main.c). Também criei o repositório, a branch integrante1-registros e fiz os commits e pushes da minha parte.

Usei IA generativa? Sim.

Ferramenta: Claude (Anthropic).

Para que usei:
- Ler o roteiro, resumir as exigências e propor a divisão de tarefas entre mim e o Willian.
- Aprender a usar Git e GitHub (criar repositório, clonar, criar branch, commit, push).
-Para ajudar a tirar duvidas, me ajudar a relembrar e explicar sobre realloc e malloc e me     ensinar a corrigir as partes do código em que eu não estava conseguindo resolver. 
- Entender malloc, realloc e free, e o cuidado de usar um ponteiro temporário no realloc.
- Entender erros de compilação e de comandos (por exemplo, undefined reference).
- Montar uma sequência de testes e o modelo deste README.

Exemplos de solicitações:
- "Resuma o roteiro e diga o que eu e minha dupla devemos fazer desde o início."
- "Sugira uma divisão de tarefas entre o Integrante 1 e o Integrante 2."
- "Me explique passo a passo como criar o repositório, a branch e fazer commit e push."
- "Por que apareceu o erro undefined reference ao compilar?"
- "Me passe uma sequência de testes para conferir o programa."

Sugestões incorporadas: ponteiro temporário no realloc; convenção de fileira e coluna de 1 a 4 e 1 a 5 combinada com o Willian. Decidi tratar entradas inválidas cancelando a operação e voltando ao menu. 

Código externo: não adaptei código de outras fontes (livros, sites ou repositórios), além do código gerado pela IA declarado acima.

Willian
(Willian):

Usei IA generativa? Sim.

Ferramenta: Chat GPT

 Ler o roteiro, resumir as exigências e propor a divisão de tarefas entre mim e o Miguel
Aprender a usar Git e GitHub (criar repositório, clonar, criar branch, commit, push).
Para ajudar a tirar duvidas, me ajudar a relembrar e explicar o conteudo
Entender erros de compilação e de comandos

11. Limitações conhecidas

O sistema apresenta as seguintes limitações:
- Os dados dos veículos são armazenados apenas durante a execução do programa, não sendo salvos em arquivos ou banco de dados.
- O programa funciona exclusivamente pelo terminal, sem interface gráfica.
- A capacidade máxima é de 20 veículos, devido à quantidade de vagas disponíveis no estacionamento.

12. Referências externas
não foram utilizadas referências externas.
