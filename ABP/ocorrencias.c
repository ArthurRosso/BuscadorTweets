#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#include "ocorrencias.h"

Ocorrencia *InicializaOcorrencia(int id)
{
    Ocorrencia *oco = malloc(sizeof(Ocorrencia));
    oco->id = id;
    oco->prox = NULL;

    return oco;
}
