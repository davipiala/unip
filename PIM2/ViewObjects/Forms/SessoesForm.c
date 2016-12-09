#include "../../apresentacao.h"
#include "../../constantes.h"
#include "../../tipos.h"
#include <stdio.h>

extern int m_qtdSessoes;
extern TSessoes m_sessoesLista[50];

int viewRemoverSessao()
{
    int l_codigo = 0;
    viewExibirHorarios();
    header("Remover- Sessao");
    viewExibirHorarios("CADASTRO DE SESSAO");
    printf("Selecione um codigo de sessao para ser removida\n");
    printf("________________________________________________________________________________\n");
    printf("Digite o codigo de sessao: ");

    getInteger( &l_codigo);
    removerSessao(l_codigo);
    changeView("Sessao Removido!!");

    return SUCESSO;

}

int viewEditarHorario()
{

    clear();
    TSessoes p_sessao;
    memset(&p_sessao, 0, sizeof(p_sessao));

    header("Editar - Sessao");
    viewExibirHorarios("CADASTRO DE SESSAO");
    printf("Selecione um codigo de sessao para ser editada\n");
    printf("________________________________________________________________________________\n");
    printf("Digite o codigo de sessao: ");

    getInteger(&p_sessao.id_sessao);

    printf("\nHora Inicio............: ");

    getString(p_sessao.hora_inicio);
    editarSessao(p_sessao);

    changeView("Sessao Editada!!");

    return SUCESSO;

}

int viewAdicionarHorario()
{
    clear();
    TSessoes p_sessao;
    memset(&p_sessao, 0, sizeof(TSessoes));

    header("Adicionar- Sessao");
    printf("\tPreencha o formulario passo a passo\n");
    printf("\tPasso [1] de [1]\n");

    printf("\nHora Inicio............:");
    getString(p_sessao.hora_inicio);
    adicionarSessao(p_sessao);

    clear();
    changeView("Sessao Adicionada!!");

    return SUCESSO;

}


int menuAdministrarHorarios()
{
    int l_opcao = 0;
    while(INFINITO)
    {
        loadSessoes();
        clear();
        header("Administrar Sessões");
        viewExibirHorarios("CADASTRO DE SESSOES");
        printf(">[1]  Adicionar - Sessoes \n");
        printf(">[2]  Remover - Sessoes\n");
        printf(">[3]  Editar  - Sessoes\n");
        printf(">[0]  Retonar ao menu anterior\n");
        printf("________________________________________________________________________________\n");
        printf(">Digite uma opção: ");
        getInteger(&l_opcao);
        switch (l_opcao)
        {
            case 0:
                return 0;
                break;
            case 1:
                viewAdicionarHorario();
                break;
            case 2:
                viewRemoverSessao();
                break;
            case 3:
                viewEditarHorario();
                break;
            default:
                messageAlert(" OPCAO INVALIDA!!! FAVOR ESCOLHER UMA OPCAO VALIDA");
                break;
        }
        loadFilmes();
    }
}


int viewExibirHorarios(char mensagem[50])
{
    clear();
    loadSessoes();
    printf("\n_______________________________%s____________________________\n\n",mensagem);
    printf("|Id\t|Início\n");
    printf("________________________________________________________________________________\n");
    for(int l_contador = 0; l_contador < m_qtdSessoes; l_contador++)
    {
        printf("|[%3d]:",m_sessoesLista[l_contador].id_sessao);
        printf("\t|%-5s\n", m_sessoesLista[l_contador].hora_inicio);
    }
    printf("________________________________________________________________________________\n");

    return SUCESSO;

}
