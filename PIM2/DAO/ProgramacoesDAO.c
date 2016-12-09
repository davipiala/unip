/****************************************************************************/
/*  CineXperience 2.0 - Projeto Integrado Multidisciplinar - Unip 2016 2Sem */
/*  Autor: Elton dos Santos Data: 08/11/16                                  */
/*  Descricao: DAO - Data Access Object                                     */
/*  Responsável por gerenciar arquivo de programacoes.csv criar, remover    */
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
#include "../colors.h"
#include "../assinaturas.h"


//constantes
#define MASK_FORMAT "%d;%d;%d;%d;%d\n"

//Referencia a variaveis globais
extern int m_qtdProgramacoes;
extern TProgramacoes m_programacoesLista[50];
extern TLugares m_lugares;

/************************************************************/
/*  Descricao: Funcao responsavel por adicionar programacao */
/************************************************************/
int adicionarProgramacao(TProgramacoes p_programacao)
{
    char* l_registroLinha;
    p_programacao.id_programacao = gerarIdSequenciaProgramacao();

    //Abrindo arquivo programacoes.csv
    FILE* l_arquivo = abrirArquivo(PROGRAMACOES_FILE,MODO_ESCRITA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroProgramacoes());

        //Formatando a string com dados de prgramacao para gravar no arquivo
        sprintf(l_registroLinha
        , MASK_FORMAT
        ,p_programacao.id_programacao
        ,p_programacao.id_sala
        ,p_programacao.id_sessao
        ,p_programacao.id_filme
        ,p_programacao.qtd_lugares);

        //posicionando o ponteiro no final do arquivo fseek e adicionando linha ao final do arquivo
        posicionarFimArquivo(l_arquivo);
        adicionarLinhaArquivo(l_registroLinha,l_arquivo);

        //fechar o arquivo e liberar memoria
        fecharArquivo(l_arquivo);
        adicionarArquivoLugares(p_programacao);
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;
}

/***********************************************************/
/*  Descricao: Funcao responsavel por editar programacoes  */
/*  Obs: necessario de dois arquivos para realizar         */
/*  edicao da linha do arquivo, cria um arquivo            */
/*  temporario com a linha editada e depois reno-          */
/*  meia para o arquivo original.                          */
/***********************************************************/
int editarProgramacao(TProgramacoes p_programacao)
{

    char* l_registroLinha;

    //Abrindo arquivo programacoes.csv e criando arquivo temporario
    FILE* l_arquivo = abrirArquivo(PROGRAMACOES_FILE,MODO_ESCRITA);
    FILE* l_arquivoAux = abrirArquivo(TMP_FILE, "w+");

    if(l_arquivo && l_arquivoAux)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroProgramacoes());
        while (fgets(l_registroLinha, getSizeRegistroProgramacoes(), l_arquivo))
        {
                //caso seja a linha correta para editar, carrega os dados para string
            if(p_programacao.id_programacao ==atoi(getfield(strdup(l_registroLinha), 1)))
            {
                sprintf(l_registroLinha, MASK_FORMAT
                ,p_programacao.id_programacao
                ,p_programacao.id_sala
                ,p_programacao.id_sessao
                ,p_programacao.id_filme
                ,p_programacao.qtd_lugares);
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
        remove(PROGRAMACOES_FILE);
        //renomeando arquivo temporario para original
        rename(TMP_FILE, PROGRAMACOES_FILE);
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;
}

/***********************************************************/
/*  Descricao: Funcao responsavel por remover programacoes */
/*  Obs: necessario de dois arquivos para realizar         */
/*  remocao da linha do arquivo.                           */
/***********************************************************/
int removerProgramacao(int p_idProgramacao)
{
    char* l_registroLinha;

    //Abrindo arquivo programacoes.csv e criando arquivo temporario
    FILE* l_arquivo = abrirArquivo(PROGRAMACOES_FILE,MODO_ESCRITA);
    FILE* l_arquivoAux = abrirArquivo(TMP_FILE, "w+");

    if(l_arquivo && l_arquivoAux)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroProgramacoes());
        while (fgets(l_registroLinha, getSizeRegistroProgramacoes(), l_arquivo))
        {
            //caso seja a linha correta para remover, carrega os dados para string
            if(p_idProgramacao==atoi(getfield(strdup(l_registroLinha), 1)))
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
        remove(PROGRAMACOES_FILE);
        //renomeando arquivo temporario para original
        rename(TMP_FILE, PROGRAMACOES_FILE);
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;
}

/************************************************************/
/*  Descricao: Funcao responsavel pela carga do             */
/*  do array de programacao, todas as formas são carregadas */
/*  a partir do arquivo formas de pagamento.csv.            */
/************************************************************/
int loadProgramacaoes()
{
    int l_contador=0;
    char* l_registroLinha;

    //Abrindo arquivo programacoes.csv
    FILE* l_arquivo = abrirArquivo(PROGRAMACOES_FILE,MODO_LEITURA);


    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroProgramacoes());
        //descartando cabecalho CSV
        descartarHeader(l_arquivo,getSizeRegistroProgramacoes());
        while (fgets(l_registroLinha, getSizeRegistroProgramacoes(), l_arquivo))
        {
            //carregando array de structs de programacao
            m_programacoesLista[l_contador].id_programacao = atoi(getfield(strdup(l_registroLinha), 1));
            m_programacoesLista[l_contador].id_sala  = atoi(getfield(strdup(l_registroLinha), 2));
            m_programacoesLista[l_contador].id_sessao  = atoi(getfield(strdup(l_registroLinha), 3));
            m_programacoesLista[l_contador].id_filme  = atoi(getfield(strdup(l_registroLinha), 4));
            m_programacoesLista[l_contador].qtd_lugares = atoi(getfield(strdup(l_registroLinha), 5));
            l_contador++;

            //Ĺimpar string de leitura
            memset( l_registroLinha, ESCAPE_ZERO, sizeof(l_registroLinha) );
        }
        //fechando os arquivos
        fecharArquivo(l_arquivo);

        //quantificando a quantidade de registros
        m_qtdProgramacoes = l_contador;
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;

}


