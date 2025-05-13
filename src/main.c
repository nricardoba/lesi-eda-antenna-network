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
    Antena* antenaHead = NULL;
    Nefasto* nefastoHead = NULL;

    DadosMatriz matriz;
    matriz.linhas = 0;
    matriz.colunas = 0;

    int op = PreMenu();
    bool term = false;

    LimpaTerminal();
    switch (op) {
        case 1:
            matriz = CriaMatriz(matriz);
            break;
        case 2:
            antenaHead = LerFicheiroMatriz("antenas.txt", antenaHead, &matriz);

            if (!ValidaMatriz(matriz)) {
                printf("matriz invalida, vamos criar uma!\n");
                matriz = CriaMatriz(matriz);
            }

            nefastoHead = GeraNefasto(antenaHead, nefastoHead, matriz);

            break;
        default:
            term = true;
    }

    if (!term) {
        while (!term) {
            op = MainMenu();
            LimpaTerminal();

            switch (op) {
                case 1:
                    antenaHead = CriaInsereAntena(antenaHead, matriz);
                    nefastoHead = GeraNefasto(antenaHead, nefastoHead, matriz);
                    break;
                case 2:
                    antenaHead = AlteraAntena(antenaHead, matriz);
                    break;
                case 3:
                    antenaHead = PerguntaRemoveAntena(antenaHead);
                    break;
                case 4:
                    if (!MostraMatrizNefasto(antenaHead, nefastoHead, matriz))
                        printf("não ha matriz!\n");
                    break;
                case 5:
                    if (!MostraMatrizAntenas(antenaHead, matriz))
                        printf("não ha matriz!\n");
                    break;
                case 6:
                    if (!MostraListaAntenas(antenaHead))
                        printf("não ha lista de antenas!\n");
                    break;
                case 7:
                    if (!MostraListaNefasto(nefastoHead))
                        printf("não ha lista de antenas!\n");
                    break;
                case 8:
                    if (GuardarFicheiroMatriz("antenas.txt", antenaHead, matriz))
                        printf("dados guardados com sucesso!\n");
                    else
                        printf("não foi possivel guardar os dados!\n");
                    break;
                default:
                    term = true;
            }

            if (op == 2 || op == 3) {
                nefastoHead = DestroiNefasto(nefastoHead);
                nefastoHead = GeraNefasto(antenaHead, nefastoHead, matriz);
            }

            if (!term) Pausar();
        }
    }

    nefastoHead = DestroiNefasto(nefastoHead);
    antenaHead = DestroiAntenas(antenaHead);
    printf("programa terminado!\n\n");

    return 0;
}
