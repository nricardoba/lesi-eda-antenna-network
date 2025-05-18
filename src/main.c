/**
 * @file main.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Ficheiro principal do programa que gere o grafo.
 * 
 * repositorio GitHub: https://github.com/ricardobara/TPEDA2425.git
 * 
 * @version 0.1
 * @date 18-05-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

/**
 * @brief Inicializa o grafo e a matriz. Gere os menus do programa.
 * 
 * @return int 
 */
int main() {
    // inicialização do grafo
    Antena* grafoHead = NULL;

    // inicialização da matriz
    DadosMatriz matriz;
    matriz.linhas = 0;
    matriz.colunas = 0;

    // variavel que determina quando o programa acaba
    bool term = false;

    #pragma region Pre Menu

    int op = PreMenu();

    LimpaTerminal();
    switch (op) {
        case 1:
            // criar uma matriz limpa
            matriz = CriaMatriz(matriz);
            break;
        case 2:
            // ler os dados das antenas e da matriz do ficheiro txt
            grafoHead = LerFicheiroMatriz("antenas.txt", grafoHead, &matriz);

            // se os dados lidos sobre a matriz forem invalidos
            if (!ValidaMatriz(matriz)) {
                printf("matriz invalida, vamos criar uma!\n");

                // criamos uma matriz limpa
                matriz = CriaMatriz(matriz);
            }

            // gerar as listas de adj e nefasto
            GeraAdj(grafoHead);
            GeraNefasto(grafoHead, matriz);

            break;
        default:
            term = true;
    }

    #pragma endregion
    #pragma region Main Menu

    if (!term) {
        while (!term) {
            op = MainMenu();
            LimpaTerminal();

            switch (op) {
                case 1:
                    // criar e inserir uma antena e gerar as respectivas listas de adj e nefastos
                    grafoHead = CriaInsereAntena(grafoHead, matriz);
                    GeraAdj(grafoHead);
                    GeraNefasto(grafoHead, matriz);
                    break;
                case 2:
                    // alterar os dados de uma antena
                    grafoHead = AlteraAntena(grafoHead, matriz);
                    break;
                case 3:
                    // remover uma antena do grafo
                    grafoHead = PerguntaRemoveAntena(grafoHead);
                    break;
                case 4:
                    // mostrar a matriz so com as antenas
                    if (!MostraMatrizAntenas(grafoHead, matriz))
                        printf("não ha matriz!\n");
                    break;
                case 5:
                    // mostrar a matriz completa
                    if (!MostraMatrizNefasto(grafoHead, matriz))
                        printf("não ha matriz!\n");
                    break;
                case 6:
                    // mostrar a lista das antenas
                    if (!MostraListaAntenas(grafoHead))
                        printf("não ha lista de antenas!\n");
                    break;
                case 7:
                    // mostrar a lista de adj de uma antena
                    EscolheMostraAdj(grafoHead);
                    break;
                case 8:
                    // mostrar todos os efeitos nefastos do grafo
                    MostraTodosNefastos(grafoHead);
                    break;
                case 9:
                    // mostar os efeitos nefastos de uma antena
                    EscolheMostraNefasto(grafoHead);
                    break;
                case 10:
                    // guardar num ficheiro de texto a mariz apenas com as antenas
                    if (GuardarFicheiroMatriz("antenas.txt", grafoHead, matriz))
                        printf("dados guardados com sucesso!\n");
                    else
                        printf("não foi possivel guardar os dados!\n");
                    break;
                default:
                    term = true;
            }
            if (!term) Pausar();
        }
    }

    #pragma endregion

    // destroir o grafo
    grafoHead = DestroiAntenas(grafoHead);
    printf("programa terminado!\n\n");

    return 0;
}
