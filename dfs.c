#include <stdio.h>
#include <stdlib.h>
#include "lista_adjacencia.h"

typedef enum Cor{
    BRANCO,
    CINZA,
    PRETO
}Cor;

typedef struct grafo{
    int v;
    int t_inicial;
    int t_final;
    Cor cor;
}Grafo;

int mark;


Grafo **definir_ordem (int **lista, int qtd) {

    Grafo **grafo;

    grafo = malloc(qtd * sizeof **grafo);
    if (grafo == NULL) {
        perror("Erro de alocação da lista de visita!\n");
        exit(0);
    }

    for (int i = 0; i < qtd; i++){
        grafo[i] = malloc(qtd * sizeof *grafo);
        if (grafo[i] == NULL) {
            perror("Erro de alocação dos grafos!\n");
            exit(0);
        }
    }

    for (int i = 0; i < qtd; i++) {
        grafo[i]->v = i;
    }

    return grafo;
}


void DFS_VISIT (Grafo *node, Grafo **grafo, int **lista, int qtd) {

    Grafo *v;
    node->cor = CINZA;
    mark++;
    node->t_inicial = mark;

    for (int i = 0; i < qtd; i++) {

        if (lista[node->v][i] == 0) {
            break;
        }

        v = grafo[lista[node->v][i]-1];

        if (v->cor == BRANCO) {
            DFS_VISIT(v, grafo, lista, qtd);
        }
    }

    node->cor = PRETO;
    mark++;
    node->t_final = mark;

    return;
}


void DFS(Grafo **grafo, int **lista, int qtd) {

    for (int i = 0; i < qtd; i++) {
        grafo[i]->cor = BRANCO;
    }

    mark = 0;

    for (int i = 0; i < qtd; i++) {
        if (grafo[i]->cor == BRANCO) {
            DFS_VISIT(grafo[i], grafo, lista, qtd);
        }
    }

    return;
}


void mostrar_tempos(Grafo **grafo, int qtd){

    printf("\n\n TEMPO INICIAL / FINAL\n\n");

    for (int i = 0; i < qtd; i++) {
        printf("%c:  %2d / %-2d\n", 'a' + i, grafo[i]->t_inicial,
                                             grafo[i]->t_final);
    }
}


int main(){

    int **lista;
    int qtd;
    Grafo **g_visitar;

    lista = carregar_lista(&qtd);
    mostrar_lista(lista, qtd);

    g_visitar = definir_ordem(lista, qtd);

    DFS(g_visitar, lista, qtd);

    mostrar_tempos(g_visitar, qtd);

    return 0;
}
