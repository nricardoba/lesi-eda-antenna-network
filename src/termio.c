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
    Coordenadas coorTemp = PedeCoordenadas("Coordenadas:\n");

    if (EncontraAntena(antenaHead, coorTemp.x, coorTemp.y) || !CabeNaMatriz(matriz, coorTemp.x, coorTemp.y))
        return antenaHead;

    DadosAntena dadosTemp;
    dadosTemp.x = coorTemp.x;
    dadosTemp.y = coorTemp.y;

    printf("frequencia: ");
    LimpaBuffer();
    scanf("%c", &dadosTemp.freq);

    if (!ValidaCharAntena(dadosTemp.freq)) return antenaHead;

    Antena* aux = CriaAntena(dadosTemp);
    antenaHead = InsereAntena(antenaHead, aux);

    return antenaHead;
}

Antena* PerguntaRemoveAntena(Antena* antenaHead) {
    if (!antenaHead) {
        printf("não existe uma lista!\n");
        return NULL;
    }

    Coordenadas coorTemp = PedeCoordenadas("que antena pretende remover?\n");
    Antena* aux = EncontraAntena(antenaHead, coorTemp.x, coorTemp.y);

    if (!aux) {
        printf("não existe nenhuma antena com essas coordenadas!\n");
        return antenaHead;
    }

    antenaHead = RemoveAntena(antenaHead, aux);
    printf("antena removida com sucesso!\n");
    
    return antenaHead;
}

Antena* AlteraAntena(Antena* antenaHead, DadosMatriz matriz) {
    if (!antenaHead) {
        printf("não existe uma lista!\n");
        return NULL;
    }

    Coordenadas coorTemp = PedeCoordenadas("que antena pretende alterar?");
    Antena* aux = EncontraAntena(antenaHead, coorTemp.x, coorTemp.y);

    if (!aux) {
        printf("não existe nenhuma antena com essas coordenadas!\n");
        return antenaHead;
    }

    coorTemp = PedeCoordenadas("Novos dados da antena:");
    if (!CabeNaMatriz(matriz, coorTemp.x, coorTemp.y) || EncontraAntena(antenaHead, coorTemp.x, coorTemp.y)) {
        printf("coordenadas invalidas!\n");
        return antenaHead;
    }

    char freqTemp;
    printf("frequencia: ");
    LimpaBuffer();
    scanf("%c", &freqTemp);
    printf("\n");

    if (!ValidaCharAntena(freqTemp)) {
        printf("frequencia invalida!\n");
        return antenaHead;
    }

    aux->dados.x = coorTemp.x;
    aux->dados.y = coorTemp.y;
    aux->dados.freq = freqTemp;

    printf("dados alterados com sucesso!\n");

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

bool MostraListaNefasto(Nefasto* nefastoHead) {
    if (!nefastoHead) return false;

    Nefasto* aux = nefastoHead;
    int contador = 0;

    while (aux) {
        printf("[%d]: %c (%c) --> x: %d, y: %d\n", contador++, NEF, aux->dados.freq, aux->dados.x, aux->dados.y);
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

bool MostraMatrizNefasto(Antena* antenaHead, Nefasto* nefastoHead, DadosMatriz matriz) {
    if (matriz.linhas <= 0 || matriz.colunas <= 0) return false;

    for (int i = 1; i <= matriz.linhas; i++) {
        for (int j = 1; j <= matriz.colunas; j++) {
            Antena* antAux = EncontraAntena(antenaHead, i, j);
            Nefasto* nefAux = EncontraNefasto(nefastoHead, i, j);

            char temp = VAZIO;
            if (antAux && nefAux) temp = SBP;
            else if (antAux) temp = antAux->dados.freq;
            else if (nefAux) temp = NEF;
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

Coordenadas PedeCoordenadas(char* mensagem) {
    Coordenadas aux;

    printf("%s\n", mensagem);
    printf("x: ");
    scanf("%d", &aux.x);
    printf("y: ");
    scanf("%d", &aux.y);
    printf("\n");

    return aux;
}
