/****************************************************************************/
/*  CineXperience 2.0 - Projeto Integrado Multidisciplinar - Unip 2016 2Sem */
/*  Autor: Elton dos Santos Data: 08/11/16                                  */
/*  Descricao: DAO - Data Access Object                                     */
/*  Responsável por gerenciar arquivo de precos.csv criar, remover          */
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
#include "../globais.h"
#include "../constantes.h"

//constantes
#define MASK_FORMAT "%d;%s;%0.2f\n"

//Referencia a variaveis globais
extern int m_qtdTarifas;
extern TTarifas m_TarifasLista[50];

/*******************************************************/
/*  Descricao: Funcao responsavel por adicionar precos */
/*******************************************************/
int adicionarPreco(TTarifas p_tarifa)
{
    char* l_registroLinha;

    //Abrindo arquivo filmes.csv
    FILE* l_arquivo = abrirArquivo(TARIFAS_FILE,MODO_ESCRITA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroTarifa());

        //Formatando a string com dados de filmes para gravar no arquivo
        sprintf(l_registroLinha, MASK_FORMAT
        , gerarIdSequenciaTarifa()
        , p_tarifa.descricao
        , p_tarifa.valor);

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

/*****************************************************/
/*  Descricao: Funcao responsavel por editar precos  */
/*  Obs: necessario de dois arquivos para realizar   */
/*  edicao da linha do arquivo, cria um arquivo      */
/*  temporario com a linha editada e depois reno-    */
/*  meia para o arquivo original.                    */
/*****************************************************/
int editarTarifa(TTarifas p_tarifa)
{
    char* l_registroLinha;
    //Abrindo arquivo precos.csv e criando arquivo temporario
    FILE* l_arquivo = abrirArquivo(TARIFAS_FILE,MODO_ESCRITA);
    FILE* l_arquivoAux = fopen(TMP_FILE, "w+");

    if(l_arquivo && l_arquivoAux)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroTarifa());
        while (fgets(l_registroLinha, getSizeRegistroTarifa(), l_arquivo))
        {
            //caso seja a linha correta para editar, carrega os dados para string
            if(p_tarifa.id_tarifa == atoi(getfield(strdup(l_registroLinha), 1)))
            {
                sprintf(l_registroLinha, MASK_FORMAT
                , p_tarifa.id_tarifa
                , p_tarifa.descricao
                , p_tarifa.valor);
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
        remove(TARIFAS_FILE);
        //renomeando arquivo temporario para original
        rename(TMP_FILE, TARIFAS_FILE);
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;
}

/*****************************************************/
/*  Descricao: Funcao responsavel por remover precos */
/*  Obs: necessario de dois arquivos para realizar   */
/*  remocao da linha do arquivo.                     */
/*****************************************************/
int removerTarifa(int p_tarifaId)
{

    char* l_registroLinha;

    //Abrindo arquivo filmes.csv e criando arquivo temporario
    FILE* l_arquivo = abrirArquivo(TARIFAS_FILE,MODO_ESCRITA);
    FILE* l_arquivoAux = abrirArquivo(TMP_FILE, "w+");

    if(l_arquivo && l_arquivoAux)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroTarifa());
        while (fgets(l_registroLinha, getSizeRegistroTarifa(), l_arquivo))
        {
                //caso seja a linha correta para remover, carrega os dados para string
            if(p_tarifaId==atoi(getfield(strdup(l_registroLinha), 1)))
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
        remove(TARIFAS_FILE);
        //renomeando arquivo temporario para original
        rename(TMP_FILE, TARIFAS_FILE);
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;
}

/************************************************************/
/*  Descricao: Funcao responsavel pela carga do             */
/*  do array de programacao, todas as precos são carregados */
/*  a partir do arquivo precos.csv.                         */
/************************************************************/
int loadTarifas()
{
    int l_contador=0;
    char* l_registroLinha;

    //Abrindo arquivo precos.csv
    FILE* l_arquivo = abrirArquivo(TARIFAS_FILE,MODO_LEITURA);
    if(l_arquivo)
    {
        l_registroLinha = calloc(1,getSizeRegistroProgramacoes());
        //descartando cabecalho CSV
        descartarHeader(l_arquivo,getSizeRegistroTarifa());
        while (fgets(l_registroLinha, getSizeRegistroTarifa(), l_arquivo))
        {
           m_TarifasLista[l_contador].id_tarifa = atoi(getfield(strdup(l_registroLinha), 1));
            strcpy(m_TarifasLista[l_contador].descricao, getfield(strdup(l_registroLinha), 2));
            m_TarifasLista[l_contador].valor = atof(getfield(strdup(l_registroLinha), 3));
            l_contador++;

        }
        //quantificando a quantidade de registros
        m_qtdTarifas = l_contador;

        //fechando os arquivos
        fecharArquivo(l_arquivo);
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;

}

/********************************************************************/
/*  Descricao: Funcao responsavel por recuperar um preco especifico */
/*  por um determinado ID.                                          */
/********************************************************************/
TTarifas getTarifaById(int p_tarifaId)
{

    char* l_registroLinha;
    TTarifas l_tarifa;

    //Abrindo arquivo precos.csv
    FILE* l_arquivo = abrirArquivo(TARIFAS_FILE,MODO_LEITURA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroTarifa());
        //descartando cabecalho CSV
        descartarHeader(l_arquivo,getSizeRegistroTarifa());
        while (fgets(l_registroLinha, getSizeRegistroTarifa(), l_arquivo))
        {
            //carregando array de structs de precos
            l_tarifa.id_tarifa = atoi(getfield(strdup(l_registroLinha), 1));
            strcpy(l_tarifa.descricao, getfield(strdup(l_registroLinha), 2));
            l_tarifa.valor = atof(getfield(strdup(l_registroLinha), 3));
            //Ao encontrar o id de filmes para a pesquisa
            if(p_tarifaId == l_tarifa.id_tarifa)
            {
                break;
            }
            memset( l_registroLinha, ESCAPE_ZERO, sizeof(l_registroLinha) );
        }
        fecharArquivo(l_arquivo);
    }
    else
    {
        return l_tarifa;
    }
    return l_tarifa;

}

/**********************************************/
/*  Descricao: Gerar ID de sequencia de preco */
/**********************************************/
int gerarIdSequenciaTarifa()
{

    int l_sequenciaId=0;
    char* l_registroLinha;

    //Abrindo arquivo precos.seq
    FILE* l_arquivo = abrirArquivo(TARIFAS_SEQ ,MODO_ESCRITA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroTarifa());

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
int getSizeRegistroTarifa()
{
     return sizeof(TFilmes)+8;
}



