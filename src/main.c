/**
 * @file main.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Ficheiro principal do programa que gere antenas e efeitos nefastos em uma matriz.
 * 
 * repositorio GitHub: https://github.com/ricardobara/TPEDA2425.git
 * 
 * @version 0.1
 * @date 30-03-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

int main() {
    Antena* grafoHead = NULL;

    DadosMatriz matriz;
    matriz.linhas = 0;
    matriz.colunas = 0;

    bool term = false;

    #pragma region Pre Menu

    int op = PreMenu();

    LimpaTerminal();
    switch (op) {
        case 1:
            matriz = CriaMatriz(matriz);
            break;
        case 2:
            grafoHead = LerFicheiroMatriz("antenas.txt", grafoHead, &matriz);

            if (!ValidaMatriz(matriz)) {
                printf("matriz invalida, vamos criar uma!\n");
                matriz = CriaMatriz(matriz);
            }

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
                    grafoHead = CriaInsereAntena(grafoHead, matriz);
                    GeraAdj(grafoHead);
                    GeraNefasto(grafoHead, matriz);
                    break;
                case 2:
                    grafoHead = AlteraAntena(grafoHead, matriz);
                    break;
                case 3:
                    grafoHead = PerguntaRemoveAntena(grafoHead);
                    break;
                case 4:
                    if (!MostraMatrizAntenas(grafoHead, matriz))
                        printf("não ha matriz!\n");
                    break;
                case 5:
                    if (!MostraMatrizNefasto(grafoHead, matriz))
                        printf("não ha matriz!\n");
                    break;
                case 6:
                    if (!MostraListaAntenas(grafoHead))
                        printf("não ha lista de antenas!\n");
                    break;
                case 7:
                    EscolheMostraAdj(grafoHead);
                    break;
                case 8:
                    MostraTodosNefastos(grafoHead);
                    break;
                case 9:
                    EscolheMostraNefasto(grafoHead);
                    break;
                case 10:
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

    grafoHead = DestroiAntenas(grafoHead);
    printf("programa terminado!\n\n");

    return 0;
}
