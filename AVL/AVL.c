#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#include "AVL.h"
#include "ocorrencias.h"

/*
 * Insere um novo nodo em uma árvore AVL
 *
 * @param *a        árvore AVL
 * @param *x        novo nodo
 * @param *ok       flag que aponta se precisa fazer mudanças de fator ou rotações
 * @param *nodos    o número de nodos a árvore tem
 * @param *comp     o número de comparações que já foram feitas na inserção
 * @param *rot      o número de rotações que já foram feitas na inserção
 * @param id        o id do tweet que estamos
 * @return          árvore AVL depois da inserção
 */ 
AVL *InsereAVL(AVL *a, char *x, int *ok, int *nodos, int *comp, int *rot, int id)
{
    if (a == NULL) // se estamos em uma árvore nula ou em uma folha então inicializa o nodo
    {
        a = InicializaAVL(x); // inicializa o nodo

        a->ocorrencia = InicializaOcorrencia(id); // inicializa a ocorência do id no nodo

        *ok = 1; // precisam ser feitas mudanças de fator ou rotações
        (*nodos)++; // adiciona um nodo
        (*comp)++; // como entrou no primeiro if, contabiliza uma comparação
    }
    else if (strcmp(x, a->palavra) < 0) // se x vem antes do nodo atual na ordem lexicográfica
    {
        (*comp) += 2; // como entrou no segundo if, contabiliza duas comparações
        a->esq = InsereAVL(a->esq, x, ok, nodos, comp, rot, id); // insere o nodo na sub-árvore esquerda
        if (*ok) // se precisam ser feitas mudanças de fator ou rotações
        {
            switch (a->fator)
            {
            case -1: // se o fator é -1 passa a ser 0 e não precisam ser feitas mais mudanças de fator ou rotações
                a->fator = 0; 
                *ok = 0;
                break;
            case 0: // se o fator é 0 passa a ser 1
                a->fator = 1;
                break;
            case 1: // se o fator é 1 então é feita uma rotação simples ou dupla à direita
                a = Caso1(a, ok, rot);
                break;
            }
        }
    }
    else if (strcmp(x, a->palavra) > 0) // se x vem depois do nodo atual na ordem lexicográfica
    {
        (*comp) += 3; // como entrou no terceiro if, contabiliza três comparações
        a->dir = InsereAVL(a->dir, x, ok, nodos, comp, rot, id); // insere o nodo na sub-árvore direita
        if (*ok) // se precisam ser feitas mudanças de fator ou rotações
        {
            switch (a->fator)
            {
            case 1: // se o fator é 1 passa a ser 0 e não precisam ser feitas mais mudanças de fator ou rotações
                a->fator = 0;
                *ok = 0;
                break;
            case 0: // se o fator é 0 passa a ser -1
                a->fator = -1;
                break;
            case -1: // se o fator é -1 então é feita uma rotação simples ou dupla à esquerda
                a = Caso2(a, ok, rot);
                break;
            }
        }
    }
    else // então as palavras são iguais
    {
        *ok=0; // não precisam ser feitas mudanças de fator ou rotações
        (*comp) += 3; // como entrou no else, contabiliza três comparações
        Ocorrencia *oco = a->ocorrencia; // cria a variavel oco pra não precisar usar a->ocorrencia toda vez
        while (oco->prox != NULL) // enquanto não estamos na próxima ocorrência
        {
            if (oco->id == id) // checamos se não passamos por um id igual ao que estamos
            {
                return a; // se sim então retornamos para não repetir
            }
            oco = oco->prox; // passamos para a próxima ocorrência
        }
        if (oco->id == id) // checamos se não passamos por um id igual ao que estamos
        {
            return a; // se sim então retornamos para não repetir
        }
        oco->prox = InicializaOcorrencia(id); // inicializa a ocorência do id no nodo
    }
    return a; // retorna a árvore
}

/*
 * Inicializa um novo nodo em uma árvore AVL
 *
 * @param *x        nova palavra para adicionar no novo nodo
 * @return          nodo inicializado
 */ 
AVL *InicializaAVL(char *x) 
{
    AVL *a = malloc(sizeof(AVL)); // aloca o ponteiro da árvore
    strcpy(a->palavra, x); // passa o conteúdo do novo nodo para o novo nodo
    a->esq = NULL; // inicializa a sub-árvore esquerda
    a->dir = NULL; // inicializa a sub-árvore direita
    a->fator = 0; // a diferença entre as sub-árvores é 0

    return a; // retorna o novo nodo
}

