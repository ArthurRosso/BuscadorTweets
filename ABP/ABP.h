#ifndef ABP_H_INCLUDED
#define ABP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#include "ocorrencias.h"

struct TADABP {
    char palavra[20];
    struct TADABP *esq;
    struct TADABP *dir;

    struct TADOcorrencia *ocorrencia;
};
typedef struct TADABP ABP;

ABP* InsereABP (ABP *a, char *x, int *nodos, int *comp, int id);

void ImprimeArvore (ABP *a, int nivel);
int Altura (ABP *a);
ABP* ConsultaABP(ABP *a, char *chave, int *comp);


#endif // ABP_H_INCLUDED
