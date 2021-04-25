#include "ABP.h"
#include "ABP.c"

#define MAX_LIN 300 // tamanho máximo de caracteres de um tweet + números de id

void converte_minuscula(char *s)
{
    int i;
    for (i = 0; i < strlen(s); i++)
        s[i] = tolower(s[i]);
}

int main(int argc, char *argv[])
{
    FILE *entrada;
    FILE *consulta;
    FILE *saida;
    char *palavra, linha[300], *id;                                      // linhas a serem lidas do arquivo
    char separador[] = {" 0123456789,.&*%\?!;/-'@\"$#=~><()][}{:\n\t_"}; //caracteres separadores para as palavras
    int id_num;

    int nodos = 0, comp_index = 0, comp_cons = 0;
    ABP *arvore = NULL;
    ABP *ptNodo;
    Ocorrencia *ocorrencia;

    setlocale(LC_ALL, "pt_BR_utf8"); //para imprimir corretamente na tela os caracteres acentuados

    if (argc != 4)
    { //testa se o numero de parametros esperado está correto (deve ser 3): nome do programa (argv[0]), nome do arq de entrada(argv[1]), nome do arq de saida(argv[2])
        printf("Número incorreto de parâmetros.\n Para chamar o programa digite: %s <arq_entrada> <arq_consulta> <arq_saida>\n", argv[0]);
        return 1;
    }

    if ((entrada = fopen(argv[1], "r")) == NULL)
    { // testa se consegue abrir o arquivo de entrada
        printf("erro ao abrir arquivo %s \n", argv[1]);
        return 1;
    }

    if ((consulta = fopen(argv[2], "r")) == NULL)
    { // testa se consegue abrir o arquivo de entrada
        printf("erro ao abrir arquivo %s \n", argv[2]);
        return 1;
    }

    if ((saida = fopen(argv[3], "w")) == NULL) // testa se consegue criar o arquivo de saída
    {
        printf("erro ao criar arquivo %s \n", argv[3]);
        return 1;
    }

    while (fgets(linha, MAX_LIN, entrada))
    {                            //lê cada linha do arquivo texto
        id = strtok(linha, ";"); //pega o id do tweet
        id_num = atoi(id);       //converte o id para numérico (vai ser necessário para inserir o id tweet na lista de ocorrências)

        palavra = strtok(NULL, separador); //pega a 1a palavra do tweet

        while (palavra != NULL)
        {                                //enquanto encontrar palavras no tweet
            converte_minuscula(palavra); //converte a palavra para minúsculo
            arvore = InsereABP(arvore, palavra, &nodos, &comp_index, id_num);
            palavra = strtok(NULL, separador); //pega a próxima palavra do tweet
        }
    }

    while (fgets(linha, 20, consulta))
    {
        linha[strlen(linha) - 1] = '\0';

        ptNodo = ConsultaABP(arvore, linha, &comp_cons);

        if (ptNodo != NULL)
        {
            fprintf(saida, "consulta: %s Palavra encontrada nos tweets ", linha);
            ocorrencia = ptNodo->ocorrencia;
            do
            {
                fprintf(saida, "%d, ", ocorrencia->id);
                ocorrencia = ocorrencia->prox;
            } while (ocorrencia != NULL);
            fprintf(saida, "\n");
            // TODO: destroi ptNodo
        }
        else
        {
            fprintf(saida, "consulta: %s Palavra não encontrada\n", linha);
        }
    }

    fprintf(saida, "\n********** Estatísticas da Indexação **************\n");
    fprintf(saida, "nodos: %d\n", nodos);
    fprintf(saida, "comparações: %d\n", comp_index);
    fprintf(saida, "altura da árvore: %d\n", Altura(arvore));

    fprintf(saida, "\n********** Estatísticas das Consultas **************\n");
    fprintf(saida, "comparações = %d\n", comp_cons);

    fclose(entrada); //fecha os arquivos
    fclose(consulta);
    fclose(saida);

    return 0; //retorna 0 para indicar que foi bem sucedido
}