/*
 * Consulta uma palavra em uma árvore AVL
 *
 * @param *a        árvore AVL
 * @param *chave    palavra que será consultada
 * @param *comp     o número de comparações que já foram feitas na consulta
 * @return          o nodo encontrado ou nulo
 */ 
AVL *ConsultaAVL(AVL *a, char *chave, int *comp)
{
    while (a != NULL) // enquanto a árvore não está nula
    {
        if (strcmp(chave, a->palavra) < 0) // se a palavra vem antes do nodo atual na ordem lexicográfica
        {
            (*comp)++; // como entrou no primeiro if, contabiliza uma comparação
            a = a->esq; // procuramos na sub-árvore esquerda
        }
        else if (strcmp(chave, a->palavra) > 0) // se a palvra vem depois do nodo atual na ordem lexicográfica
        {
            (*comp)+=2; // como entrou no segundo if, contabiliza duas comparações
            a = a->dir; // procuramos na sub-árvore direita
        }
        else // se achou a palavra
        {
            (*comp)+=2; // como entrou no else, contabiliza duas comparações
            return a; // retorna o nodo da palavra
        }
    }
    return NULL; // se não achou retorna nulo
}

/*
 * Decide se faz uma rotação simples ou dupla à direita
 *
 * @param *a        árvore AVL
 * @param *ok       flag que aponta se precisa fazer mudanças de fator ou rotações
 * @param *rot      o número de rotações que já foram feitas na inserção
 * @return          árvore AVL depois da rotação
 */ 
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

/*
 * Decide se faz uma rotação simples ou dupla à esquerda
 *
 * @param *a        árvore AVL
 * @param *ok       flag que aponta se precisa fazer mudanças de fator ou rotações
 * @param *rot      o número de rotações que já foram feitas na inserção
 * @return          árvore AVL depois da rotação
 */ 
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

/*
 * Faz uma rotação simples à direita
 *
 * @param *p        árvore AVL
 * @return          árvore AVL depois da rotação
 */ 
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

/*
 * Faz uma rotação simples à esquerda
 *
 * @param *p        árvore AVL
 * @return          árvore AVL depois da rotação
 */ 
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

/*
 * Faz uma rotação dupla à direita
 *
 * @param *p        árvore AVL
 * @return          árvore AVL depois da rotação
 */ 
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

/*
 * Faz uma rotação dupla à esquerda
 *
 * @param *p        árvore AVL
 * @return          árvore AVL depois da rotação
 */ 
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

/*
 * Imprime uma árvore AVL colocando '=' para identificar o seu nível 
 *
 * @param *a        árvore AVL
 * @param nivel     o nivel do nodo que será printado
 */ 
void ImprimeArvore(AVL *a, int nivel)
{
    int i;
    if (a != NULL) // se a árvore for diferente de nulo
    {
        for (i = 0; i <= nivel; i++) // imprime um '=' para cada nível
        {
            printf("=");
        }
        printf("%s ", a->palavra); // imprime a palavra
        printf("fator %d\n", a->fator); // imprime o fator
        ImprimeArvore(a->esq, nivel + 1); // imprime a sub-árvore esquerda
        ImprimeArvore(a->dir, nivel + 1); // imprime a sub-árvore direita
    }
}

/*
 * Calcula a altura de uma árvore AVL
 *
 * @param *a        árvore AVL
 * @return          altura da árvore
 */ 
int Altura(AVL *a)
{
    int Alt_Esq, Alt_Dir;
    if (a == NULL) // se a árvore for nula retorna 0
        return 0;
    else // se não retorna a altura da maior sub-árvore
    {
        Alt_Esq = Altura(a->esq);
        Alt_Dir = Altura(a->dir);
        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
        else
            return (1 + Alt_Dir);
    }
}

/*
 * Confere se a árvore é AVL
 *
 * @param *a        árvore AVL
 * @return          1 se a árvore é AVL ou 0 se não for
 */ 
int EhAVL(AVL *a)
{
    int alt_esq, alt_dir;
    if (a != NULL)
    {
        alt_esq = Altura(a->esq);
        alt_dir = Altura(a->dir);
        return ((alt_esq - alt_dir < 2) && (alt_dir - alt_esq < 2) &&
                (EhAVL(a->esq)) && (EhAVL(a->dir))); // se as diferenças de altura de sub-árvores for menor que 2 e elas forem avl também então é avl
    }
    else // se a árvore for nula então é AVL
        return 1;
}
