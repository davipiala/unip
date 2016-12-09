/****************************************************************************/
/*  CineXperience 2.0 - Projeto Integrado Multidisciplinar - Unip 2016 2Sem */
/*  Autor: Elton dos Santos Data: 08/11/16                                  */
/*  Descricao: DAO - Data Access Object                                     */
/*  Responsável por gerenciar arquivo de transacoes.csv criar, remover      */
/*  editar registros                                                        */
/****************************************************************************/
//Importar bibliotecas padrao C
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

//Importar arquivos header projeto
#include "../utilitarios.h"
#include "../apresentacao.h"
#include "../globais.h"
#include "../constantes.h"

//constantes
#define MASK_FORMAT "%d;%d;%s;%d;%0.2f;%d;%d\n"
#define MASK_FORMAT_BILHETE "%d;%d;%d;%s\n"


//Referencia a variaveis globais
extern int m_qtdTransacoes;
extern TTransacoes m_transacoesLista[50];



/**********************************************************/
/*  Descricao: Funcao responsavel por adicionar transacao */
/**********************************************************/
int adicionarBilhete(TBilhetes* p_bilhete)
{
    char* l_registroLinha;
    p_bilhete->id_bilhete = gerarIdSequenciaBilhete();

    //Abrindo arquivo transacoes.csv
    FILE* l_arquivo = abrirArquivo(BILHETES_FILE,MODO_ESCRITA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroTransacao());

        //Formatando a string com dados de filmes para gravar no arquivo
        sprintf(l_registroLinha
        , MASK_FORMAT_BILHETE
        , p_bilhete->id_bilhete
        , p_bilhete->id_transacao
        , p_bilhete->linha
        , p_bilhete->coluna);

        //posicionando o ponteiro no final do arquivo fseek e adicionando linha ao final do arquivo
        posicionarFimArquivo(l_arquivo);
        adicionarLinhaArquivo(l_registroLinha,l_arquivo);

        //fechar o arquivo e liberar memoria
        fecharArquivo(l_arquivo);
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;
}


/**********************************************************/
/*  Descricao: Funcao responsavel por adicionar transacao */
/**********************************************************/
int adicionarTransacao(TTransacoes* pTransacao)
{
    char* l_registroLinha;

    pTransacao->id_transacao = gerarIdSequenciaTransacao();
    //Abrindo arquivo transacoes.csv
    FILE* l_arquivo = abrirArquivo(TRANSACAO_FILE,MODO_ESCRITA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroTransacao());

        //Formatando a string com dados de filmes para gravar no arquivo
        sprintf(l_registroLinha
        , MASK_FORMAT
        , pTransacao->id_transacao
        , pTransacao->id_programacao
        , pTransacao->data_transacao
        , pTransacao->qtd_ingressos
        , pTransacao->valor_transacao
        , pTransacao->id_forma
        , pTransacao->id_tarifa);

        //posicionando o ponteiro no final do arquivo fseek e adicionando linha ao final do arquivo
        posicionarFimArquivo(l_arquivo);
        adicionarLinhaArquivo(l_registroLinha,l_arquivo);

        //fechar o arquivo e liberar memoria
        fecharArquivo(l_arquivo);
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;
}

/****************************************************************/
/*  Descricao: Funcao responsavel pela carga do                 */
/*  do array de transacoes, todas as transacaoes são carregadas */
/*  a partir do arquivo transacoes.csv.                         */
/****************************************************************/
int loadTransacoes()
{
    int l_contador=0;
    char* l_registroLinha;

    //Abrindo arquivo transacoes.csv
    FILE* l_arquivo = abrirArquivo(TRANSACAO_FILE,MODO_LEITURA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroTransacao());
        //descartando cabecalho CSV
        descartarHeader(l_arquivo,getSizeRegistroTransacao());
        while (fgets(l_registroLinha, getSizeRegistroTransacao(), l_arquivo))
        {
            //carregando array de structs de transacoes
            m_transacoesLista[l_contador].id_transacao = atoi(getfield(strdup(l_registroLinha), 1));
            m_transacoesLista[l_contador].id_programacao = atoi(getfield(strdup(l_registroLinha), 2));
            strcpy(m_transacoesLista[l_contador].data_transacao, getfield(strdup(l_registroLinha), 3));
            m_transacoesLista[l_contador].qtd_ingressos = atoi(getfield(strdup(l_registroLinha), 4));
            m_transacoesLista[l_contador].valor_transacao = atof(getfield(strdup(l_registroLinha), 5));
            m_transacoesLista[l_contador].id_forma = atoi(getfield(strdup(l_registroLinha), 6));
            m_transacoesLista[l_contador].id_tarifa = atoi(getfield(strdup(l_registroLinha), 7));

            memset( l_registroLinha, ESCAPE_ZERO, sizeof(l_registroLinha) );
            l_contador++;

        }
        //quantificando a quantidade de registros
        m_qtdTransacoes = l_contador;

        //fechando os arquivos
        fecharArquivo(l_arquivo);
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;

}

