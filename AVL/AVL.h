#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#include "ocorrencias.h"

struct TADAVL
{
    char palavra[20];
    int fator;
    struct TADAVL *esq;
    struct TADAVL *dir;

    struct TADOcorrencia *ocorrencia;
};
typedef struct TADAVL AVL;

AVL *InsereAVL(AVL *a, char *x, int *ok, int *nodos, int *comp, int *rot, int id);
AVL *InicializaAVL(char *x, int *ok);
AVL *Caso1(AVL *a, int *ok, int *rot);
AVL *Caso2(AVL *a, int *ok, int *rot);
AVL *rotacao_direita(AVL *p);
AVL *rotacao_esquerda(AVL *p);
AVL *rotacao_dupla_direita(AVL *p);
AVL *rotacao_dupla_esquerda(AVL *p);

void ImprimeArvore(AVL *a, int nivel);
int Altura(AVL *a);
AVL *ConsultaAVL(AVL *a, char *chave, int *comp);

#endif // AVL_H_INCLUDED
