#include "ocorrencias.h"

Ocorrencia *InicializaOcorrencia(int id)
{
    Ocorrencia *oco = malloc(sizeof(Ocorrencia));
    oco->id = id;
    oco->prox = NULL;

    return oco;
}
