/**
 * @file termio.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 11-05-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

Antena* CriaInsereAntena(Antena* antenaHead, DadosMatriz matriz) {
    DadosAntena temp;

    printf("x: ");
    scanf("%d", &temp.x);
    printf("y: ");
    scanf("%d", &temp.y);

    if (EncontraAntena(antenaHead, temp.x, temp.y) || !CabeNaMatriz(matriz, temp.x, temp.y))
        return antenaHead;

    printf("frequencia: ");
    LimpaBuffer();
    scanf("%c", &temp.freq);

    if (!ValidaCharAntena(temp.freq)) return antenaHead;

    Antena* aux = CriaAntena(temp);
    antenaHead = InsereAntena(antenaHead, aux);

    return antenaHead;
}

bool MostraListaAntenas(Antena* antenaHead) {
    // não ha nada para mostrar
    if (!antenaHead) return false;

    Antena* aux = antenaHead;
    int contador = 0;

    while (aux) {
        printf("[%d]: %c --> x: %d, y: %d\n", contador++, aux->dados.freq, aux->dados.x, aux->dados.y);
        aux = aux->next;
    }

    return true;
}

bool MostraMatrizAntenas(Antena* antenaHead, DadosMatriz matriz) {
    if (matriz.linhas <= 0 || matriz.colunas <= 0) return false;

    for (int i = 1; i <= matriz.linhas; i++) {
        for (int j = 1; j <= matriz.colunas; j++) {
            Antena* aux = EncontraAntena(antenaHead, i, j);

            char temp = VAZIO;
            if (aux) temp = aux->dados.freq;
            printf("%c", temp);
        }
        printf("\n");
    }
    puts("\n");

    return true;
}

// a função está correta, mas tens de a tentar perceber melhor
Antena* LerFicheiroMatriz(char* ficheiro, Antena* antenaHead, DadosMatriz* matriz) {
    FILE* fp = fopen(ficheiro, "rt");
    // se não conseguimos abrir o ficheiro, devolvemos a lista tal como estava
    if (!fp) return antenaHead;

    // destuir uma lista, para criar uma nova
    antenaHead = DestroiAntenas(antenaHead);

    matriz->linhas = 0;
    matriz->colunas = 0;
    int colunasAtual = 0;
    char tempChar;

    // pode vir a ser necessario
    // LimpaBuffer();

    while ((tempChar = fgetc(fp)) != EOF) {
        if (tempChar == END_LINE) {
            if (matriz->linhas < MAX_MATRIZ) matriz->linhas++;

            if (matriz->colunas < colunasAtual)
                matriz->colunas = colunasAtual;
                
            colunasAtual = 0;
        }
        else if (colunasAtual < MAX_MATRIZ) {
            colunasAtual++;

            // acho que não é preciso verificar se já existe uma antena com as coordenadas atuais,
            // porque estámos a criar uma lista nova
            if (ValidaCharAntena(tempChar)) {
                DadosAntena tempDados;
                tempDados.x = matriz->linhas + 1;
                tempDados.y = colunasAtual;
                tempDados.freq = tempChar;

                Antena* aux = CriaAntena(tempDados);
                antenaHead = InsereAntena(antenaHead, aux);
            }
        }
    }

    // verificar se a ultima linha não foi contada (caso o ficheiro não termine com '\n')
    if (colunasAtual > 0 && matriz->linhas < MAX_MATRIZ) {
        matriz->linhas++;

        if (matriz->colunas < colunasAtual)
            matriz->colunas = colunasAtual;
    }
    fclose(fp);

    return antenaHead;
}

bool GuardarFicheiroMatriz(char* ficheiro, Antena* antenaHead, DadosMatriz matriz) {
    if (!ValidaMatriz(matriz)) return false;

    FILE* fp = fopen(ficheiro, "wt");
    if (!fp) return false;

    for (int i = 1; i <= matriz.linhas; i++) {
        for (int j = 1; j <= matriz.colunas; j++) {
            Antena* aux = EncontraAntena(antenaHead, i, j);

            char temp = VAZIO;
            if (aux) temp = aux->dados.freq;
            fprintf(fp, "%c", temp);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

    return true;
}

DadosMatriz CriaMatriz(DadosMatriz matriz) {
    DadosMatriz temp;
    printf("linhas: ");
    scanf("%d", &temp.linhas);
    printf("colunas: ");
    scanf("%d", &temp.colunas);

    if (!ValidaMatriz(temp)) {
        matriz.linhas = 10;
        matriz.colunas = 10;

        return matriz;
    }

    matriz = temp;
    return matriz;
}
