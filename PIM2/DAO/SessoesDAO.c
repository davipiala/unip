/****************************************************************************/
/*  CineXperience 2.0 - Projeto Integrado Multidisciplinar - Unip 2016 2Sem */
/*  Autor: Davi Piala dosdos Santos Data: 01/11/16                          */
/*  Descricao: DAO - Data Access Object                                     */
/*  Responsável por gerenciar arquivo de sessoes.csv criar, remover         */
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
extern int m_qtdSessoes;
extern TSessoes m_sessoesLista[50];


/********************************************************/
/*  Descricao: Funcao responsavel por adicionar horario */
/********************************************************/
int adicionarSessao(TSessoes p_sessao)
{
    char* l_registroLinha;
    //Abrindo arquivo sessoes.csv
    FILE* l_arquivo = abrirArquivo(SESSOES_FILE,MODO_ESCRITA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroSessao());

        //Formatando a string com dados de horario para gravar no arquivo
        sprintf(l_registroLinha
        , MASK_FORMAT
        , gerarIdSequenciaSessao()
        , p_sessao.hora_inicio);

        //posicionando o ponteiro no final do arquivo fseek
        posicionarFimArquivo(l_arquivo);

        //adicionando linha ao arquivo salas.csv
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

/**************************************************/
/*  Descricao: Funcao para editar horarios        */
/*  Obs: necessario de dois arquivos para realizar*/
/*  edicao da linha do arquivo, cria um arquivo   */
/*  temporario com a linha editada e depois reno- */
/*  meia para o arquivo original.                 */
/**************************************************/
int editarSessao(TSessoes p_sessao)
{

    char* l_registroLinha;

    //Abrindo arquivo sessoes.csv e seu arquivo temporario
    FILE* l_arquivo = abrirArquivo(SESSOES_FILE,MODO_ESCRITA);
    FILE* l_arquivoAux = abrirArquivo(TMP_FILE, "w+");

    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroSessao());

        while (fgets(l_registroLinha, getSizeRegistroSessao(), l_arquivo))
        {
            //caso seja a linha correta para editar, carrega os dados para string
            if(p_sessao.id_sessao == atoi(getfield(strdup(l_registroLinha), 1)))
            {
                sprintf(l_registroLinha, MASK_FORMAT
                , p_sessao.id_sessao
                , p_sessao.hora_inicio);
            }
            //Adicionando linha no arquivo temporario
            adicionarLinhaArquivo(l_registroLinha, l_arquivoAux);
            memset( l_registroLinha, ESCAPE_ZERO, sizeof(l_registroLinha) );

        }
        //fechar os arquivos e liberar memoria
        fecharArquivo(l_arquivo);
        fecharArquivo(l_arquivoAux);

        //removendo arquivo original
        remove(SESSOES_FILE);
        //renomeando arquivo temporario para original
        rename(TMP_FILE, SESSOES_FILE);
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;
}

/*******************************************************/
/*  Descricao: Funcao responsavel por remover horarios */
/*  Obs: necessario de dois arquivos para realizar     */
/*  remocao da linha do arquivo.                       */
/*******************************************************/
int removerSessao(int p_sessaoId)
{

    char* l_registroLinha;

    //Abrindo arquivo sessoes.csv e seu arquivo temporario
    FILE* l_arquivo = abrirArquivo(SESSOES_FILE,MODO_ESCRITA);
    FILE* l_arquivoAux = abrirArquivo(TMP_FILE, "w+");

    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroSessao());
        while (fgets(l_registroLinha,getSizeRegistroSessao(), l_arquivo))
        {

            //caso seja a linha correta para remover, carrega os dados para string
            if(p_sessaoId==atoi(getfield(strdup(l_registroLinha), 1)))
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
        remove(SESSOES_FILE);
        rename(TMP_FILE, SESSOES_FILE);
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;
}

