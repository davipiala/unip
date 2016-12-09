/****************************************************************************/
/*  CineXperience 2.0 - Projeto Integrado Multidisciplinar - Unip 2016 2Sem */
/*  Autor: Elton dos Santos Data: 02/11/16                                  */
/*  Descricao: DAO - Data Access Object                                     */
/*  Responsável por gerenciar arquivo de formaspagamento.csv criar, remover */
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
#define MASK_FORMAT "%d;%s\n"

//Referencia a variaveis globais
extern int m_qtdFormaPagamentos;
extern TFormaPagamentos m_formaPagamentosLista[50];

/***************************************************************/
/*  Descricao: Funcao responsavel por adicionar formaspagamento*/
/***************************************************************/
int adicionarFormaPagamento(TFormaPagamentos p_formaPagamentos)
{
    char* l_registroLinha;

    //Abrindo arquivo salas.csv
    FILE* l_arquivo = abrirArquivo(FORMAPAGAMENTOS_FILE,MODO_ESCRITA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroFormaPagamento());

        //Formatando a string com dados de formas de pagamento para gravar no arquivo
        sprintf(l_registroLinha, MASK_FORMAT
        , gerarIdSequenciaFormaPagamento()
        , p_formaPagamentos.descricao);

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

/*****************************************************************/
/*  Descricao: Funcao responsavel por editar formas de pagamento */
/*  Obs: necessario de dois arquivos para realizar               */
/*  edicao da linha do arquivo, cria um arquivo                  */
/*  temporario com a linha editada e depois reno-                */
/*  meia para o arquivo original.                                */
/*****************************************************************/
int editarFormaPagamento(TFormaPagamentos p_formaPagamentos)
{
    char* l_registroLinha;

    //Abrindo arquivo salas.csv e criando arquivo temporario
    FILE* l_arquivo = abrirArquivo(FORMAPAGAMENTOS_FILE,MODO_ESCRITA);
    FILE* l_arquivoAux = abrirArquivo(TMP_FILE, "w+");

    if(l_arquivo && l_arquivoAux)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroFormaPagamento());
        while (fgets(l_registroLinha, getSizeRegistroFormaPagamento(), l_arquivo))
        {
            //caso seja a linha correta para editar, carrega os dados para string
            if(p_formaPagamentos.id_forma == atoi(getfield(strdup(l_registroLinha), 1)))
            {
                sprintf(l_registroLinha, MASK_FORMAT
                , p_formaPagamentos.id_forma
                , p_formaPagamentos.descricao);
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
        remove(FORMAPAGAMENTOS_FILE);
        //renomeando arquivo temporario para original
        rename(TMP_FILE, FORMAPAGAMENTOS_FILE);
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;
}

/*****************************************************************/
/*  Descricao: Funcao responsavel por remover formas de pagamento*/
/*  Obs: necessario de dois arquivos para realizar               */
/*  remocao da linha do arquivo.                                 */
/*****************************************************************/
int removerFormaPagamento(int p_formaPagamentoId)
{

    char* l_registroLinha;
    //Abrindo arquivo formaspagamento.csv e criando arquivo temporario
    FILE* l_arquivo = abrirArquivo(FORMAPAGAMENTOS_FILE,MODO_ESCRITA);
    FILE* l_arquivoAux = abrirArquivo(TMP_FILE, "w+");

    if(l_arquivo && l_arquivoAux)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroFormaPagamento());
        while (fgets(l_registroLinha, getSizeRegistroFormaPagamento(), l_arquivo))
        {
            //caso seja a linha correta para remover, carrega os dados para string
            if(p_formaPagamentoId==atoi(getfield(strdup(l_registroLinha), 1)))
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
        remove(FORMAPAGAMENTOS_FILE);
        //renomeando arquivo temporario para original
        rename(TMP_FILE, FORMAPAGAMENTOS_FILE);
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;
}

/*******************************************************************/
/*  Descricao: Funcao responsavel pela carga do                    */
/*  do array de formas de pagamento, todas as formas são carregadas*/
/*  a partir do arquivo formas de pagamento.csv.                   */
/*******************************************************************/
int loadFormaPagamentos()
{
    int l_contador=0;
    char* l_registroLinha;

    //Abrindo arquivo formaspagamento.csv
    FILE* l_arquivo = abrirArquivo(FORMAPAGAMENTOS_FILE,MODO_LEITURA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroFormaPagamento());
        //descartando cabecalho CSV
        descartarHeader(l_arquivo,getSizeRegistroFormaPagamento());
        while (fgets(l_registroLinha, getSizeRegistroFormaPagamento(), l_arquivo))
        {
            //carregando array de structs de formas de pagamento
            m_formaPagamentosLista[l_contador].id_forma = atoi(getfield(strdup(l_registroLinha), 1));
            strcpy(m_formaPagamentosLista[l_contador].descricao, getfield(strdup(l_registroLinha), 2));
            l_contador++;

            //Ĺimpar string de leitura
            memset( l_registroLinha, ESCAPE_ZERO, sizeof(l_registroLinha) );

        }
        //fechando os arquivos
        fecharArquivo(l_arquivo);

        //quantificando a quantidade de registros
        m_qtdFormaPagamentos = l_contador;

    }
    else
    {
        return ERRO;
    }
    return SUCESSO;

}

/*******************************************************************************/
/*  Descricao: Funcao responsavel por recuperar formas de pagamento especifica */
/*  por um determinado ID.                                                     */
/*******************************************************************************/
TFormaPagamentos getFormaPagamentoById(int p_formaPagamentoId)
{
    char* l_registroLinha;
    TFormaPagamentos l_FormaPagamento;

    //Abrindo arquivo formaspagamento.csv
    FILE* l_arquivo = abrirArquivo(FORMAPAGAMENTOS_FILE,MODO_LEITURA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroFormaPagamento());
        //descartando cabecalho CSV
        descartarHeader(l_arquivo,getSizeRegistroFormaPagamento());
        while (fgets(l_registroLinha, getSizeRegistroFormaPagamento(), l_arquivo))
        {
            //carregando array de structs de formas de pagamento
            l_FormaPagamento.id_forma = atoi(getfield(strdup(l_registroLinha), 1));
            strcpy(l_FormaPagamento.descricao, getfield(strdup(l_registroLinha), 2));

            //Ao encontrar o id de formas de pagamento para a pesquisa
            if(p_formaPagamentoId == l_FormaPagamento.id_forma)
            {
                break;
            }
            //Ĺimpar string de leitura
            memset( l_registroLinha, ESCAPE_ZERO, sizeof(l_registroLinha) );
        }
        //fechando os arquivos
        fecharArquivo(l_arquivo);
    }
    else
    {
        return l_FormaPagamento;
    }
    return l_FormaPagamento;

}

/**********************************************/
/*  Descricao: Gerar ID de sequencia de salas */
/**********************************************/
int gerarIdSequenciaFormaPagamento()
{
    int l_sequenciaId=0;
    char* l_registroLinha;
    //Abrindo arquivo formaspagamento.seq
    FILE* l_arquivo = abrirArquivo(FORMAPAGAMENTOS_SEQ ,MODO_ESCRITA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroFormaPagamento());

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
int getSizeRegistroFormaPagamento()
{
     return sizeof(TFilmes)+8;
}
