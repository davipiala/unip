#include <stdio.h>
#include "../../apresentacao.h"
#include "../../constantes.h"
#include "../../tipos.h"

extern int m_qtdFormaPagamentos;
extern TFormaPagamentos m_formaPagamentosLista[50];

int menuAdministrarFormasPagamento()
{
    int l_opcao = 0;
    while(INFINITO)
    {
        clear();

        header("Administrar Formas Pagamento");
        viewExibirFormasPagamento("CADASTRO DE FORMAS PAGAMENTO");

        printf(">[1]  Adicionar - Formas Pagamento\n");
        printf(">[2]  Remover - Formas Pagamento\n");
        printf(">[3]  Editar  - Formas Pagamento\n");
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
                viewAdicionarTarifaFormasPagamento();
                break;
            case 2:
                viewRemoverFormasPagamento();
                break;
            case 3:
                viewEditarFormasPagamento();
                break;
            default:
                messageAlert(" OPCAO INVALIDA!!! FAVOR ESCOLHER UMA OPCAO VALIDA");
                break;
        }
        loadFilmes();
    }
}




int viewRemoverFormasPagamento()
{
    int l_idFormaPagamento = 0;

    header("Remover - Formas Pagamento");
    viewExibirFormasPagamento("CADASTRO de Formas Pagamento");
    printf("\tPasso [1] de [1]\n");
    printf("________________________________________________________________________________\n");
    printf(">Digite id de forma de pagamento para ser excluído: ");
    getInteger(&l_idFormaPagamento);

    removerFormaPagamento(l_idFormaPagamento);
    clear();
    changeView("Formas de Pagamento!!");

    return SUCESSO;

}


int viewEditarFormasPagamento()
{

    TFormaPagamentos l_formaPagamento;
    memset(&l_formaPagamento, 0, sizeof(l_formaPagamento));

    clear();
    header("Editar - Forma de Pagamento");
    viewExibirFormasPagamento("CADASTRO DE FORMAS DE PAGAMENTO");

    printf("|Selecione um id de forma de pagamento para editar");
    printf("\n|Digite o código:");


    getInteger(&l_formaPagamento.id_forma);

    printf("\n|Digite uma descrição para forma de pagamento:");
    getString(l_formaPagamento.descricao);

    editarFormaPagamento(l_formaPagamento);

    clear();
    changeView("Forma de Pagamento Editada!!");


    return SUCESSO;

}

int viewAdicionarTarifaFormasPagamento()
{

    TFormaPagamentos l_formaPagamento;
    memset(&l_formaPagamento, 0, sizeof(TFormaPagamentos));

    clear();
    header("Adicionar - Forma de Pagamento");
    printf("|Preencha o formulario passo a passo\n");
    printf("|Passo [1] de [1]\n");
    printf("________________________________________________________________________________\n");

    printf("\nDescricao............:");

    getString(l_formaPagamento.descricao);

    adicionarFormaPagamento(l_formaPagamento);

    clear();
    changeView("Forma de Pagamento Adicionado!!");

    loadTarifas();
    return SUCESSO;

}

int viewExibirFormasPagamento(char mensagem[50])
{
    clear();
    loadFormaPagamentos();
    printf("\n_______________________________%s_____________________________\n\n", mensagem);
    printf("|Id\t|Descrição\n");
    printf("________________________________________________________________________________\n");
    for(int l_contador = 0; l_contador < m_qtdFormaPagamentos; l_contador++)
    {
        printf("|[%3d]:",m_formaPagamentosLista[l_contador].id_forma);
        printf("\t|%s\n", m_formaPagamentosLista[l_contador].descricao);


    }
    printf("________________________________________________________________________________\n");

    return SUCESSO;

}

int viewGetFormaPagamento()
{
    clear();
    loadFormaPagamentos();
    printf("Escolha uma forma de pagamento : \n");
    printf("________________________________________________________________________________\n");
    printf("|Id\t|Descrição\n");
    printf("________________________________________________________________________________\n");
    for(int l_contador = 0; l_contador < m_qtdFormaPagamentos; l_contador++)
    {
        printf("|[%3d]:",m_formaPagamentosLista[l_contador].id_forma);
        printf("\t|%s\n", m_formaPagamentosLista[l_contador].descricao);


    }
    printf("________________________________________________________________________________\n");
    printf("\nDigite sua opcao: ");

    return SUCESSO;

}