/*************************************************************************/
/*  Descricao: Funcao responsavel por recuperar uma transacao especifica */
/*  por um determinado ID.                                               */
/*************************************************************************/
TTransacoes getTransacaoById(int p_transacaoId)
{
    char* l_registroLinha;
    TTransacoes l_transacao;

    //Abrindo arquivo transacoes.csv
    FILE* l_arquivo = abrirArquivo(TRANSACAO_FILE,MODO_LEITURA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroTransacao());
        //descartando cabecalho CSV
        descartarHeader(l_arquivo);
        while (fgets(l_registroLinha, getSizeRegistroTransacao(), l_arquivo))
        {
            //carregando array de structs de precos
            l_transacao.id_transacao = atoi(getfield(strdup(l_registroLinha), 1));
            l_transacao.id_programacao = atoi(getfield(strdup(l_registroLinha), 2));
            strcpy(l_transacao.data_transacao, getfield(strdup(l_registroLinha), 3));
            l_transacao.qtd_ingressos = atoi(getfield(strdup(l_registroLinha), 4));
            l_transacao.valor_transacao = atof(getfield(strdup(l_registroLinha), 5));
            l_transacao.id_forma = atoi(getfield(strdup(l_registroLinha), 6));
            l_transacao.id_tarifa = atoi(getfield(strdup(l_registroLinha), 7));
            //Ao encontrar o id de filmes para a pesquisa
            if(p_transacaoId == l_transacao.id_transacao)
            {
                break;
            }
        }
        fecharArquivo(l_arquivo);
    }
    else
    {
        return l_transacao;
    }
    return l_transacao;

}

/*************************************************************************/
/*  Descricao: Funcao responsavel por recuperar uma transacao especifica */
/*  por um determinado ID.                                               */
/*************************************************************************/
float getValorTransacaoByDate(char* p_data)
{
    char* l_registroLinha;
    float l_valorTransacaoTotal = 0.0f;
    TTransacoes l_transacao;

    //Abrindo arquivo transacoes.csv
    FILE* l_arquivo = abrirArquivo(TRANSACAO_FILE,MODO_LEITURA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroTransacao());
        //descartando cabecalho CSV
        descartarHeader(l_arquivo);
        while (fgets(l_registroLinha, getSizeRegistroTransacao(), l_arquivo))
        {
            //Ao encontrar o id de filmes para a pesquisa
            strcpy(l_transacao.data_transacao,getfield(strdup(l_registroLinha), 3));
            if(strcmp(p_data,l_transacao.data_transacao)==0)
            {
               l_valorTransacaoTotal = l_valorTransacaoTotal + atof(getfield(strdup(l_registroLinha), 5));
            }
        }
        fecharArquivo(l_arquivo);
    }
    else
    {
        return l_valorTransacaoTotal;
    }
    return l_valorTransacaoTotal;

}