/************************************************************/
/*  Descricao: Funcao responsavel pela carga do             */
/*  do array de ocupacao, todas as formas são carregadas    */
/*  a partir do arquivo dinâmico                            */
/************************************************************/
int getLugaresByIdProgramacao(int p_programacaoId)
{
    TProgramacoes l_Programacao;
    int l_linha=0;
    int l_coluna=2;
    int l_sizeColunas = getSalaById(getProgramacaoById(p_programacaoId).id_sala).qtd_colunas;
    char* l_registroLinha;
    char* l_nomeArquivo;
    l_nomeArquivo = calloc(1,getSizeRegistroProgramacoes());

    //Abrindo arquivo opacoes[dinamico].csv

    sprintf(l_nomeArquivo, "%s%d%s"
                ,LUGARES_FILE
                ,p_programacaoId
                ,".csv");

    FILE* l_arquivo = abrirArquivo(l_nomeArquivo,MODO_LEITURA);

    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroProgramacoes());
        //descartando cabecalho CSV
        descartarHeader(l_arquivo,getSizeRegistroProgramacoes());
        while (fgets(l_registroLinha, getSizeRegistroProgramacoes(), l_arquivo))
        {
            //carregando array de structs de programacao
            for(int l_coluna=2;l_coluna<l_sizeColunas;l_coluna++)
            {
                int valor_coluna = atoi(getfield(strdup(l_registroLinha), l_coluna));
                m_lugares.posicao[l_linha][l_coluna-2] = valor_coluna;
            }
            l_linha++;

            //Ĺimpar string de leitura
            memset( l_registroLinha, ESCAPE_ZERO, sizeof(l_registroLinha) );
        }
        //fechando os arquivos
        fecharArquivo(l_arquivo);

        //quantificando a quantidade de registros
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;

}
/**********************************************************/
/*  Descricao: Funcao responsavel por adicionar assento   */
/**********************************************************/

int adicionarArquivoLugares(TProgramacoes p_programacao )
{
    int l_linha=0;
    int l_coluna=0;

    char* l_registroLinha;
    char* l_nomeArquivo;

    TSalas l_sala;
    l_sala =  getSalaById(p_programacao.id_sala);

    l_nomeArquivo = calloc(1,getSizeRegistroProgramacoes());

    //Abrindo arquivo opacoes[dinamico].csv

    sprintf(l_nomeArquivo, "%s%d%s"
                ,LUGARES_FILE
                ,p_programacao.id_programacao
                ,".csv");

    FILE* l_arquivo = abrirArquivo(l_nomeArquivo,"w+");

    if(l_arquivo )
    {
        l_registroLinha = calloc(1,getSizeRegistroProgramacoes());
        strcat(l_registroLinha," ;");
        for(l_coluna = 0; l_coluna <= l_sala.qtd_colunas; l_coluna++)
        {
            strcat(l_registroLinha,getNomeColuna(l_coluna));
            strcat(l_registroLinha,";");
        }
        strcat(l_registroLinha,"\n");
        adicionarLinhaArquivo(l_registroLinha, l_arquivo);
        memset( l_registroLinha, ESCAPE_ZERO, sizeof(l_registroLinha) );
        for(l_linha = 0; l_linha < l_sala.qtd_linhas; l_linha++)
        {
            sprintf(l_registroLinha, "%d",l_linha);
            for(l_coluna = 0; l_coluna <= l_sala.qtd_colunas; l_coluna++)
            {
                char* l_posicao;
                l_posicao = calloc(1,getSizeRegistroProgramacoes());
                sprintf(l_posicao, ";%d",m_lugares.posicao[l_linha][l_coluna]);
                strcat(l_registroLinha,l_posicao);

            }
            strcat(l_registroLinha,"\n");
            adicionarLinhaArquivo(l_registroLinha, l_arquivo);

        }
        //fechando os arquivos
        fecharArquivo(l_arquivo);

    }
    else
    {
        return ERRO;
    }
    return SUCESSO;

}


