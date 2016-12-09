#include <stdio.h>
#include "../../apresentacao.h"
#include "../../constantes.h"
#include "../../tipos.h"

extern int m_qtdSalas;
extern TSalas m_salasLista[50];

int viewEditarSala()
{

    TSalas l_sala;
    memset(&l_sala, 0, sizeof(TSalas));

    clear();
    header("Editar - Sala");
    viewExibirSalas("CADASTRO DE SALA");

    printf("Selecione uma sala para ser editada\n");
    printf("Digite o código de sala: ");
    getInteger(&l_sala.id_sala);

    printf("\nQuantidade de Linhas...:");
    getInteger(&l_sala.qtd_linhas);

    printf("\nQuantidade de Colunas...:");
    getInteger(&l_sala.qtd_colunas);

    editarSala(l_sala);
    changeView("Sala Editada!!");



    return SUCESSO;

}

int viewRemoverSala()
{
    int l_salaId = 0;
    clear();
    header("Remover - Sala");
    viewExibirSalas("CADASTRO DE SALA");
    printf("Selecione uma sala para ser removida\n");
    printf("Digite o codigo de sala:");
    getInteger(&l_salaId);
    removerSala(l_salaId);
    changeView("Sala Removida!!");


    return SUCESSO;

}

int viewAdicionarSala()
{


    TSalas l_sala;
    memset(&l_sala, 0, sizeof(l_sala));
    clear();
    header("Adicionar- Sala");
    viewExibirSalas("CADASTRO DE SALA");

    printf("\tPreencha o formulario passo a passo\n");
    printf("\tPasso [1] de [1]\n");

    printf("\Quantidade de Linhas...:");
    getInteger(&l_sala.qtd_linhas);

    printf("\Quantidade de Colunas...:");
    getInteger(&l_sala.qtd_colunas);
    adicionarSala(l_sala);
    changeView("Sala Adicionada!!");



    return SUCESSO;

}


int menuAdministrarSalas()
{
    int l_opcao = 0;
    while(INFINITO)
    {
        clear();
        header("Administrar Salas");
        viewExibirSalas("CADASTRO DE SALAS");

        printf(">[1]  Adicionar - Salas \n");
        printf(">[2]  Remover - Salas\n");
        printf(">[3]  Editar  - Salas\n");
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
                viewAdicionarSala();
                break;
            case 2:
                viewRemoverSala();
                break;
            case 3:
                viewEditarSala();
                break;
            default:
                messageAlert(" OPCAO INVALIDA!!! FAVOR ESCOLHER UMA OPCAO VALIDA");
                break;
        }
        loadFilmes();
    }
}

int viewExibirSalas(char mensagem[50])
{
    clear();
    loadSalas();
    printf("\n_______________________________%s_____________________________\n\n",mensagem);
    printf("|Id\t|Capacidade\n");
    printf("________________________________________________________________________________\n");
    for(int l_contador = 0; l_contador < m_qtdSalas; l_contador++)
    {
        printf("|[%3d]:",m_salasLista[l_contador].id_sala);
        printf("\t|%3d\n", m_salasLista[l_contador].capacidade);

    }
    printf("________________________________________________________________________________\n");

    return SUCESSO;

}