/********************************************************/
/*  Descricao: Funcao responsavel pela carga do         */
/*  do array de horarios, todas as salas são carregadas */
/*  a partir do arquivo sessoes.csv.                   */
/********************************************************/
int loadSessoes()
{
    int l_contador=0;
    char* l_registroLinha;

    //Abrindo arquivo sessoes.csv
    FILE* l_arquivo = abrirArquivo(SESSOES_FILE,MODO_LEITURA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroSessao());

        //descartando cabecalho CSV
        descartarHeader(l_arquivo,getSizeRegistroSessao());

        while (fgets(l_registroLinha, getSizeRegistroSessao(), l_arquivo))
        {
            //carregando array de structs de horarios
            m_sessoesLista[l_contador].id_sessao = atoi(getfield(strdup(l_registroLinha), 1));
            strcpy(m_sessoesLista[l_contador].hora_inicio,getfield(strdup(l_registroLinha), 2));
            l_contador++;

            //Ĺimpar string de leitura
            memset( l_registroLinha, ESCAPE_ZERO, sizeof(l_registroLinha) );
        }
        //fechando os arquivos
        fecharArquivo(l_arquivo);

        //quantificando a quantidade de registros
        m_qtdSessoes = l_contador;

    }
    else
    {
        return ERRO;
    }
    return SUCESSO;

}

/*********************************************************************/
/*  Descricao: Funcao responsavel por recuperar um horario especifico */
/*  por um determinado ID.                                            */
/**********************************************************************/
TSessoes getSessaoById(int p_sessaoId)
{
    char* l_registroLinha;
    TSessoes l_sessao;

    //Abrindo arquivo sessoes.csv
    FILE* l_arquivo = abrirArquivo(SESSOES_FILE,MODO_LEITURA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroSessao());
        //descartando cabecalho CSV
        descartarHeader(l_arquivo,getSizeRegistroSessao());
        while (fgets(l_registroLinha, getSizeRegistroSessao(), l_arquivo))
        {
            //carregando array de structs de horarios
            l_sessao.id_sessao = atoi(getfield(strdup(l_registroLinha), 1));
            strcpy(l_sessao.hora_inicio,getfield(strdup(l_registroLinha), 2));

            //Ao encontrar o id de horario correta para a pesquisa
            if(l_sessao.id_sessao == p_sessaoId)
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
        return l_sessao;
    }
    return l_sessao;

}

/**********************************************************************/
/*  Descricao: Funcao responsavel por recuperar uma lista de horarios */
/*  por um determinado ID de filme.                                   */
/**********************************************************************/
/*
int listHorariosByFilmeId(int p_filmeId)
{
    int l_contador=0;
    char* l_registroLinha;
    struct relacionamento * l_Relacionamentos;

    l_Relacionamentos = loadProgramacaoes(p_filmeId);
    FILE* l_arquivo = abrirArquivo(SESSOES_FILE,MODO_LEITURA);
    if(l_arquivo)
    {
        l_registroLinha = calloc(1,getSizeRegistroSessao());
        descartarHeader(l_arquivo,getSizeRegistroSessao());
        while (fgets(l_registroLinha, getSizeRegistroSessao(), l_arquivo))
        {
            m_sessoesLista[l_contador].id_sessao = atoi(getfield(strdup(l_registroLinha), 1));
            strcpy(m_sessoesLista[l_contador].hora_inicio,getfield(strdup(l_registroLinha), 2));
            strcpy(m_sessoesLista[l_contador].hora_termino,getfield(strdup(l_registroLinha), 3));

            l_contador++;

            //Ĺimpar string de leitura
            memset( l_registroLinha, ESCAPE_ZERO, sizeof(l_registroLinha) );

        }
        m_qtdSessoes = l_contador;
        fecharArquivo(l_arquivo);
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;

}
*/

/*************************************************/
/*  Descricao: Gerar ID de sequencia de horarios */
/*************************************************/
int gerarIdSequenciaSessao()
{
    int l_sequenciaId=0;
    char* l_registroLinha;
    //Abrindo arquivo horarios.seq
    FILE* l_arquivo = abrirArquivo(SESSOES_SEQ ,MODO_ESCRITA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroSessao());
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
int getSizeRegistroSessao()
{
     return sizeof(TFilmes)+8;
}
