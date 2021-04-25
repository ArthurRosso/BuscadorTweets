#include "ABP.h"
#include "ocorrencias.h"

ABP *InsereABP(ABP *a, char *x, int *nodos, int *comp, int id)
{
    if (a == NULL)
    {
        a = (ABP *)malloc(sizeof(ABP));
        strcpy(a->palavra, x);
        a->esq = NULL;
        a->dir = NULL;

        a->ocorrencia = malloc(sizeof(Ocorrencia));
        a->ocorrencia->id = id;
        a->ocorrencia->prox = NULL;

        (*nodos)++;
        (*comp)++;
    }
    else if (strcmp(x, a->palavra) < 0)
    { // x < a->palavra
        (*comp) += 2;
        a->esq = InsereABP(a->esq, x, nodos, comp, id);
    }
    else if (strcmp(x, a->palavra) > 0)
    { // x > a->palavra
        (*comp) += 3;
        a->dir = InsereABP(a->dir, x, nodos, comp, id);
    }
    else
    {
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

ABP *ConsultaABP(ABP *a, char *chave, int *comp)
{
    while (a != NULL)
    {
        (*comp)++;
        if (strcmp(a->palavra, chave) == 0)
        {
            return a;
        }
        else
        {
            if (strcmp(a->palavra, chave) > 0)
            {
                a = a->esq;
            }
            else
            {
                a = a->dir;
            }
        }
    }
    return NULL;
}

void ImprimeArvore(ABP *a, int nivel)
{
    int i;
    if (a != NULL)
    {
        for (i = 0; i <= nivel; i++)
        {
            printf("=");
        }
        printf("%s\n", a->palavra);
        ImprimeArvore(a->esq, nivel + 1);
        ImprimeArvore(a->dir, nivel + 1);
    }
}

int Altura(ABP *a)
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
