#include <stdio.h>
#include <stdlib.h>
#include "alocador.h"

/*
 * Alocador de memória - Passa size bytes para p_ref utilizando
 * da enumeração Tipo_var para definir o tipo da alocação requerida.
 */

void aloca_mem (void*** p_ref, Tipo_var __tipo, size_t size){

    switch (__tipo) {
    case P_INT:
        (**p_ref) = malloc(size);

        if ((**p_ref) == NULL) {
            perror("Erro de alocação de memória [P_INT]!\n");
            exit(0);
        }

        break;

    case PP_INT:
        (*p_ref) = malloc(size);

        if ((*p_ref) == NULL) {
            perror("Erro de alocação de memória [PP_INT]!\n");
            exit(0);
        }

        break;

    case P_CHAR:

        (**p_ref) = (char*) malloc(size);

        if ((*p_ref) == NULL){
            perror("Erro de alocação de memória [P_CHAR]!\n");
            exit(0);
        }

        break;

    default:
        printf("Opção inválida: <void*** p_ref>,",
                                "<Tipo_var __tipo>,",
                                "<size_t size>");
    }
}