/*************************************************************************/
/*  Descricao: Funcao responsavel por recuperar uma transacao especifica */
/*  por um determinado ID.                                               */
/*************************************************************************/
int getQtdTransacaoByDate(char* p_data)
{
    char* l_registroLinha;
    int l_qtdTransacoes = 0;
    TTransacoes l_transacao;

    //Abrindo arquivo transacoes.csv
    FILE* l_arquivo = abrirArquivo(TRANSACAO_FILE,MODO_LEITURA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroTransacao());
        //descartando cabecalho CSV
        descartarHeader(l_arquivo);
        while (fgets(l_registroLinha, getSizeRegistroTransacao(), l_arquivo))
        {
            strcpy(l_transacao.data_transacao,getfield(strdup(l_registroLinha), 3));
            if(strcmp(p_data,l_transacao.data_transacao)==0)
            {
                l_qtdTransacoes++;
            }
        }
        fecharArquivo(l_arquivo);
    }
    else
    {
        return l_qtdTransacoes;
    }
    return l_qtdTransacoes;

}



/**************************************************/
/*  Descricao: Gerar ID de sequencia de transacao */
/**************************************************/
int gerarIdSequenciaTransacao()
{

    int l_sequenciaId=0;
    char* l_registroLinha;

    //Abrindo arquivo precos.seq
    FILE* l_arquivo = abrirArquivo(TRANSACAO_SEQ ,MODO_ESCRITA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroTransacao());

        //recuperando o ID de sequencia e formatando a string
        fscanf(l_arquivo, "%d", &l_sequenciaId);
        l_sequenciaId++;
        sprintf(l_registroLinha, "%d", l_sequenciaId);

        //posicionando no inicio do arquivo para sobrescrever
        posicionarInicioArquivo(l_arquivo);
        adicionarLinhaArquivo(l_registroLinha, l_arquivo);
        fecharArquivo(l_arquivo);
    }
    else
    {
        return ERRO;
    }
    return l_sequenciaId;
}

/********************************************************/
/*  Descricao: Funcao responsavel por remover bilhetes  */
/*  Obs: necessario de dois arquivos para realizar      */
/*  remocao da linha do arquivo.                        */
/********************************************************/
int removerBilhete(int p_idBilhete)
{

    char* l_registroLinha;
    //Abrindo arquivo formaspagamento.csv e criando arquivo temporario
    FILE* l_arquivo = abrirArquivo(BILHETES_FILE,MODO_ESCRITA);
    FILE* l_arquivoAux = abrirArquivo(TMP_FILE, "w+");

    if(l_arquivo && l_arquivoAux)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroFormaPagamento());
        while (fgets(l_registroLinha, getSizeRegistroFormaPagamento(), l_arquivo))
        {
            //caso seja a linha correta para remover, carrega os dados para string
            if(p_idBilhete==atoi(getfield(strdup(l_registroLinha), 1)))
            {
                continue;
            }
            //Adicionando linha no arquivo temporario
            adicionarLinhaArquivo(l_registroLinha, l_arquivoAux);
            //Ĺimpar string de leitura
            memset( l_registroLinha, ESCAPE_ZERO, sizeof(l_registroLinha) );
        }
        //fechando os arquivos
        fecharArquivo(l_arquivo);
        fecharArquivo(l_arquivoAux);
        //removendo arquivo original
        remove(BILHETES_FILE);
        //renomeando arquivo temporario para original
        rename(TMP_FILE, BILHETES_FILE);
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;
}

/**************************************************/
/*  Descricao: Gerar ID de sequencia de bilhete */
/**************************************************/
int gerarIdSequenciaBilhete()
{
    int l_sequenciaId=0;
    char* l_registroLinha;
    //alocando espaço na string que corresponde a linha do arquivo
    FILE* l_arquivo = abrirArquivo(BILHETES_SEQ ,MODO_ESCRITA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroTransacao());

        //recuperando o ID de sequencia e formatando a string
        fscanf(l_arquivo, "%d", &l_sequenciaId);
        l_sequenciaId++;
        sprintf(l_registroLinha, "%d", l_sequenciaId);

        //posicionando no inicio do arquivo para sobrescrever
        posicionarInicioArquivo(l_arquivo);
        adicionarLinhaArquivo(l_registroLinha, l_arquivo);
        fecharArquivo(l_arquivo);
    }
    else
    {
        return ERRO;
    }
    return l_sequenciaId;
}

/*********************************************************/
/*  Descricao: Recuperar o tamanho da estrutura em bytes */
/*********************************************************/
int getSizeRegistroTransacao()
{
     return sizeof(TFilmes)+8;
}
