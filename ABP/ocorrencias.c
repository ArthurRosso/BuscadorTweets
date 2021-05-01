#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#include "ocorrencias.h"

/*
 * Inicializa uma nova ocorrência
 *
 * @param id        novo id para adicionar na lista
 * @return          nova ocorrência
 */ 
Ocorrencia *InicializaOcorrencia(int id)
{
    Ocorrencia *oco = malloc(sizeof(Ocorrencia)); // aloca o ponteiro da ocorrência
    oco->id = id; // passa o id para a lista
    oco->prox = NULL; // inicializa a próxima occorrência como nula

    return oco; // retorna a ocorrência
}
