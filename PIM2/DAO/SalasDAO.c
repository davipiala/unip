/****************************************************************************/
/*  CineXperience 2.0 - Projeto Integrado Multidisciplinar - Unip 2016 2Sem */
/*  Autor: Elton dos Santos Data: 02/11/16                                  */
/*  Descricao: DAO - Data Access Object                                     */
/*  Responsável por gerenciar arquivo de salas.csv criar, remover           */
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
#define MASK_FORMAT "%d;%d;%d;%d\n"

//Referencia a variaveis globais
extern int m_qtdSalas;
extern TSalas m_salasLista[50];

/******************************************************/
/*  Descricao: Funcao responsavel por adicionar sala  */
/******************************************************/
int adicionarSala(TSalas p_sala)
{
    char* l_registroLinha;
    //Abrindo arquivo salas.csv
    FILE* l_arquivo = abrirArquivo(SALAS_FILE,MODO_ESCRITA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroSala());

        //Formatando a string com dados de sala para gravar no arquivo
        sprintf(l_registroLinha
        ,MASK_FORMAT
        ,gerarIdSequenciaSala()
        ,p_sala.qtd_colunas * p_sala.qtd_linhas
        ,p_sala.qtd_linhas
        ,p_sala.qtd_colunas);

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
/*  Descricao: Funcao responsavel por editar sala */
/*  Obs: necessario de dois arquivos para realizar*/
/*  edicao da linha do arquivo, cria um arquivo   */
/*  temporario com a linha editada e depois reno- */
/*  meia para o arquivo original.                 */
/**************************************************/
int editarSala(TSalas p_sala)
{

    char* l_registroLinha;

    //Abrindo arquivo salas.csv e criando arquivo temporario
    FILE* l_arquivo = abrirArquivo(SALAS_FILE,MODO_ESCRITA);
    FILE* l_arquivoAux = abrirArquivo(TMP_FILE, "w+");

    if(l_arquivo && l_arquivoAux )
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroSala());
        while (fgets(l_registroLinha, getSizeRegistroSala(), l_arquivo))
        {
            //caso seja a linha correta para editar, carrega os dados para string
            if(p_sala.id_sala == atoi(getfield(strdup(l_registroLinha), 1)))
            {
                //Formatando a string com dados de sala para gravar no arquivo
                sprintf(l_registroLinha, MASK_FORMAT
                ,p_sala.id_sala
                ,p_sala.qtd_colunas * p_sala.qtd_linhas
                ,p_sala.qtd_linhas
                ,p_sala.qtd_colunas);
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
        remove(SALAS_FILE);
        //renomeando arquivo temporario para original
        rename(TMP_FILE, SALAS_FILE);
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;
}

/**************************************************/
/*  Descricao: Funcao responsavel por remover sala*/
/*  Obs: necessario de dois arquivos para realizar*/
/*  remocao da linha do arquivo.                  */
/**************************************************/
int removerSala(int p_salaId)
{

    char* l_registroLinha;

    //Abrindo arquivo salas.csv e criando arquivo temporario
    FILE* l_arquivo = abrirArquivo(SALAS_FILE,MODO_LEITURA);
    FILE* l_arquivoAux = abrirArquivo(TMP_FILE, "w+");

    if(l_arquivo && l_arquivoAux)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroSala());
        while (fgets(l_registroLinha, getSizeRegistroSala(), l_arquivo))
        {
            //caso seja a linha correta para remover, carrega os dados para string
            if(p_salaId==atoi(getfield(strdup(l_registroLinha), 1)))
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
        remove(SALAS_FILE);
        //renomeando arquivo temporario para original
        rename(TMP_FILE, SALAS_FILE);
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;
}

/*****************************************************/
/*  Descricao: Funcao responsavel pela carga do      */
/*  do array de salas, todas as salas são carregadas */
/*  a partir do arquivo salas.csv.                   */
/*****************************************************/
int loadSalas()
{
    int l_contador = 0;
    char* l_registroLinha;
    //Abrindo arquivo salas.csv
    FILE* l_arquivo = abrirArquivo(SALAS_FILE,MODO_LEITURA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroSala());
        //descartando cabecalho CSV
        descartarHeader(l_arquivo,getSizeRegistroSala());
        while (fgets(l_registroLinha, getSizeRegistroSala(), l_arquivo))
        {
            //carregando array de structs de salas
            m_salasLista[l_contador].id_sala = atoi(getfield(strdup(l_registroLinha), 1));
            m_salasLista[l_contador].capacidade = atoi(getfield(strdup(l_registroLinha), 2));
            m_salasLista[l_contador].qtd_linhas= atoi(getfield(strdup(l_registroLinha), 3));
            m_salasLista[l_contador].qtd_colunas = atoi(getfield(strdup(l_registroLinha), 4));
            l_contador++;

        }
        //fechando os arquivos
        fecharArquivo(l_arquivo);
        //quantificando a quantidade de registros
        m_qtdSalas = l_contador;

    }
    else
    {
        return ERRO;
    }
    return SUCESSO;

}

/********************************************************************/
/*  Descricao: Funcao responsavel por recuperar uma sala especifica */
/*  por um determinado ID.                                          */
/********************************************************************/
TSalas getSalaById(int p_SalaId)
{
    char* l_registroLinha;
    TSalas l_Sala;
    //Abrindo arquivo salas.csv
    FILE* l_arquivo = abrirArquivo(SALAS_FILE,MODO_LEITURA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroSala());
        //descartando cabecalho CSV
        descartarHeader(l_arquivo,getSizeRegistroSala());
        while (fgets(l_registroLinha, getSizeRegistroSala(), l_arquivo))
        {
            //carregando array de structs de salas
            l_Sala.id_sala = atoi(getfield(strdup(l_registroLinha), 1));
            l_Sala.capacidade = atoi(getfield(strdup(l_registroLinha), 2));
            l_Sala.qtd_linhas= atoi(getfield(strdup(l_registroLinha), 3));
            l_Sala.qtd_colunas = atoi(getfield(strdup(l_registroLinha), 4));
            //Ao encontrar o id de sala correta para a pesquisa
            if(p_SalaId == l_Sala.id_sala)
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
        return l_Sala;
    }
    return l_Sala;

}

/**********************************************/
/*  Descricao: Gerar ID de sequencia de salas */
/**********************************************/
int gerarIdSequenciaSala()
{
    int l_sequenciaId = 0;
    char* l_registroLinha;
    FILE* l_arquivo = NULL;
    //Abrindo arquivo salas.seq
    l_arquivo = abrirArquivo(SALAS_SEQ ,MODO_ESCRITA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroSala());
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
int getSizeRegistroSala()
{
     return sizeof(TFilmes)+8;
}



