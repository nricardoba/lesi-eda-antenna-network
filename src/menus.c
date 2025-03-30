/**
 * @file menus.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Ficheiro que gere as funções sobre os menus do projeto.
 * @version 0.1
 * @date 30-03-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

/**
 * @brief Cria uma matriz sem antenas.
 * 
 * @param m Apontador para a variavel com as dimensões da matriz.
 * @return true Conseguiu criar a matriz.
 * @return false Não conseguiu criar a matriz.
 */
bool CriaMatriz(Matriz* m) {
    // variavel auxiliar
    int aux;

    // pergunta ao utilizador o numero de linhas
    printf("numero de linhas: ");
    // le o numero de linhas
    scanf("%d", &aux);

    // se o numero de linhas for invalido, não é possivel criar matriz
    if (aux <= 0) return false;
    // caso seja valido guarda o numero de linhas
    m->linhas = aux;

    // pergunta ao utilizador o numero de colunas
    printf("numero de colunas: ");
    // le o numero de colunas
    scanf("%d", &aux);

    // se o numero de colunas for invalido, não é possivel criar matriz
    if (aux <= 0) return false;
    // caso seja valido guarda o numero de colunas
    m->colunas = aux;

    // a matriz foi criada
    return true;
}

/**
 * @brief Verifica se as dimensões da matriz passadas por parâmetros são válidas.
 * 
 * @param x Numero de linhas da matriz.
 * @param y Numero de colunas da matriz.
 * @return true As dimensões da matriz sejam válidas.
 * @return false As dimensões da matriz não sejam válidas.
 */
bool ExisteMatriz(int x, int y) {
    // verifica se as dimensões da matriz são validas
    if (x <= 0 || y <= 0) return false;

    // as dimensões da matriz são validas
    return true;
}

/**
 * @brief Mostra o pre menu ao utilizador e pede uma opção.
 * 
 * @return int Opção escolhida pelo utilizador.
 */
int PreMenu() {
    // variavel para registar a opção escolhida pelo utilizador
    int op;

    // variavel para verificar se é para terminar o loop
    bool term = false;

    // enquanto não for para terminar o loop
    while (!term) {

        // limpa o terminal antes de mostrar o menu
        limpaTerminal();
        printf("Antes de começar:\n\n");

        // opções disponiveis para o utilizador escolher
        printf("1 - Criar nova Matriz\n");
        printf("2 - Carregar Matriz do ficheiro\n");
        printf("0 - Sair\n\n");

        // pergunta ao utilizador a opção pretendida
        printf("opção: ");
        // lê a opção
        scanf("%d", &op);
        printf("\n");

        // se a opção for valida, podemos terminar o loop
        if (op >= 0 && op <= 2) term = true;
        // caso não seja valida, o loop continua até ser escolhida uma opção valida
        else {
            printf("opção invalida!");
            pausar();
        }
    }

    // devolve a opção escolhida pelo utilizador
    return op;
}

/**
 * @brief Mostra o main menu ao utilizador e pede uma opção.
 * 
 * @return int Opção escolhida pelo utilizador.
 */
int MainMenu() {
    // variavel para registar a opção escolhida pelo utilizador
    int op;

    // variavel para verificar se é para terminar o loop
    bool term = false;

    // enquanto não for para terminar o loop
    while (!term) {
        // limpa o terminal antes de mostrar o menu
        limpaTerminal();
        printf("Escolha uma opção:\n\n");

        // opções disponiveis para o utilizador escolher
        printf("1 - Adicionar antena\n");
        printf("2 - Alterar antena\n");
        printf("3 - Remover antena\n");
        printf("4 - Mostrar matriz com efeito nefasto\n");
        printf("5 - Mostrar matriz sem efeito nefasto\n");
        printf("6 - Mostra lista das Antenas\n");
        printf("7 - Mostra lista do Efeito Nefasto\n");
        printf("8 - Guardar a matriz em ficheiro\n");
        printf("0 - Sair\n\n");

        // pergunta ao utilizador a opção pretendida
        printf("opção: ");
        // lê a opção
        scanf("%d", &op);
        printf("\n");

        // se a opção for valida, podemos terminar o loop
        if (op >= 0 && op <= 8) term = true;
        // caso não seja valida, o loop continua até ser escolhida uma opção valida
        else {
            printf("opção invalida!");
            pausar();
        }
    }

    // devolve a opção escolhida pelo utilizador
    return op;
}

