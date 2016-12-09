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
TBilhetes m_bilhete;
extern int m_qtdFilmes;
extern int m_qtdSalas;
extern int m_qtdProgramacoes;

int menuAdministrarVenda()
{

    int l_opcao = 0;
    changeView("Carregar Bilhetaria");
    viewExibirProgramacao("Bilheteria");

    printf("[0]  Sair e retornar para o menu anterior\n");
    printf("Selecione um codigo de programacao: ");
    getInteger(&l_opcao);
    switch (l_opcao)
    {
        case 0:
            changeView("Retornar para o menu anterior");
            return 0;
            break;

        default:
            menuAdministrarVendaIngressos(l_opcao);
            break;
    }
    return 0;
}

int viewCancelarBilhete()
{
    TTransacoes l_transacao;
    TBilhetes l_bilhete;
    int l_opcao = 0;
    changeView("Carregar Bilhetaria");
    header("Cancelar Bilhete");

    printf("[0]  Sair e retornar para o menu anterior\n");
    printf("Selecione um codigo do bilhete para cancelar: ");
    getInteger(&l_opcao);
    switch (l_opcao)
    {
        case 0:
            changeView("Retornar para o menu anterior");
            return 0;
            break;

        default:
            removerBilhete(l_opcao);
            break;
    }
    return 0;
}

int viewReimprimirBilhete()
{
    TTransacoes l_transacao;
    TBilhetes l_bilhete;
    int l_opcao = 0;
    changeView("Carregar Bilhetaria");
    header("Impressao Bilhete");

    printf("[0]  Sair e retornar para o menu anterior\n");
    printf("Selecione um codigo do bilhete: ");
    getInteger(&l_opcao);
    switch (l_opcao)
    {
        case 0:
            changeView("Retornar para o menu anterior");
            return 0;
            break;

        default:
            l_bilhete.id_bilhete = l_opcao;
            l_transacao = getTransacaoById(l_bilhete.id_bilhete);
            viewImprimirBilhete(l_transacao,l_bilhete);
            sleep(3);
            break;
    }
    return 0;
}

int menuAdministrarBilhete()
{
    while(INFINITO)
    {
        int l_opcao = 0;
        changeView("Carregar Bilheteria");
        header("Administrar Bilheteria");
        printf(">[1]  Reimprimir bilhete\n");
        printf(">[2]  Cancelar bilhete\n");
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
                viewReimprimirBilhete();
                break;

            case 2:
                loadProgramacaoes();
                viewCancelarBilhete();
                break;
            default:
                messageAlert(" OPCAO INVALIDA!!! FAVOR ESCOLHER UMA OPCAO VALIDA");
                break;
        }
    }
}


int menuAdministrarVendaIngressos(int p_IdProgramacao)
{

    char str_aux[50];
    TProgramacoes l_programacao;
    TTransacoes l_transacao;
    TBilhetes l_bilhete;


    l_programacao = getProgramacaoById(p_IdProgramacao);

    if(l_programacao.id_programacao != p_IdProgramacao)
    {
        messageAlert("Programação não encontrado");
    }
    printf("Digite a quantidade de ingressos..: ");
    getInteger(&l_transacao.qtd_ingressos);

    viewMarcarAssento(&l_transacao,&l_programacao);


    l_programacao.qtd_lugares = l_programacao.qtd_lugares - l_transacao.qtd_ingressos;
    if(l_programacao.qtd_lugares< 0)
    {
        messageAlert("Não há lugares disponíveis!");
        return ERRO;
    }

    //Tarifa
    viewGetTarifa();
    printf("[Escolha o modelo de tarifa] : ");
    getInteger(&l_transacao.id_tarifa);

    //Meio de pagamento
    viewGetFormaPagamento();
    getInteger(&l_transacao.id_forma);

    //calculando valor da transacao
    l_transacao.valor_transacao = getTarifaById(l_transacao.id_tarifa).valor * l_transacao.qtd_ingressos;

    clear();
    sprintf(str_aux, "\t\t\t$R$ %0.2f",l_transacao.valor_transacao);
    header(str_aux);
    printf("[O valor total igual a R$ %0.2f]: \n", l_transacao.valor_transacao);
    continuar();

    //debitando ingressos da quantidade lugares disponiveis
    l_programacao.qtd_lugares = l_programacao.qtd_lugares - l_transacao.qtd_ingressos;
    strcpy(l_transacao.data_transacao,systemDate());

    adicionarTransacao(&l_transacao);
    editarProgramacao(l_programacao);
    registrarAssentos(l_programacao);
    //imprimir bilhetes conforme qtd.
    for(int l_contador=0;l_contador<l_transacao.qtd_ingressos;l_contador++)
    {
        l_bilhete.id_transacao = l_transacao.id_transacao;
        adicionarBilhete(&l_bilhete);
        clear();
        viewImprimirBilhete(l_transacao, l_bilhete);
    }
    editarProgramacao(l_programacao);

    changeView("Compra efetuada com sucesso!");
    return SUCESSO;

}


