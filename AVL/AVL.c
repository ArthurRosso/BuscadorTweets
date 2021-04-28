#include "AVL.h"
#include "ocorrencias.h"

AVL *InsereAVL(AVL *a, char *x, int *ok, int *nodos, int *comp, int *rot, int id)
{
    if (a == NULL)
    {
        a = (AVL *)malloc(sizeof(AVL));
        strcpy(a->palavra, x);
        a->esq = NULL;
        a->dir = NULL;
        a->fator = 0;
        *ok = 1;

        a->ocorrencia = malloc(sizeof(Ocorrencia));
        a->ocorrencia->id = id;
        a->ocorrencia->prox = NULL;

        (*nodos)++;
        (*comp)++;
    }
    else if (strcmp(x, a->palavra) < 0)
    { // x < a->palavra
        (*comp) += 2;
        a->esq = InsereAVL(a->esq, x, ok, nodos, comp, rot, id);
        if (*ok)
        {
            switch (a->fator)
            {
            case -1:
                a->fator = 0;
                *ok = 0;
                break;
            case 0:
                a->fator = 1;
                break;
            case 1:
                a = Caso1(a, ok, rot);
                break;
            }
        }
    }
    else if (strcmp(x, a->palavra) > 0)
    { // x > a->palavra
        (*comp) += 3;
        a->dir = InsereAVL(a->dir, x, ok, nodos, comp, rot, id);
        if (*ok)
        {
            switch (a->fator)
            {
            case 1:
                a->fator = 0;
                *ok = 0;
                break;
            case 0:
                a->fator = -1;
                break;
            case -1:
                a = Caso2(a, ok, rot);
                break;
            }
        }
    }
    else
    {
        *ok=0;
        (*comp) += 3;
        Ocorrencia *oco = a->ocorrencia;
        while (oco->prox != NULL)
        {
            if (oco->id == id)
            {
                return a;
            }
            oco = oco->prox;
        }
        if (oco->id == id)
        {
            return a;
        }
        oco->prox = malloc(sizeof(Ocorrencia));
        oco->prox->id = id;
        oco->prox->prox = NULL;
    }
    return a;
}

AVL *ConsultaAVL(AVL *a, char *chave, int *comp)
{
    while (a != NULL)
    {
        if (strcmp(a->palavra, chave) > 0)
        {
            (*comp)++;
            a = a->esq;
        }
        else if (strcmp(a->palavra, chave) < 0)
        {
            (*comp)+=2;
            a = a->dir;
        }
        else
        {
            (*comp)+=2;
            return a;
        }
    }
    return NULL;
}


AVL *Caso1(AVL *a, int *ok, int *rot)
{
    AVL *z;
    z = a->esq;
    if (z->fator == 1)
    {
        a = rotacao_direita(a);
        (*rot)++;
    }
    else
    {
        a = rotacao_dupla_direita(a);
        (*rot) += 2;
    }
    a->fator = 0;
    *ok = 0;
    return a;
}

AVL *Caso2(AVL *a, int *ok, int *rot)
{
    AVL *z;
    z = a->dir;
    if (z->fator == -1)
    {
        a = rotacao_esquerda(a);
        (*rot)++;
    }
    else
    {
        a = rotacao_dupla_esquerda(a);
        (*rot) += 2;
    }
    a->fator = 0;
    *ok = 0;
    return a;
}

AVL *rotacao_direita(AVL *p)
{
    AVL *u;
    u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->fator = 0;
    p = u;
    return p;
}

AVL *rotacao_esquerda(AVL *p)
{
    AVL *z;
    z = p->dir;
    p->dir = z->esq;
    z->esq = p;
    p->fator = 0;
    p = z;
    return p;
}

AVL *rotacao_dupla_direita(AVL *p)
{
    AVL *u, *v;
    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;
    if (v->fator == 1)
        p->fator = -1;
    else
        p->fator = 0;
    if (v->fator == -1)
        u->fator = 1;
    else
        u->fator = 0;
    p = v;
    return p;
}

AVL *rotacao_dupla_esquerda(AVL *p)
{
    AVL *z, *y;
    z = p->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    p->dir = y->esq;
    y->esq = p;
    if (y->fator == -1)
        p->fator = 1;
    else
        p->fator = 0;
    if (y->fator == 1)
        z->fator = -1;
    else
        z->fator = 0;
    p = y;
    return p;
}

void ImprimeArvore(AVL *a, int nivel)
{
    int i;
    if (a != NULL)
    {
        for (i = 0; i <= nivel; i++)
        {
            printf("=");
        }
        printf("%s ", a->palavra);
        printf("fator %d\n", a->fator);
        ImprimeArvore(a->esq, nivel + 1);
        ImprimeArvore(a->dir, nivel + 1);
    }
}

int Altura(AVL *a)
{
    int Alt_Esq, Alt_Dir;
    if (a == NULL)
        return 0;
    else
    {
        Alt_Esq = Altura(a->esq);
        Alt_Dir = Altura(a->dir);
        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
        else
            return (1 + Alt_Dir);
    }
}

int ehAVL(AVL *a)
{
    int alt_esq, alt_dir;
    if (a != NULL)
    {
        alt_esq = Altura(a->esq);
        alt_dir = Altura(a->dir);
        return ((alt_esq - alt_dir < 2) && (alt_dir - alt_esq < 2) &&
                (ehAVL(a->esq)) && (ehAVL(a->dir)));
    }
    else
        return 1;
}