/**
 * @brief Executa a funçao PreMenu e processa a opção escolhida pelo utilizador.
 * 
 * @param head Duplo apontador para o inicio da lista ligada das antenas.
 * @param inicioNef Duplo apontador para o inicio da lista ligada do efeito nefasto.
 * @param m Apontador para a variavel com as dimensões da matriz.
 * @return true Caso tenha conseguido concluir a opção escolhida pelo utilizador ou o utilizador não tenha escolhido sair do programa.
 * @return false Caso não tenha conseguido concluir a opção escolhida pelo utilizador ou o utilizador tenha escolhido sair do programa.
 */
bool ExecPreMenu(Antena** head, EfeitoNefasto** inicioNef, Matriz* m) {
    // variavel para saber se é para continuar 
    bool continua = false;

    // opção escolhida pelo utilizador na função PreMenu
    int op = PreMenu();

    // processar a opção escolhida pelo utilizador
    switch (op) {
        // criar uma nova matriz
        case 1:
            // se consegui criar a matriz, o programa continua
            if (CriaMatriz(m)) continua = true;
            break;

        // lê a informação sobre uma matriz presente num ficheiro txt
        case 2:
            // se conseguiu ler a informação do ficheiro, o programa continua
            if (LerFicheiroMatriz(head, m)) {

                // se leu as informações do ficheiro, temos de gerar o efeito nefasto
                *inicioNef = GeraNefasto(*inicioNef, *head, *m);
                continua = true;
            }
            break;
    }

    // devolve o estado da variavel continua (se o programa vai continuar ou não)
    return continua;
}

/**
 * @brief Executa a funçao MainMenu e processa a opção escolhida pelo utilizador.
 * 
 * @param head Apontador para o inicio da lista ligada das antenas.
 * @param inicioNef Duplo apontador para o inicio da lista ligada do efeito nefasto.
 * @param m Variavel com as dimensões da matriz.
 * @param term Apontador com a decisão que o utilizador tomou em relação a sair do programa.
 * @return Antena* Apontador para o inicio da lista ligada das antenas, agora atualizada.
 */
Antena* ExecMainMenu(Antena* head, EfeitoNefasto** inicioNef, Matriz m, bool* term) {
    // opção escolhida pelo utilizador na função MainMenu
    int op = MainMenu();

    // limpa o terminal antes de apresentar no terminal a opção escolhida
    limpaTerminal();

    // processar a opção escolhida pelo utilizador
    switch (op) {
        // cria e insere uma nova antena na lista
        case 1:
            head = CriaInsereAntena(head, m);
            break;
        // altera a informação de uma antena na lista
        case 2:
            head = AlteraAntena(head, m);
            break;
        // pergunta e remove uma antena da lista
        case 3:
            head = PerguntaRemoveAntena(head);
            break;
        // mostra no terminal a matriz com as antenas e o efeito nefasto
        case 4:
            MostraMatrizNefasto(head, *inicioNef, m);
            break;
        // mostra no terminal a matriz com as antenas, mas sem o efeito nefasto
        case 5:
            MostraMatrizAntenas(head, m);
            break;
        // mostra no terminal a lista das antenas, mas sem o efeito nefasto
        case 6:
            MostraListaAntenas(head);
            break;
        // mostra no terminal a lista do efeito nefasto
        case 7:
            MostraListaNefasto(*inicioNef);
            break;
        // guarda num ficheiro txt a matriz com as antenas, mas sem o efeito nefasto
        case 8:
            GuardarFicheiroMatriz(head, m);
            break;
        // o utilizador selecionou a opção '0', para sair do programa
        default:
            *term = true;
    }

    // se alterarmos ou removermos uma antena, temos de destruir a lista do efito nefasto, para evitar duplicações
    if (op == 2 || op == 3) DestroiListaNefasto(inicioNef);

    // se alterarmos, removermos ou criarmos uma antena, temos de gerar a lista do efeito nefasto
    if (op >= 1 && op <= 3) *inicioNef = GeraNefasto(*inicioNef, head, m);

    // devolve a lista ligada (das antenas) atualizada
    return head;
}