int menuAdministrarBilhetaria()
{
    while(INFINITO)
    {
        int l_opcao = 0;
        changeView("Carregar Bilheteria");
        header("Administrar Bilheteria");
        printf(">[1]  Vender  - bilhetes\n");
        printf(">[2]  Administrar - bilhetes\n");
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
                menuAdministrarVenda();
                break;

            case 2:
                loadProgramacaoes();
                menuAdministrarBilhete();
                break;
            default:
                messageAlert(" OPCAO INVALIDA!!! FAVOR ESCOLHER UMA OPCAO VALIDA");
                break;
        }
    }
}

void viewMarcarAssento(TTransacoes* p_transacao, TProgramacoes* p_programacao)
{
    int l_linha=0;
    int l_coluna=0;
    char l_colunaAux[5];

    //Quantidade de lugares
    getLugaresByIdProgramacao(p_programacao->id_programacao);
    p_transacao->id_programacao = p_programacao->id_programacao;

    for(int l_contador=0;l_contador<p_transacao->qtd_ingressos;l_contador++)
    {
        viewExibirLugares(    p_transacao->id_programacao );
        printf("[Ingresso %d]\n", l_contador+1);
        printf("[Escolha o assento[Fileira][Numeros]: ");
        getInteger(&l_linha);
        m_bilhete.linha = l_linha;
        l_linha = l_linha -1 ;
        printf("[Escolha o assento[Cadeira][Letras]: ");
        getString(l_colunaAux);
        strcpy(m_bilhete.coluna,l_colunaAux);
        l_coluna = getValorColuna(l_colunaAux);
        m_lugares.posicao[l_linha][l_coluna] = 1;
    }

}

int viewImprimirBilhete(TTransacoes p_transacao, TBilhetes p_bilhete)
{

    TProgramacoes l_programacao = getProgramacaoById(p_transacao.id_programacao);

    changeView("Carregar Bilheteria");
    header("Administrar Bilheteria");

    printf("\t\t_________________________________________________________\n");
    printf("\t\t|\t\t\t\t\t\t\t|\n");
    printf("\t\t|\t\t CineXperience 2.0\t\t\t|\n");
    printf("\t\t|\t\t\t\t\t\t\t|\n");
    printf("\t\t| Numero Bilhete: %04d   Data Compra: %-18s|\n", p_bilhete.id_bilhete, p_transacao.data_transacao);
    printf("\t\t| Id Transacao..: %05d  Tarifa: %-23s|\n", p_transacao.id_transacao, getTarifaById(p_transacao.id_tarifa).descricao);
    printf("\t\t| Filme.........: %-36s  |\n", getFilmeById(l_programacao.id_filme).nome);
    printf("\t\t| Poltrona...: %d%s \t\t\t\t\t| \n", m_bilhete.linha,m_bilhete.coluna);
    printf("\t\t| Sessao...: %-5s Sala: %3d  \t\t\t\t|\n", getSessaoById(l_programacao.id_sessao).hora_inicio,l_programacao.id_sala);
    printf("\t\t|\t\t\t\t\t\t\t|\n");
    printf("\t\t---------------------------------------------------------\n");
    printf("\n\n");
    printf("Pressione ENTER para continuar");
    pressKey();

}
