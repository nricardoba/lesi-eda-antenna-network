/**
 * @file nefasto.c
 * @author Ricardo Araújo (a21150@alunos.ipca.pt)
 * @brief Ficheiro que gere as funções sobre a lista ligada relativa ao efeito nefasto.
 * @version 0.1
 * @date 30-03-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "includes.h"

/**
 * @brief Cria um novo efeito nefasto com as coordenadas passadas por parâmetros.
 * 
 * @param x Coordenada x do efeito nefasto.
 * @param y Coordenada y do efeito nefasto.
 * @return EfeitoNefasto* Apontador para o novo efeito nefasto.
 */
EfeitoNefasto* CriaNefasto(int x, int y) {
    // aloca memoria para um elemento do tipo EfeitoNefasto*
    EfeitoNefasto* aux = (EfeitoNefasto*)malloc(sizeof(EfeitoNefasto));

    // se conseguiu alocar memoria, guarda os valores passados por parametros dentro da variavel
    if (aux) {
        aux->x = x;
        aux->y = y;

        // o proximo elemento da lista ainda não existe
        aux->next = NULL;
    }

    // devolve o elemento criado
    return aux;
}

/**
 * @brief Insere na lista ligada do efeito nefasto um novo elemento passada por parâmetros.
 * 
 * @param inicio Apontador para o inicio da lista ligada do efeito nefasto.
 * @param novo Apontador para o elemento que pretendemos introduzir na lista ligada do efeito nefasto.
 * @return EfeitoNefasto* Apontador para o inicio da lista ligada do efeito nefasto, agora atualizada.
 */
EfeitoNefasto* InsereNefasto(EfeitoNefasto* inicio, EfeitoNefasto* novo) {
    // se não existir o novo elemento, devolve a lista tal como estava
    if (!novo) return inicio;

    // se ainda não existir uma lista, o novo elemento é o primeiro e unico elemnto da lista
    if (!inicio) {
        inicio = novo;
        return inicio;
    }

    // variavel auxiliar
    EfeitoNefasto* aux = inicio;

    // se já existir lista e tambem existir o novo elemento, a lista é percorrida até ao ultimo elemento
    while (aux->next) {

        // avança uma celula da lista
        aux = aux->next;
    }

    // adiciona o novo alemento na celula asseguir ao ultimo, ficando o novo elemento como o ultimo elemento da lista
    aux->next = novo;

    // devolve a lista atualizada
    return inicio;
}

/**
 * @brief Percorre todos os elementos da lista ligada das antenas e cria o efeito nefasto que correspondem a cada antena.
 * 
 * @param inicioNefasto Apontador para o inicio da lista ligada do efeito nefasto.
 * @param head Apontador para o inicio da lista ligada das antenas.
 * @param m Variavel com as dimensões da matriz.
 * @return EfeitoNefasto* Apontador para o inicio da lista ligada do efeito nefasto, agora atualizada.
 */
EfeitoNefasto* GeraNefasto(EfeitoNefasto* inicioNefasto, Antena* head, Matriz m) {
    // se não existir uma lista de antenas, não há nenhum efeito nefasto para criar
    if (!head) return NULL;

    // antena atual
    Antena* atual = head;

    // antena para comparar com a atual para vereficar se existe efeito nefasto
    Antena* comparador = NULL;

    // percorre a lista das antenas até ao final
    while (atual) {

        // começa a comparar desde o inicio da lista
        comparador = head;

        // percorre a lista das antenas até ao final
        while (comparador) {

            // variavel para medir a distancia de uma antena para a outra
            int distancia = 0;

            // se existir efeito nefasto entre as duas antenas
            if (VerificaNefasto(*atual, *comparador, &distancia)) {

                // gera a coordenada x do novo efeito nefasto
                int novoX = atual->x + (atual->x - comparador->x);

                // gera a coordenada y do novo efeito nefasto
                int novoY = atual->y + (atual->y - comparador->y);

                // se ainda não existir efeito nefasto nessa posição e estiver dentro da matriz
                if (!ExisteNefasto(inicioNefasto, novoX, novoY) && CabeNaMatriz(m, novoX, novoY)) {

                    // cria um novo efeito nefasto
                    EfeitoNefasto* aux = CriaNefasto(novoX, novoY);

                    // adiciona esse efeito nefato na lista dos efeitos nefastos
                    inicioNefasto = InsereNefasto(inicioNefasto, aux);
                }
            }

            // avança uma celula da lista
            comparador = comparador->next;
        }

        // avança uma celula da lista
        atual = atual->next;
    }

    // devolve a lista atualizada
    return inicioNefasto;
}

/**
 * @brief Verifica se exite um efeito nefasto na lista ligada do efeito nefasto com as coordenadas passadas por parâmetro utilizando a função ExisteNefasto, caso exista, encontra esse efeito nefasto.
 * 
 * @param inicioNef Apontador para o inicio da lista ligada do efeito nefasto.
 * @param x Coordenada x do efeito nefasto.
 * @param y Coordenada y do efeito nefasto.
 * @return EfeitoNefasto* Apontador para o efeito nefasto encontrado.
 */
EfeitoNefasto* EncontraNefasto(EfeitoNefasto* inicioNef, int x, int y) {
    // se não existir um efeito nefasto com essas coordenadas, não ha nada para encontrar
    if (!ExisteNefasto(inicioNef, x, y)) return NULL;

    // variavel auxiliar
    EfeitoNefasto* aux = inicioNef;

    // percorre a lista até encontrar o elemento pretendido
    while (aux->x != x || aux->y != y) {

        // avança uma celula da lista
        aux = aux->next;
    }

    // devolve o efeito nefasto pretendido
    return aux;
}

