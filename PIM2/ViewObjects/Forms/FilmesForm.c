#include <stdio.h>
#include "../../apresentacao.h"
#include "../../constantes.h"
#include "../../tipos.h"

extern int m_qtdFilmes;
extern TFilmes m_filmesLista[100];

int viewAdicionarFilme()
{

    TFilmes l_filme;
    memset(&l_filme, 0, sizeof(TFilmes));
    viewExibirFilmes("CADASTRO DE FILMES");
    printf("\n\nPreencha o formulario abaixo\n");
    printf("Nome............:");
    getString(l_filme.nome);

    printf("Descricao.......:");
    getString(l_filme.descricao);

    printf("Diretor.........:");
    getString(l_filme.diretor);

    printf("Sinopse.........:");
    getString(l_filme.sinopse);

    printf("Classificacao...:");
    getInteger(&l_filme.classificacao);

    adicionarFilme(l_filme);

    changeView("Filme Adicionado!!");


    return SUCESSO;

}


int viewRemoverFilme()
{
    int l_filmeId = 0;
    clear();
    viewExibirFilmes("CADASTRO DE FILMES");
    printf("Digite o codigo do filme para ser removido\n");
    printf("Codigo:");
    getInteger(&l_filmeId);
    removerFilme(l_filmeId);
    changeView("Filme Removido!!");


    return SUCESSO;

}

int viewEditarFilme()
{
    TFilmes l_filme;
    clear();
    viewExibirFilmes("CADASTRO DE FILMES");
    printf("Digite o codigo do filme para ser editado\n");
    printf("Codigo:");
    getInteger(&l_filme.id_filme);

    printf("\n\nPreencha o formulario abaixo para alterar os dados\n");
    printf("Nome............:");
    getString(l_filme.nome);

    printf("Descricao.......:");
    getString(l_filme.descricao);

    printf("Diretor.........:");
    getString(l_filme.diretor);

    printf("Sinopse.........:");
    getString(l_filme.sinopse);

    printf("Classificacao...:");
    getInteger(&l_filme.classificacao);


    editarFilme(l_filme);

    changeView("Filme Editado!!");
    return SUCESSO;

}

int menuAdministrarFilmes()
{
    int l_opcao = 0;
    while(INFINITO)
    {
        clear();
        header("Administrar Filmes");
        viewExibirFilmes("CADASTRO DE FILMES");
        printf(">[1]  Adicionar - Filme \n");
        printf(">[2]  Remover - Filme\n");
        printf(">[3]  Editar  - Filme\n");
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
                viewAdicionarFilme();
                break;
            case 2:
                viewRemoverFilme();
                break;
            case 3:
                viewEditarFilme();
                break;
            default:
                messageAlert(" OPCAO INVALIDA!!! FAVOR ESCOLHER UMA OPCAO VALIDA");
                break;
        }
        loadFilmes();
    }
}

int viewExibirFilmes(char mensagem[50])
{
    clear();
    loadFilmes();
    printf("\n_______________________________%s_____________________________\n\n",mensagem);
    printf("|Id\t|Nome\t\t\t\t\tClassificacao\n");
    printf("________________________________________________________________________________\n");
    for(int l_contador = 0; l_contador < m_qtdFilmes; l_contador++)
    {
        printf("|[%3d]:",m_filmesLista[l_contador].id_filme);
        printf("\t|%-30s", m_filmesLista[l_contador].nome);
        printf("\t\t|%2d\n", m_filmesLista[l_contador].classificacao);

    }
    printf("________________________________________________________________________________\n");

    return SUCESSO;

}
