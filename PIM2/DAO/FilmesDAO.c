/****************************************************************************/
/*  CineXperience 2.0 - Projeto Integrado Multidisciplinar - Unip 2016 2Sem */
/*  Autor: Elton dos Santos Data: 08/11/16                                  */
/*  Descricao: DAO - Data Access Object                                     */
/*  Responsável por gerenciar arquivo de filmes.csv criar, remover          */
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
#define MASK_FORMAT "%d;%s;%s;%s;%s;%s;%d\n"

//Referencia a variaveis globais
extern int m_qtdFilmes;
TFilmes m_filmesLista[50];

/*******************************************************/
/*  Descricao: Funcao responsavel por adicionar filmes */
/*******************************************************/
int adicionarFilme(TFilmes p_filme)
{
    int l_idFilme = gerarIdSequenciaFilme();
    char* l_registroLinha;

    //Abrindo arquivo programacoes.csv
    FILE* l_arquivo = abrirArquivo(FILMES_FILE,MODO_ESCRITA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroFilme());

        //Formatando a string com dados de prgramacao para gravar no arquivo
        sprintf(l_registroLinha
        , MASK_FORMAT
        ,l_idFilme
        ,p_filme.nome
        ,p_filme.descricao
        ,systemDate()
        ,p_filme.diretor
        ,p_filme.sinopse
        ,p_filme.classificacao);

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
    return l_idFilme;
}

/*****************************************************/
/*  Descricao: Funcao responsavel por editar filmes  */
/*  Obs: necessario de dois arquivos para realizar   */
/*  edicao da linha do arquivo, cria um arquivo      */
/*  temporario com a linha editada e depois reno-    */
/*  meia para o arquivo original.                    */
/*****************************************************/
int editarFilme(TFilmes p_filme)
{

    char* l_registroLinha;

    //Abrindo arquivo filmes.csv e criando arquivo temporario
    FILE* l_arquivo = abrirArquivo(FILMES_FILE,MODO_ESCRITA);
    FILE* l_arquivoAux = abrirArquivo(TMP_FILE, "w+");

    if(l_arquivo && l_arquivoAux)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroFilme());
        while (fgets(l_registroLinha, getSizeRegistroFilme(), l_arquivo))
        {
            //caso seja a linha correta para editar, carrega os dados para string
            if(p_filme.id_filme==atoi(getfield(strdup(l_registroLinha), 1)))
            {
                sprintf(l_registroLinha, MASK_FORMAT
                ,p_filme.id_filme
                ,p_filme.nome
                ,p_filme.descricao
                ,systemDate()
                ,p_filme.diretor
                ,p_filme.sinopse
                ,p_filme.classificacao);
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
        remove(FILMES_FILE);
        //renomeando arquivo temporario para original
        rename(TMP_FILE, FILMES_FILE);
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;
}

/*****************************************************/
/*  Descricao: Funcao responsavel por remover filmes */
/*  Obs: necessario de dois arquivos para realizar   */
/*  remocao da linha do arquivo.                     */
/*****************************************************/
int removerFilme(int p_filmeId)
 {
    char* l_registroLinha;

    //Abrindo arquivo filmes.csv e criando arquivo temporario
    FILE* l_arquivo = abrirArquivo(FILMES_FILE,MODO_ESCRITA);
    FILE* l_arquivoAux = abrirArquivo(TMP_FILE, "w+");

    if(l_arquivo && l_arquivoAux)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroFilme());
        while (fgets(l_registroLinha, getSizeRegistroFilme(), l_arquivo))
        {
            //caso seja a linha correta para remover, carrega os dados para string
            if(p_filmeId==atoi(getfield(strdup(l_registroLinha), 1)))
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
        remove(FILMES_FILE);
        //renomeando arquivo temporario para original
        rename(TMP_FILE, FILMES_FILE);
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;
}

/************************************************************/
/*  Descricao: Funcao responsavel pela carga do             */
/*  do array de programacao, todas as filmes são carregados */
/*  a partir do arquivo filmes.csv.                         */
/************************************************************/
int loadFilmes()
{
    int l_contador=0;
    char* l_registroLinha;

    //Abrindo arquivo filmes.csv
    FILE* l_arquivo = abrirArquivo(FILMES_FILE,MODO_LEITURA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroFilme());
        //descartando cabecalho CSV
        descartarHeader(l_arquivo,getSizeRegistroFilme());
        while (fgets(l_registroLinha, getSizeRegistroFilme(), l_arquivo))
        {
            //carregando array de structs de filmes
            m_filmesLista[l_contador].id_filme = atoi(getfield(strdup(l_registroLinha), 1));
            strcpy(m_filmesLista[l_contador].nome,getfield(strdup(l_registroLinha), 2));
            strcpy(m_filmesLista[l_contador].descricao,getfield(strdup(l_registroLinha), 3));
            strcpy(m_filmesLista[l_contador].data_cadastro,getfield(strdup(l_registroLinha), 4));
            strcpy(m_filmesLista[l_contador].diretor,getfield(strdup(l_registroLinha), 5));
            strcpy(m_filmesLista[l_contador].sinopse,getfield(strdup(l_registroLinha), 6));
            m_filmesLista[l_contador].classificacao = atoi(getfield(strdup(l_registroLinha), 7));
            l_contador++;

        }
        //fechando os arquivos
        fecharArquivo(l_arquivo);

        //quantificando a quantidade de registros
        m_qtdFilmes = l_contador;
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;
}

/********************************************************************/
/*  Descricao: Funcao responsavel por recuperar um filme especifico */
/*  por um determinado ID.                                          */
/********************************************************************/
TFilmes getFilmeById(int p_FilmeId)
{
    char* l_registroLinha;
    TFilmes l_Filme;

    //Abrindo arquivo filmes.csv
    FILE* l_arquivo = abrirArquivo(FILMES_FILE,MODO_LEITURA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroFilme());
        //descartando cabecalho CSV
        descartarHeader(l_arquivo,getSizeRegistroFilme());
        while (fgets(l_registroLinha, getSizeRegistroFilme(), l_arquivo))
        {
            //carregando array de structs de filmes
            l_Filme.id_filme = atoi(getfield(strdup(l_registroLinha), 1));
            strcpy(l_Filme.nome,getfield(strdup(l_registroLinha), 2));
            strcpy(l_Filme.descricao,getfield(strdup(l_registroLinha), 3));
            strcpy(l_Filme.data_cadastro,getfield(strdup(l_registroLinha), 4));
            strcpy(l_Filme.diretor,getfield(strdup(l_registroLinha), 5));
            strcpy(l_Filme.sinopse,getfield(strdup(l_registroLinha), 6));
            l_Filme.classificacao = atoi(getfield(strdup(l_registroLinha), 7));

            //Ao encontrar o id de filmes para a pesquisa
            if(p_FilmeId == l_Filme.id_filme)
            {
                break;
            }
            memset( l_registroLinha, ESCAPE_ZERO, sizeof(l_registroLinha) );
        }
        fecharArquivo(l_arquivo);
    }
    else
    {
        return l_Filme;
    }
    return l_Filme;

}

/**********************************************/
/*  Descricao: Gerar ID de sequencia de filme */
/**********************************************/
int gerarIdSequenciaFilme()
{
    int l_sequenciaId=0;
    char* l_registroLinha;

    //Abrindo arquivo filmes.seq
    FILE* l_arquivo = abrirArquivo(FILMES_SEQ ,MODO_ESCRITA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroFilme());

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
int getSizeRegistroFilme()
{
     return sizeof(TFilmes)+8;
}