/**
 * @brief Verifica se existe efeito nefasto entre duas antenas.
 * 
 * @param antena1 Variavel com as informações da primeira antena.
 * @param antena2 Variavel com as informações da segunda antena.
 * @param distancia Apontador para a variavel onde vai ser guardada a distância entre as duas antenas.
 * @return true Caso haja efeito nefasto.
 * @return false Caso não haja efeito nefasto.
 */
bool VerificaNefasto(Antena antena1, Antena antena2, int* distancia) {
    // variavei auxiliares
    int difx = 0, dify = 0;

    // verifica se as antenas têm a mesma frequencia
    if (antena1.frequencia == antena2.frequencia) {

        // verifica se não é a mesma antena
        if (antena1.x != antena2.x || antena1.y != antena2.y) {

            // calcula a diferença entre a coordenada x das duas antenas
            difx = antena1.x - antena2.x;
            // valor absoluto
            if (difx < 0) difx *= -1;

            // calcula a diferença entre a coordenada y das duas antenas
            dify = antena1.y - antena2.y;
            // valor absoluto
            if (dify < 0) dify *= -1;

            // soma as o valor absoluto das distancias
            // se a distancia não causar efeito nefasto, podemos sair
            if (difx + dify > TAMNEF) return false;

            // caso cause efeito nefasto, atribui o valor da distancia
            *distancia = difx + dify;
            return true;
        }
    }

    // as frequencias das duas antenas não são as mesmas
    // ou está a comparar a mesma antena
    return false;
}

/**
 * @brief Verifica se um efeito nefasto com as coordenadas passadas por parâmetro, existe na lista ligada do efeito nefasto.
 * 
 * @param inicioNef Apontador para o inicio da lista ligada do efeito nefasto.
 * @param x Coordenada x do efeito nefasto.
 * @param y Coordenada y do efeito nefasto.
 * @return true Caso já exista um efeito nefasto nessas coordenadas.
 * @return false Caso ainda não exista um efeito nefasto nessas coordenadas.
 */
bool ExisteNefasto(EfeitoNefasto* inicioNef, int x, int y) {
    // se não existir lista, não ha nada para procurar
    if (!inicioNef) return false;

    // variavel auxiliar
    EfeitoNefasto* aux = inicioNef;

    // percorre toda a lista
    while (aux != NULL) {

        // se as coordenadas coincidirem, é porque já existe efeito nefasto nessa posição
        if (aux->x == x && aux->y == y) {
            return true;
        }

        // avança uma celula da lista
        aux = aux->next;
    }

    // não existe efeito nefasto nessa posição
    return false;
}

/**
 * @brief Mostra no terminal a matriz, com todas as antenas e efeito nefasto presentes.
 * 
 * @param inicioAnt Apontador para o inicio da lista ligada das antenas.
 * @param inicioNef Apontador para o inicio da lista ligada do efeito nefasto.
 * @param m Variavel com as dimensões da matriz.
 */
void MostraMatrizNefasto(Antena* inicioAnt, EfeitoNefasto* inicioNef, Matriz m) {
    // variavei auxiliares
    Antena* anten = NULL;
    EfeitoNefasto* nefas = NULL;

    // percorre todas as linhas da matriz
    for (int i = 1; i <= m.linhas; i++) {
        // percorre todas as colunas da matriz
        for (int j = 1; j <= m.colunas; j++) {

            // procura uma antena nas coordenadas atuais
            anten = EncontraAntena(inicioAnt, i, j);

            // procura um efeito nefasto nas coordenadas atuais
            nefas = EncontraNefasto(inicioNef, i, j);

            // se existir uma antena nestas coordenadas, representa a sua frequencia
            if (anten) {
                printf("%c", anten->frequencia);

            // se não existir antena, mas existir efeito nefasto, representa o efeito nefasto
            } else if (nefas) {
                printf("%c", NEF);

            // se não existir antena nem efeito nefasto, representa vazio
            } else {
                printf("%c", EMPTY);
            }
        }
        printf("\n");
    }
    puts("\n");
}

/**
 * @brief Mostra no terminal a lista ligada do efeito nefasto.
 * 
 * @param inicio Apontador para o inicio da lista ligada do efeito nefasto.
 */
void MostraListaNefasto(EfeitoNefasto* inicio) {
    // se não existir uma lista de efeito nefato, nã ha nada para mostrar
    if (!inicio) return;

    // variavel auxiliar
    EfeitoNefasto* aux = inicio;

    printf("Lista de todos os efeitos nefastos:\n\n");

    // percorre a lista até ao final
    while (aux) {

        // mostra que existe efeito nefasto e as suas coordenadas
        printf("%c --> x: %d, y: %d\n", NEF, aux->x, aux->y);

        // avança uma celula da lista
        aux = aux->next;
    }
}

/**
 * @brief Destroi a lista ligada das antenas.
 * 
 * @param head Duplo apontador para o inicio da lista ligada do efeito nefasto.
 */
void DestroiListaNefasto(EfeitoNefasto** head) {
    // se existir uma lista
    if (head != NULL && *head != NULL) {

        // variavel auxiliar
        EfeitoNefasto* aux = NULL;

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
