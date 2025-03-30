/**
 * @file func.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Ficheiro que gere as funções sobre a lista ligada relativa às antenas.
 * @version 0.1
 * @date 30-03-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

/**
 * @brief Cria uma nova antena com as coordenadas e frequência passadas por parâmetros.
 * 
 * @param x Coordenada x da antena.
 * @param y Coordenada y da antena.
 * @param freq Frequência da antena.
 * @return Antena* Apontador para a nova antena.
 */
Antena* CriaAntena(int x, int y, char freq) {
    // aloca memoria para um elemento do tipo Antena*
    Antena* aux = (Antena*)malloc(sizeof(Antena));

    // se conseguiu alocar memoria, guarda os valores passados por parametros dentro da variavel
    if (aux) {
        aux->x = x;
        aux->y = y;
        aux->frequencia = freq;

        // o proximo elemento da lista ainda não existe
        aux->next = NULL;
    }

    // devolve o elemento criado
    return aux;
}

/**
 * @brief Insere na lista ligada das antenas um novo elemento passado por parâmetros.
 * 
 * @param head Apontador para o inicio da lista ligada das antenas.
 * @param novo Apontador para o elemento que pretendemos introduzir na lista ligada das antenas.
 * @return Antena* Apontador para o inicio da lista ligada das antenas, agora atualizada.
 */
Antena* InsereAntena(Antena* head, Antena* novo) {
    // se não existir o novo elemento, devolve a lista tal como estava
    if (!novo) return head;

    // se ainda não existir uma lista, o novo elemento é o primeiro e unico elemnto da lista
    if (!head) {
        head = novo;
        return head;
    }

    // variavel auxiliar
    Antena* aux = head;

    // se já existir lista e tambem existir o novo elemento, a lista é percorrida até ao ultimo elemento
    while(aux->next) {

        // avança uma celula da lista
        aux = aux->next;
    }

    // adiciona o novo alemento na celula asseguir ao ultimo, ficando o novo elemento como o ultimo elemento da lista
    aux->next = novo;

    // devolve a lista atualizada
    return head;
}

/**
 * @brief Remove da lista ligada das antenas uma antena com as coordenadas especificadas pelo utilizador e depois cria uma nova antena com dados especificados pelo utilizador.
 * 
 * @param head Apontador para o inicio da lista ligada das antenas.
 * @param m Variavel com as dimensões da matriz.
 * @return Antena* Apontador para o inicio da lista ligada das antenas, agora atualizada.
 */
Antena* AlteraAntena(Antena* head, Matriz m) {
    // se não existir uma lista, não ha nada para alterar
    if (!head) return NULL;

    // pergunta ao utilizador as coordenadas do elemento que pretende alterar
    int xTemp, yTemp;
    printf("coordenada x: ");
    scanf("%d", &xTemp);
    printf("coordenada y: ");
    scanf("%d", &yTemp);

    // procura por uma antena com as coordenadas selecionadas pelo utilizador
    Antena* aux = EncontraAntena(head, xTemp, yTemp);

    // se existir uma antena com essas coordenadas
    if (aux) {
        limpaTerminal();

        // remove a antena com as coordenadas selecionadas
        head = RemoveAntena(head, xTemp, yTemp);

        // pede ao utilizador as novas coordenadas
        printf("novas coordenadas:\n");

        // cria uma antena com as novas coordenadas
        head = CriaInsereAntena(head, m);
    }

    // devolve a lista atualizada
    return head;
}

/**
 * @brief Remove da lista ligada das antenas uma antena com as coordenadas passadas por parâmetro.
 * 
 * @param head Apontador para o inicio da lista ligada das antenas.
 * @param x Coordenada x da antena que pretendemos remover da lista.
 * @param y Coordenada y da antena que pretendemos remover da lista.
 * @return Antena* Apontador para o inicio da lista ligada das antenas, agora atualizada.
 */
Antena* RemoveAntena(Antena* head, int x, int y) {
    // se não existir uma lista, não ha nada para alterar
    if (!head) return NULL;

    // se a antena para eliminar for o inicio da lista
    if (head->x == x && head->y == y) {
        // variavel auxiliar para eliminar o primeiro elemento da lista
        Antena* aux = head;

        // o inicio passa a ser o segundo elemento da lista
        head = head->next;

        // elimina o primeiro elemento da lista
        free(aux);

    // no caso de o elemento a eliminar não ser o inicio da lista
    } else {
        Antena* atual = head;
        Antena* anterior = NULL;

        // percorre a lista até encontrar uma antena com as coordenadas pretendidas
        while (atual != NULL && (atual->x != x || atual->y != y)) {
            
            // guarda a antena anterior à atual
            anterior = atual;

            // avança uma celula da lista
            atual = atual->next;
        }

        // se encontrou um elemento com essas coordenadas, é eliminado
        if (atual != NULL) {

            // avança uma celula da lista
            anterior->next = atual->next;

            // elimina a antena pretendida
            free(atual);
        }
    }

    // devolve a lista atualizada
    return head;
}

