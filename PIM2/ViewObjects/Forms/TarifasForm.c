#include <stdio.h>
#include "../../apresentacao.h"
#include "../../constantes.h"
#include "../../tipos.h"
#include "../../assinaturas.h"
#include "../../globais.h"

extern int m_qtdTarifas;
extern TTarifas m_TarifasLista[50];

int menuAdministrarTarifas()
{
    int l_opcao = 0;
    while(INFINITO)
    {
        clear();

        header("Administrar Tarifas");
        viewExibirTarifas("CADASTRO DE TARIFAS");

        printf(">[1]  Adicionar - Tarifas\n");
        printf(">[2]  Remover - Tarifas\n");
        printf(">[3]  Editar  - Tarifas\n");
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
                viewAdicionarTarifa();
                break;
            case 2:
                viewRemoverTarifa();
                break;
            case 3:
                viewEditarTarifa();
                break;
            default:
                messageAlert(" OPCAO INVALIDA!!! FAVOR ESCOLHER UMA OPCAO VALIDA");
                break;
        }
        loadFilmes();
    }
}




int viewRemoverTarifa()
{
    int l_IdTarifa = 0;

    header("Remover - Preco");
    viewExibirTarifas("CADASTRO DE TARIFAS");
    printf("\tPasso [1] de [1]\n");
    printf("________________________________________________________________________________\n");
    printf(">Digite id de tarifa para ser excluída: ");
    getInteger(&l_IdTarifa);

    removerTarifa(l_IdTarifa);
    clear();
    changeView("Tarifa Removida!!");

    return SUCESSO;

}


int viewEditarTarifa()
{

    int l_IdTarifa = 0;
    TTarifas p_tarifa;
    memset(&p_tarifa, 0, sizeof(p_tarifa));


    header("Editar - Preco");
    viewExibirTarifas("CADASTRO DE TARIFAS");
    printf("|Selecione um id de tarifa para ser editada\n");
    printf("________________________________________________________________________________\n");
    printf("|Digite o código:");

    getInteger(&p_tarifa.id_tarifa);

    printf("\nDescrição............:");
    getString(p_tarifa.descricao);


    printf("\nValor............:");
    getFloat(&p_tarifa.valor);

    editarTarifa(p_tarifa);

    clear();
    changeView("Tarifa Editada!!");


    return SUCESSO;

}

int viewAdicionarTarifa()
{

    TTarifas p_tarifa;
    memset(&p_tarifa, 0, sizeof(TTarifas));

    clear();
    header("Adicionar - Tarifas");
    printf("|Preencha o formulario passo a passo\n");
    printf("|Passo [1] de [1]\n");
    printf("________________________________________________________________________________\n");

    printf("\nDescricao............:");

    getString(p_tarifa.descricao);

    printf("\nValor............:");
    getFloat(&p_tarifa.valor);

    adicionarPreco(p_tarifa);

    clear();
    changeView("Tarifa Adicionada!!");

    loadTarifas();
    return SUCESSO;

}

int viewExibirTarifas(char mensagem[50])
{
    clear();
    loadTarifas();
    printf("\n_______________________________%s_____________________________\n\n", mensagem);
    printf("|Id\t|Descrição\t\t\t|Valor\n");
    printf("________________________________________________________________________________\n");
    for(int l_contador = 0; l_contador < m_qtdTarifas; l_contador++)
    {
        printf("|[%3d]:",m_TarifasLista[l_contador].id_tarifa);
        printf("\t|%-12s", m_TarifasLista[l_contador].descricao);
        printf("\t\t\t|R$ %02.2f\n", m_TarifasLista[l_contador].valor);

    }
    printf("________________________________________________________________________________\n");

    return SUCESSO;

}

int viewGetTarifa()
{
    clear();
    loadTarifas();
    printf("Escolha um id de tarifa : \n");
    printf("________________________________________________________________________________\n");
    printf("|Id\t|Descrição\t|Valor\n");
    printf("________________________________________________________________________________\n");
    for(int l_contador = 0; l_contador < m_qtdTarifas; l_contador++)
    {
        printf("|[%3d]:",m_TarifasLista[l_contador].id_tarifa);
        printf("\t|%-12s", m_TarifasLista[l_contador].descricao);
        printf("\t|R$ %0.2f\n", m_TarifasLista[l_contador].valor);


    }
    printf("________________________________________________________________________________\n");
    printf("\nDigite sua opcao: ");

    return SUCESSO;

}


