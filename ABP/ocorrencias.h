#ifndef OCORRENCIAS_H_INCLUDED
#define OCORRENCIAS_H_INCLUDED

struct TADOcorrencia {
    int id;
    struct TADOcorrencia *prox;
};
typedef struct TADOcorrencia Ocorrencia;

Ocorrencia *InicializaOcorrencia(int id);

#endif // OCORRENCIAS_H_INCLUDED
