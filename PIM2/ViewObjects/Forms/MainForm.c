#include <stdio.h>
#include <time.h>
#include "../../apresentacao.h"
#include "../../constantes.h"
#include "../../tipos.h"
#include "../../assinaturas.h"
#include "../../colors.h"


extern TFilmes m_filmesLista[50];
extern TSalas m_salasLista[50];
extern TProgramacoes m_programacoesLista[50];
extern TSessoes m_sessoesLista[50];

extern int m_qtdFilmes;
extern int m_qtdSalas;
extern int m_qtdProgramacoes;


int menuAdministrarSistema()
{
    int l_opcao = 0;
    while(INFINITO)
    {
        changeView("Carregar Administração Sistema");
        header("Administração do Sistema");
        printf(">[1]  Gerenciar - Filmes\n");
        printf(">[2]  Gerenciar - Salas\n");
        printf(">[3]  Gerenciar - Sessoes\n");
        printf(">[4]  Gerenciar - Tarifas\n");
        printf(">[5]  Gerenciar - Formas Pagamento\n");
        printf(">[6]  Gerenciar - Programação\n");
        printf(">[0]  Retornar para o menu anterior\n");
        printf("________________________________________________________________________________\n");
        printf(">Digite uma opção: ");
        getInteger(&l_opcao);
        switch (l_opcao)
        {
            case 0:
                return 0;
                break;
            case 1:
                menuAdministrarFilmes();
                break;
            case 2:
                menuAdministrarSalas();
                break;
            case 3:
                menuAdministrarHorarios();
                break;
            case 4:
                menuAdministrarTarifas();
                break;
            case 5:
                menuAdministrarFormasPagamento();
                break;
            case 6:
                menuAdministrarProgramacao();
                break;
            default:
                messageAlert(" OPCAO INVALIDA!!! FAVOR ESCOLHER UMA OPCAO VALIDA");
                break;
        }
        changeView("Retornando para Anterior");
    }
}

int menuPrincipal()
{

    fflush(stdin);
    int l_opcao = 0;
    while(INFINITO)
    {

        header("Administração do Sistema");
        printf(">[1]  Administração\n");
        printf(">[2]  Bilheteria\n");
        printf(">[3]  Relatórios\n");
        printf(">[0]  Sair do sistema\n");
        printf("________________________________________________________________________________\n");
        printf(">Digite uma opção: ");
        getInteger(&l_opcao);
        switch (l_opcao)
        {
            case 0:
                changeView("Saindo da aplicacao!!");
                return 0;
                break;
            case 1:
                menuAdministrarSistema();
                break;
            case 2:
                menuAdministrarBilhetaria();
                break;
            case 3:
                menuRelatorio();
                break;
            default:
                messageAlert(" OPCAO INVALIDA!!! FAVOR ESCOLHER UMA OPCAO VALIDA");
                break;
        }
        changeView("Retornando para Anterior");
    }
}