/**********************************************************/
/*  Descricao: Funcao responsavel por adicionar assento   */
/**********************************************************/

int registrarAssentos(TProgramacoes p_programacao )
{
    int l_linha=0;
    int l_coluna=0;

    char* l_registroLinha;
    char* l_nomeArquivo;

    TSalas l_sala;
    l_sala =  getSalaById(p_programacao.id_sala);

    l_nomeArquivo = calloc(1,getSizeRegistroProgramacoes());

    //Abrindo arquivo opacoes[dinamico].csv

    sprintf(l_nomeArquivo, "%s%d%s"
                ,LUGARES_FILE
                ,p_programacao.id_programacao
                ,".csv");
    remove(l_nomeArquivo);


    FILE* l_arquivo = abrirArquivo(TMP_FILE,"w+");

    if(l_arquivo )
    {
        l_registroLinha = calloc(1,getSizeRegistroProgramacoes());
        strcat(l_registroLinha," ;");
        for(l_coluna = 0; l_coluna <= l_sala.qtd_colunas; l_coluna++)
        {
            strcat(l_registroLinha,getNomeColuna(l_coluna));
            strcat(l_registroLinha,";");
        }
        strcat(l_registroLinha,"\n");
        adicionarLinhaArquivo(l_registroLinha, l_arquivo);
        memset( l_registroLinha, ESCAPE_ZERO, sizeof(l_registroLinha) );
        for(l_linha = 0; l_linha < l_sala.qtd_linhas; l_linha++)
        {
            sprintf(l_registroLinha, "%d",l_linha);
            for(l_coluna = 0; l_coluna <= l_sala.qtd_colunas; l_coluna++)
            {
                char* l_posicao;
                l_posicao = calloc(1,getSizeRegistroProgramacoes());
                sprintf(l_posicao, ";%d",m_lugares.posicao[l_linha][l_coluna]);
                strcat(l_registroLinha,l_posicao);

            }
            strcat(l_registroLinha,"\n");
            adicionarLinhaArquivo(l_registroLinha, l_arquivo);

        }
        //fechando os arquivos
        fecharArquivo(l_arquivo);
        rename(TMP_FILE, l_nomeArquivo);

    }
    else
    {
        return ERRO;
    }
    return SUCESSO;

}

/********************************************************************************/
/*  Descricao: Funcao responsavel por recuperar formas de programacao especifica */
/*  por um determinado ID.                                                       */
/*********************************************************************************/
TProgramacoes getProgramacaoById(int p_IdProgramacao)
{
    char* l_registroLinha;
    TProgramacoes l_Programacao;

    //Abrindo arquivo programacoes.csv
    FILE* l_arquivo = abrirArquivo(PROGRAMACOES_FILE,MODO_LEITURA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroProgramacoes());
        //descartando cabecalho CSV
        descartarHeader(l_arquivo);
        while (fgets(l_registroLinha, getSizeRegistroProgramacoes(), l_arquivo))
        {
            //carregando array de structs de programacao
            l_Programacao.id_programacao = atoi(getfield(strdup(l_registroLinha), 1));
            l_Programacao.id_sala  = atoi(getfield(strdup(l_registroLinha), 2));
            l_Programacao.id_sessao  = atoi(getfield(strdup(l_registroLinha), 3));
            l_Programacao.id_filme  = atoi(getfield(strdup(l_registroLinha), 4));
            l_Programacao.qtd_lugares= atoi(getfield(strdup(l_registroLinha), 5));

            //Ao encontrar o id de formas de programcao para a pesquisa
            if(l_Programacao.id_programacao  == p_IdProgramacao)
            {
                break;
            }
            //Ĺimpar string de leitura
            memset( l_registroLinha, ESCAPE_ZERO, sizeof(l_registroLinha) );
        }
        fecharArquivo(l_arquivo);
    }
    else
    {
        return l_Programacao;
    }
    return l_Programacao;
}

/****************************************************/
/*  Descricao: Gerar ID de sequencia de programacao */
/****************************************************/
int gerarIdSequenciaProgramacao()
{
    int l_sequenciaId=0;
    char* l_registroLinha;

    //Abrindo arquivo programacoes.seq
    FILE* l_arquivo = abrirArquivo(PROGRAMACOES_SEQ ,MODO_ESCRITA);
    if(l_arquivo)
    {
        //alocando espaço na string que corresponde a linha do arquivo
        l_registroLinha = calloc(1,getSizeRegistroProgramacoes());

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
int getSizeRegistroProgramacoes()
{
     return sizeof(TFilmes)+8;
}