/**
 * @brief Pede ao utilizador os dados de uma nova antena, cria essa antena utilizando a função CriaAntena e depois utiliza a função InsereAntena para introduzir essa antena na lista ligada das antenas.
 * 
 * @param head Apontador para o inicio da lista ligada das antenas.
 * @param m Variavel com as dimensões da matriz.
 * @return Antena* Apontador para o inicio da lista ligada das antenas, agora atualizada.
 */
Antena* CriaInsereAntena(Antena* head, Matriz m) {
    int xTemp, yTemp;
    char freqTemp;

    // pede ao utilizador as coordenadas da nova antena
    printf("coordenada x: ");
    scanf("%d", &xTemp);
    printf("coordenada y: ");
    scanf("%d", &yTemp);

    // se não existir nenhuma antena com essas coordenadas e as coordenadas fizerem parte da matriz
    if (!ExisteAntena(head, xTemp, yTemp) && CabeNaMatriz(m, xTemp, yTemp)) {
        // pede a frequencia da antena
        printf("frequencia: ");

        // limpar o buffer para evitar erros ao ler o caracter
        limpaBuffer();
        scanf("%c", &freqTemp);

        // se a frequencia da antena for valida
        if (ValidaCharAntena(freqTemp)) {
            // cria uma nova antena e adiciona na lista ligada
            Antena* point = CriaAntena(xTemp, yTemp, freqTemp);
            head = InsereAntena(head, point);

        // o caracter escolhido pelo utilizador é invalido
        } else {
            printf("char invalido!\n");
        }
    
    // o utolizador escolheu as coordenadas de uma antena já existente ou as coordenadas não cabem na matriz
    } else {
        printf("já existe uma antena com essas coordenadas ou não cabe na matriz!\n");
    }

    // devolve a lista atualizada
    return head;
}

/**
 * @brief Pergunta ao utilizador as coordenadas de uma antena para remover e remove essa antena utilizando a função RemoveAntena.
 * 
 * @param head Apontador para o inicio da lista ligada das antenas.
 * @return Antena* Apontador para o inicio da lista ligada das antenas, agora atualizada.
 */
Antena* PerguntaRemoveAntena(Antena* head) {
    // se não existir uma lista, não ha nada para alterar
    if (!head) {
        printf("ainda não existe nehuma antena\n");
        return NULL;
    }

    // pergunta ao utilizador as coordenadas da antena parab eliminar
    int xTemp, yTemp;
    printf("coordenada x: ");
    scanf("%d", &xTemp);
    printf("coordenada y: ");
    scanf("%d", &yTemp);

    // caso não exista nenhuma antena com as coordenadas pretendidas
    if (!ExisteAntena(head, xTemp, yTemp)) {
        printf("não existe nenhuma antena com essas coordenadas!\n");

    // se existe uma antena com as coordenadas pretendidas
    } else {
        // esta é eliminada
        head = RemoveAntena(head, xTemp, yTemp);
    }

    // devolve a lista atualizada
    return head;
}

/**
 * @brief Verifica se a posição com as coordenadas passadas por parâmetro faz parte da matriz.
 * 
 * @param m Variavel com as dimensões da matriz.
 * @param x Coordenada x.
 * @param y Coordenada y.
 * @return true Caso faça parte da matriz.
 * @return false Caso não faça parte da matriz.
 */
bool CabeNaMatriz(Matriz m, int x, int y) {
    // se as coordenadas do x e do y forem as duas 0, é porque a matriz não foi criada
    if (m.linhas <= 0 || m.colunas <= 0) return false;

    // as coordenadas não podem ser menores ou iguais a 0
    if (x <= 0 || y <= 0) return false;

    // se o x for menor ou igual ao numero de linhas
    // e o y tambem for menor ou igual ao numero de colunas,
    // concluimos que a antena cabe na matriz
    if (x <= m.linhas && y <= m.colunas) return true;

    // caso não verifica a condição anterior, concluimos que a antena não cabe na matriz
    return false;
}

/**
 * @brief Verifica se uma antena com as coordenadas passadas por parâmetro, existe na lista ligada das antenas.
 * 
 * @param head Apontador para o inicio da lista ligada das antenas.
 * @param x Coordenada x da antena.
 * @param y Coordenada y da antena.
 * @return true Caso exista uma antena com essas coordenadas.
 * @return false Caso não exista uma antena com essas coordenadas.
 */
