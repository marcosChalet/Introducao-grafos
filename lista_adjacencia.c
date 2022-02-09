#include <stdio.h>
#include <stdlib.h>
#include "alocador.h"

#define NOME_GRAFO "grafo.txt"

/*
 * O arquivo lido terá, na primeira linha, a quantidade de 'm' arestas e de
 * 'n' nós, respecticvamente, separadas por um espaço em branco. As próximas
 * 'n' linhas terão as arestas, representadas pelos dois primeiros números/nós
 * e seu peso.
 */


// Pega no arquivo as dimensões da lista em termos de nós e arestas.
void pega_dim (FILE **fp, int *nos, int *linhas){

    char linha_arq[1000], *pt_linhas;

    (*fp) = fopen(NOME_GRAFO,"r");
    if((*fp) == NULL){
        perror("Erro ao tentar abrir o arquivo!\n");
        exit(0);
    }

    fscanf((*fp), "%[^\n]s", linha_arq);
    getc((*fp));

    pt_linhas = &linha_arq[1];
    (*nos) = atoi(linha_arq);

    (*linhas) = atoi(pt_linhas);
}


// Aloca lista de adjacências e a inicia com zeros.
int **cria_lista (int dim){

    int **lista, **aux_aloca;

    aloca_mem((void***)&lista, PP_INT, dim * sizeof lista);

    for (int i = 0; i < dim; i++) {
        aux_aloca = &lista[i];
        aloca_mem((void***)&aux_aloca, P_INT, dim * sizeof lista);

        for (int j = 0; j < dim; j++)
            lista[i][j] = 0;
    }
    return lista;
}


void adiciona_elementos (FILE **fp, int ***lista,
                         int qtd_nos, int qtd_linhas) {

    char linha_arq[1000], *conv_i, *conv_j;
    int append[qtd_nos];

    for (int i = 0; i < qtd_nos; i++)
        append[i] = 0;

    for (int i = 0; i < qtd_linhas; i++){
        fscanf((*fp), "%[^\n]s", linha_arq);
        getc((*fp));
        conv_i = &linha_arq[0];
        conv_j = &linha_arq[1];

        (*lista)[atoi(conv_i)][append[atoi(conv_i)]++] = atoi(conv_j)+1;
        (*lista)[atoi(conv_j)][append[atoi(conv_j)]++] = atoi(conv_i)+1;
    }
}


// Carrega do arquivo uma lista de adjacências
int** carregar_lista (int *qtd_nos){

    char linha_arq[1000], *num_conv;
    int **lista;
    int qtd_linhas;
    FILE *fp;

    pega_dim(&fp, qtd_nos, &qtd_linhas);

    lista = cria_lista(*qtd_nos);

    adiciona_elementos(&fp, &lista, *qtd_nos, qtd_linhas);

    fclose(fp);

    return lista;
}


void mostrar_lista (int **lista, int dim){

    for (int i = 0; i < dim; i++) {
        if (lista[i][0] == 0)
            continue;

        printf("Vértice %d: [", i+1);
        for (int j = 0; j < dim; j++) {
            if (lista[i][j+1] == 0){
                printf("%d", lista[i][j]);
                break;
            }
            printf("%d, ", lista[i][j]);
        }
        printf("]\n");
    }
}
