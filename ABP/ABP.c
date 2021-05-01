#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#include "ABP.h"
#include "ocorrencias.h"

/*
 * Insere um novo nodo em uma árvore ABP
 *
 * @param *a        árvore ABP
 * @param *x        novo nodo
 * @param *nodos    o número de nodos a árvore tem
 * @param *comp     o número de comparações que já foram feitas na inserção
 * @param id        o id do tweet que estamos
 * @return          árvore ABP depois da inserção
 */ 
ABP *InsereABP(ABP *a, char *x, int *nodos, int *comp, int id)
{
    if (a == NULL) // se estamos em uma árvore nula ou em uma folha então inicializa o nodo
    {
        a = InicializaABP(x); // inicializa o nodo

        a->ocorrencia = InicializaOcorrencia(id); // inicializa a ocorência do id no nodo

        (*nodos)++; // adiciona um nodo
        (*comp)++; // como entrou no primeiro if, contabiliza uma comparação
    }
    else if (strcmp(x, a->palavra) < 0) // se x vem antes do nodo atual na ordem lexicográfica
    {
        (*comp) += 2; // como entrou no segundo if, contabiliza duas comparações
        a->esq = InsereABP(a->esq, x, nodos, comp, id); // insere o nodo na sub-árvore esquerda
    }
    else if (strcmp(x, a->palavra) > 0) // se x vem depois do nodo atual na ordem lexicográfica
    {
        (*comp) += 3; // como entrou no terceiro if, contabiliza três comparações
        a->dir = InsereABP(a->dir, x, nodos, comp, id); // insere o nodo na sub-árvore direita
    }
    else // então as palavras são iguais
    {
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
 * Inicializa um novo nodo em uma árvore ABP
 *
 * @param *x        nova palavra para adicionar no novo nodo
 * @return          nodo inicializado
 */ 
ABP *InicializaABP(char *x)
{
    ABP *a = malloc(sizeof(ABP)); // aloca o ponteiro da árvore
    strcpy(a->palavra, x); // passa o conteúdo do novo nodo para o novo nodo
    a->esq = NULL; // inicializa a sub-árvore esquerda
    a->dir = NULL; // inicializa a sub-árvore direita

    return a; // retorna o novo nodo
}

/*
 * Consulta uma palavra em uma árvore ABP
 *
 * @param *a        árvore ABP
 * @param *chave    palavra que será consultada
 * @param *comp     o número de comparações que já foram feitas na consulta
 * @return          o nodo encontrado ou nulo
 */ 
ABP *ConsultaABP(ABP *a, char *chave, int *comp)
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
 * Imprime uma árvore ABP colocando '=' para identificar o seu nível 
 *
 * @param *a        árvore ABP
 * @param nivel     o nivel do nodo que será printado
 */ 
void ImprimeArvore(ABP *a, int nivel)
{
    int i;
    if (a != NULL) // se a árvore for diferente de nulo
    {
        for (i = 0; i <= nivel; i++) // imprime um '=' para cada nível
        {
            printf("=");
        }
        printf("%s\n", a->palavra); // imprime a palavra
        ImprimeArvore(a->esq, nivel + 1); // imprime a sub-árvore esquerda
        ImprimeArvore(a->dir, nivel + 1); // imprime a sub-árvore direita
    }
}

/*
 * Calcula a altura de uma árvore ABP
 *
 * @param *a        árvore ABP
 * @return          altura da árvore
 */ 
int Altura(ABP *a)
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