bool ExisteAntena(Antena* head, int x, int y) {
    // se não existir lista, tambem não existe a antena
    if (!head) return false;

    Antena* aux = head;

    // percorre toda a lista
    while (aux != NULL) {

        // se existir uma antena com as coordenada pretendidas
        if (aux->x == x && aux->y == y) {
            return true;
        }

        // avança uma celula da lista
        aux = aux->next;
    }

    // significa que não existe nenhuma antena com as coordenadas pretendidas
    return false;
}

/**
 * @brief Verifica se exite uma antena com as coordenadas passadas por parâmetro utilizando a função ExisteAntena, caso exista, encontra essa antena.
 * 
 * @param head Apontador para o inicio da lista ligada das antenas.
 * @param x Coordenada x da antena.
 * @param y Coordenada y da antena.
 * @return Antena* Apontador para a antena encontrada.
 */
Antena* EncontraAntena(Antena* head, int x, int y) {
    // se não existe uma antena com as coordenadas pretendidas, não ha nada para encontrar
    if (!ExisteAntena(head, x, y)) return NULL;

    // variavel auxiliar
    Antena* aux = head;

    // percorre a lista enquanto não encontrar a antena com as coordenadas pretendidas
    while (aux->x != x || aux->y != y) {

        // avança uma celula da lista
        aux = aux->next;
    }

    // devolver a antena pretendida
    return aux;
}

/**
 * @brief Mostra no terminal a matriz, com todas as antenas presentes.
 * 
 * @param head Apontador para o inicio da lista ligada das antenas.
 * @param m Variavel com as dimensões da matriz.
 */
void MostraMatrizAntenas(Antena* head, Matriz m) {
    // variavel auxiliar
    Antena* aux = NULL;

    // percorre todas as linhas da matriz
    for (int i = 1; i <= m.linhas; i++) {

        // percorre todas as colunas da matriz
        for (int j = 1; j <= m.colunas; j++) {

            // tenta encontrar uma entena com as coordenadas pretendidas
            aux = EncontraAntena(head, i, j);

            // se existir uma antena com essas coordenadas
            if (aux) {
                // mostra essa antena
                printf("%c", aux->frequencia);

            // se não existir uma antena com essas coordenadas
            } else {
                // mostra que essas coordenadas não têm antena
                printf("%c", EMPTY);
            }
        }
        printf("\n");
    }
    puts("\n");
}

/**
 * @brief Mostra no terminal a lista ligada das antenas.
 * 
 * @param head Apontador para o inicio da lista ligada das antenas.
 */
void MostraListaAntenas(Antena* head) {
    // se não existir uma lista, não ha nada para mostrar
    if (!head) return;

    // variavel auxiliar
    Antena* aux = head;

    printf("Lista de todas as antenas:\n\n");

    // percorre toda a lista
    while (aux) {
        
        // mostra a frequencia da antena e as suas coordenadas
        printf("%c --> x: %d, y: %d\n", aux->frequencia, aux->x, aux->y);

        // passa para a celula seguinte
        aux = aux->next;
    }
}

/**
 * @brief Lê de um ficheiro .txt a informação de uma matriz, assim com as antenas presentes na mesma.
 * 
 * @param head Duplo apontador para o inicio da lista ligada das antenas.
 * @param m Apontador para a variavel com as dimensões da matriz.
 * @return true Se conseguiu ler com sucesso a informação do ficheiro.
 * @return false Se a informação presente no ficheiro é inválida.
 */
