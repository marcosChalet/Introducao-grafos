#ifndef _ALOCADOR_H
#define _ALOCADOR_H

typedef enum{
    P_INT,      // definição do tipo int*
    PP_INT,     // definição do tipo int**
    P_CHAR      // definição do tipo char*
}Tipo_var;

void aloca_mem (void*** p_ref, Tipo_var __tipo, size_t size);

#endif // !_ALOCADOR_H
