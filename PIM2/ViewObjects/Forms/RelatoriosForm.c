#include <stdio.h>
#include <time.h>
#include "../../apresentacao.h"
#include "../../constantes.h"
#include "../../tipos.h"
#include "../../assinaturas.h"
#include "../../colors.h"

extern TLugares m_lugares;
extern TFilmes m_filmesLista[50];
extern TSalas m_salasLista[50];
extern TProgramacoes m_programacoesLista[50];
extern TSessoes m_sessoesLista[50];

extern int m_qtdFilmes;
extern int m_qtdSalas;
extern int m_qtdProgramacoes;



int menuRelatorio()
{
    while(INFINITO)
    {
        int l_opcao = 0;
        changeView("Carregar Bilheteria");
        header("Relatorios");
        printf(">[1]  Relatorio Geral\n");
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
                viewRelatorioGeral();
                break;

            default:
                messageAlert(" OPCAO INVALIDA!!! FAVOR ESCOLHER UMA OPCAO VALIDA");
                break;
        }
    }
}




int viewRelatorioGeral()
{


    changeView("Relatorio Geral");
    header("Relatorio Geral");

    printf("\t\t_________________________________________________________\n");
    printf("\t\t|\t\t\t\t\t\t\t|\n");
    printf("\t\t|\t\t %s \t\t\t\t|\n", systemDate());
    printf("\t\t_________________________________________________________\n");
    printf("\t\t|\t\t Hoje \t\t\t\t\t|\n");
    printf("\t\t| Valor Total Transacoes....: R$ %7.2f\t\t|\n", getValorTransacaoByDate(systemDate()));
    printf("\t\t| Quantidade de Transacoes..: \t%8d\t\t|\n", getQtdTransacaoByDate(systemDate()));
    printf("\t\t_________________________________________________________\n");
    printf("\n\n");
    printf("Pressione ENTER para continuar");
    pressKey();

}