bool LerFicheiroMatriz(Antena** head, Matriz* m) {
    // abre o ficheiro que tem presente a informação sobre as antenas
    FILE* fp = fopen("antenas.txt", "rt");

    // caso não tenha conseguido abrir o ficheiro, ou se ele não existe
    if (fp == NULL) return false;

    // destroi a lista das antenas, para começar uma do zero
    DestroiListaAntenas(head);

    int numLinhas = 0, numColunas = 0, colunasAtual = 0;
    char tempChar = EMPTY;

    // limpa o buffer, pois vai ler caracteres
    limpaBuffer();

    // percorre o ficheiro e lê os seus caracteres até ao final
    while ((tempChar = fgetc(fp)) != EOF) {

        // se o caracter for '\n' é porque uma linha chegou ao final
        if (tempChar == '\n') {

            // na primeira linha
            if (numLinhas == 0) {

                // definir o número de colunas na primeira linha
                numColunas = colunasAtual;

            // se duas linhas tiverem o numero de colunas diferente, o ficheiro é invalido
            } else if (colunasAtual != numColunas) {

                // não lê a matriz
                fclose(fp);
                return false;
            }

            // incrementa 1 ao numero de linhas
            numLinhas++;

            // reiniciar a contagem de colunas para a próxima linha
            colunasAtual = 0;

        // se o caracter lido for != '\n' incrementa 1 ao numero de colunas
        } else {
            colunasAtual++;
        }
    }

    // se o numero de linhas ou de colunas for 0, a matriz é invalida
    if (numLinhas == 0 || numColunas == 0) {

        // não lê a matriz
        fclose(fp);
        return false;
    }

    // se chegou aqui é porque a matriz é valida

    // guarda o numero de linhas da matriz
    m->linhas = numLinhas;

    // guarda o numero de colunas da matriz
    m->colunas = numColunas;

    // voltar ao início do ficheiro para ler os dados
    rewind(fp);

    // variavei auxiliares
    Antena* aux = NULL;
    tempChar = EMPTY;

    // percorre todas as linhas da matriz
    for (int i = 1; i <= m->linhas; i++) {

        // percorre todas as colunas da matriz
        for (int j = 1; j <= m->colunas; j++) {

            // lê todos os caracteres da matriz até encontrar o final de uma linha
            do {
                fscanf(fp, "%c", &tempChar);
            } while (tempChar == '\n');

            // se o caracter representar uma frequencia
            if (ValidaCharAntena(tempChar)) {

                // cria uma nova antena
                aux = CriaAntena(i, j, tempChar);

                // insere essa antena na lista ligada
                *head = InsereAntena(*head, aux);
            }
        }
    }

    // fecha o ficheiro
    fclose(fp);

    // conseguiu ler o ficheiro com sucesso
    return true;
}

/**
 * @brief Guarda num ficheiro .txt a matriz, com as antenas presentes na mesma.
 * 
 * @param head Apontador para o inicio da lista ligada das antenas.
 * @param m Variavel com as dimensões da matriz.
 */
void GuardarFicheiroMatriz(Antena* head, Matriz m) {
    // se não existir nenhuma matriz, não ha nada para guardar
    if (!ExisteMatriz(m.linhas, m.colunas)) {
        printf("não existe matriz!\n");
        return;
    }

    // abre ou cria um ficheiro das antenas
    FILE* fp = fopen("antenas.txt", "wt");

    // caso não tenha conseguido abrir o ficheiro
    if (fp == NULL) return;

    // variaveis auxiliares
    Antena* aux = NULL;
    char charTemp;

    // percorre todas as linhas da matriz
    for (int i = 1; i <= m.linhas; i++) {

        // percorre todas as colunas da matriz
        for (int j = 1; j <= m.colunas; j++) {

            // tenta encontar uma antena com as coordenadas atuais
            aux = EncontraAntena(head, i, j);

            // se encontrou, quer representar a frequencia dessa antena na matriz
            if (aux) charTemp = aux->frequencia;

            // caso não tenha encontrado nenhuma antena com as coordenadas atuais
            // representa com o caracter que representa vazio
            else charTemp = EMPTY;

            // escreve no ficheiro o caracter pretendido
            fprintf(fp, "%c", charTemp);
        }

        // quando chega ao fim de uma linha representa o \n para mudar de linha
        fprintf(fp, "\n");
    }

    // fecha o ficheiro
    fclose(fp);

    // diz ao utilizador que os dados foram guardados
    printf("dados guardados!\n");
}

/**
 * @brief Destroi a lista ligada das antenas.
 * 
 * @param head Duplo apontador para o inicio da lista ligada das antenas.
 */
void DestroiListaAntenas(Antena** head) {
    // se existir uma lista
    if (head != NULL && *head != NULL) {

        // variavel auxiliar
        Antena* aux = NULL;

        // enquanto existir pelo menos um elemento na lista
        while (*head) {

            // elimina esse elemnto
            aux = *head;
            *head = (*head)->next;
            free(aux);
        }

        // para certeficar que não ficou nenhum elemenro na lista
        *head = NULL;
    }
}

/**
 * @brief Verifica se o caracter passado por parâmetros pode representar a frequência de uma antena.
 * 
 * @param letra Caracter que representa a frequência de uma antena.
 * @return true Representa a frequência de uma antena.
 * @return false Não representa a frequência de uma antena.
 */
bool ValidaCharAntena(char letra) {
    // se o caracter não for um caracter restrito
    if (letra != EMPTY && letra != NEF && letra != SPACE) return true;
    return false;
}
