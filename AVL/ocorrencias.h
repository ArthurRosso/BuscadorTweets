#ifndef OCORRENCIAS_H_INCLUDED
#define OCORRENCIAS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

struct TADOcorrencia {
    int id;
    struct TADOcorrencia *prox;
};
typedef struct TADOcorrencia Ocorrencia;


Ocorrencia *InicializaOcorrencia(int id);

#endif // OCORRENCIAS_H_INCLUDED
