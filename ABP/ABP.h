#ifndef ABP_H_INCLUDED
#define ABP_H_INCLUDED

#include "ocorrencias.h"

/*
 * Estrutura que representa uma árvore ABP
 */ 
struct TADABP {
    char palavra[20];
    struct TADABP *esq;
    struct TADABP *dir;

    struct TADOcorrencia *ocorrencia;
};
typedef struct TADABP ABP;

ABP *InsereABP (ABP *a, char *x, int *nodos, int *comp, int id);
ABP *InicializaABP(char *x);

void ImprimeArvore (ABP *a, int nivel);
int Altura (ABP *a);
ABP *ConsultaABP(ABP *a, char *chave, int *comp);


#endif // ABP_H_INCLUDED
