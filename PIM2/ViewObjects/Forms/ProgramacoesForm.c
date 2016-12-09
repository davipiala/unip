#include <stdio.h>
#include "../../apresentacao.h"
#include "../../constantes.h"
#include "../../assinaturas.h"
#include "../../tipos.h"
int adicionarProgramacao( TProgramacoes l_Programacao);

extern int m_qtdProgramacoes;
extern TProgramacoes m_programacoesLista[50];
extern TLugares m_lugares;


int viewAdicionarProgramacao()
{

   TProgramacoes l_Programacao;


    viewExibirProgramacao("CADASTRO DE PROGRAMAÇÃO");
    clear();
    header("Preencha passo a passo a wizard, para adicionar programação!");
    clear();

    loadFilmes();
    viewExibirFilmes("Escolher Filme");
    printf("Passo [1] de [3]\n");
    printf("Selecione o código de filme: ");
    getInteger( &l_Programacao.id_filme);
    clear();

    loadSalas();
    viewExibirSalas("Escolher Sala");
    printf("Passo [2] de [3]\n");
    printf("Selecione um id de sala: ");
    getInteger( &l_Programacao.id_sala);
    clear();

    loadSessoes();
    viewExibirHorarios("Escolher Sessao");
    printf("Passo [3] de [3]\n");
    printf("Selecione um id de sessao: ");
    getInteger( &l_Programacao.id_sessao);
    clear();


    l_Programacao.qtd_lugares = getSalaById(l_Programacao.id_sala).capacidade;
    adicionarProgramacao(l_Programacao);
    changeView("Programacao adicionada!!");


    return SUCESSO;

}

int viewEditarProgramacao()
{

    TProgramacoes l_Programacao;
    viewExibirProgramacao("CADASTRO DE PROGRAMAÇÃO");

    clear();
    header("Preencha passo a passo a wizard, para editar uma programação!");
    clear();

    loadFilmes();
    viewExibirFilmes("Escolher Filme");
    printf("Passo [1] de [3]\n");
    printf("Selecione o código do filme: ");
    getInteger( &l_Programacao.id_filme);
    clear();

    loadSalas();
    viewExibirSalas("Escolher Sala");
    printf("Passo [2] de [3]\n");
    printf("Selecione um id de sala: ");
    getInteger( &l_Programacao.id_programacao);
    clear();

    loadSessoes();
    viewExibirHorarios("Escolher Sessao");
    printf("Passo [3] de [3]\n");
    printf("Selecione um id de sessao: ");
    getInteger( &l_Programacao.id_sessao);
    clear();


    editarProgramacao(l_Programacao);

    return SUCESSO;
}

int viewRemoverProgramacao()
{
    int l_codigo = 0;

    viewExibirProgramacao("CADASTRO DE PROGRAMAÇÃO");
    printf("Selecione um codigo de programacao para remover\n");
    printf("Digite o código: ");
    getInteger(&l_codigo);
    removerProgramacao(l_codigo);
    changeView("Programacao removida!!");

    return SUCESSO;

}


int menuAdministrarProgramacao()
{
    int l_opcao = 0;
    while(INFINITO)
    {
        clear();
        header("Administrar Programação");
        viewExibirProgramacao("CADASTRO DE PROGRAMAÇÃO");

        printf(">[1]  Adicionar - Programação\n");
        printf(">[2]  Remover - Programação\n");
        printf(">[3]  Editar  - Programação\n");
        printf(">[0]  Retornar ao menu anterior\n");
        printf("________________________________________________________________________________\n");
        printf(">Digite uma opção: ");
        getInteger(&l_opcao);
        switch (l_opcao)
        {
            case 0:
                return 0;
                break;
            case 1:
                loadProgramacaoes();
                viewAdicionarProgramacao();
                break;
            case 2:
                loadProgramacaoes();
                viewRemoverProgramacao();
                break;

            case 3:
                loadProgramacaoes();
                viewEditarProgramacao();
                break;
            default:
                messageAlert(" OPCAO INVALIDA!!! FAVOR ESCOLHER UMA OPCAO VALIDA");
                break;
        }

    }
}




int viewExibirProgramacao(char* mensagem)
{
    clear();
    loadProgramacaoes();
    printf("\n_______________________________%s________________________\n\n",mensagem);
    printf("|Id\t|Filme\t\t\tSala\t\tSessao\n");
    printf("________________________________________________________________________________\n");
    for(int l_contador = 0; l_contador < m_qtdProgramacoes; l_contador++)
    {
        printf("|[%3d]:",m_programacoesLista[l_contador].id_programacao);
        printf("\t|%-30s", getFilmeById(m_programacoesLista[l_contador].id_filme).nome);
        printf("\t|%02d", m_programacoesLista[l_contador].id_sala);
        printf("\t\t|%-5s\n", getSessaoById(m_programacoesLista[l_contador].id_sessao).hora_inicio);

    }
    printf("________________________________________________________________________________\n");

    return SUCESSO;

}

int viewExibirLugares(int p_programacaoId)
{
    int l_linha = 0;
    int l_coluna = 0;

    TProgramacoes l_programacao = getProgramacaoById(p_programacaoId);
    TSalas l_sala = getSalaById(l_programacao.id_sala);

    getLugaresByIdProgramacao(l_programacao.id_programacao);
    clear();
    header("Lugares Ocupados");
    printf("\t\t ");
    for(l_coluna = 0; l_coluna <= l_sala.qtd_colunas; l_coluna++)
    {
        if((l_coluna % 4) == 0)
        {
            printf("    ");
        }
        printf(" %s -", getNomeColuna(l_coluna));
    }
    printf("\n________________________________________________________________________________\n");
    for(l_linha = 0; l_linha < l_sala.qtd_linhas; l_linha++)
    {
        printf("\t\t%02d",l_linha+1);
        for(l_coluna = 0; l_coluna <= l_sala.qtd_colunas; l_coluna++)
        {
            if((l_coluna % 4) == 0)
            {
                printf("    ");
            }
            printf("[");
            if(m_lugares.posicao[l_linha][l_coluna] == 1)
            {
                printf("X");
            }
            else{
                printf(" ");
            }
            printf("] ");
        }
        printf("\n");
    }
    printf("________________________________________________________________________________\n");

    return SUCESSO;

}

