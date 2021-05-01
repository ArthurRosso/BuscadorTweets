#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

#include "ocorrencias.h"

/*
 * Estrutura que representa uma árvore AVL
 */ 
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
AVL *InicializaAVL(char *x);
AVL *Caso1(AVL *a, int *ok, int *rot);
AVL *Caso2(AVL *a, int *ok, int *rot);
AVL *rotacao_direita(AVL *p);
AVL *rotacao_esquerda(AVL *p);
AVL *rotacao_dupla_direita(AVL *p);
AVL *rotacao_dupla_esquerda(AVL *p);

void ImprimeArvore(AVL *a, int nivel);
int Altura(AVL *a);
AVL *ConsultaAVL(AVL *a, char *chave, int *comp);
int EhAVL(AVL *a);

#endif // AVL_H_INCLUDED
