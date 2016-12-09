#ifndef ASSINATURAS_H_INCLUDED
#define ASSINATURAS_H_INCLUDED
#include "tipos.h"
//persistencia
struct filme getFilmeById(int p_FilmeId);
int getFloat(int *p_parametro);
int adicionarSala(struct sala pSala);
int editarSala(struct sala pSala);
int removerSala(int pSalaId);
int loadSalas();
int gerarIdSequenciaSala();
float getValorTransacaoByDate(char* p_data);

int adicionarSessao(struct horario pHorario);
int editarSessao(struct horario pHorario);
int removerSessao(int pHorarioId);
int loadSessoes();
TSessoes getSessaoById(int p_sessaoId);
int listHorariosByFilmeId(int pFilmeId);
int gerarIdSequenciaSessao();

int removerFilme(int pIdFilme);
int editarFilme(struct filme pFilme);
int adicionarFilme(struct filme pFilme);
int loadFilmes();
struct filme getFilmeById(int p_FilmeId);
int gerarIdSequenciaFilme();

int adicionarPreco(TTarifas p_tarifa);
int editarTarifa(TTarifas p_tarifa);
int removerTarifa(int p_tarifaId);
int loadTarifas();
TTarifas getTarifaById(int p_tarifaId);
int gerarIdSequenciaTarifa();



//utilitarios
const char* getfield(char* line, int num);
void pressKey();
void clear();
void header();
char* systemDate();
char* systemTime();
void changeView(char* pMensagem);
void header(char* pMensagem);
int bootStrap();
void messageInfo(char* mensagem);
void messageAlert(char* mensagem);
void messageError(char* mensagem, char* erro);
FILE* abrirArquivo(char pNomeArquivo[120], char pModo[2]);
int fecharArquivo(FILE* pFp);
int adicionarLinhaArquivo(FILE* pFp, char* pmLine);
void getInteger(int *p_IntegerParameter);


//menus
int menuAdministrarProgramacao();
int menuAdministrarFilmes();
int menuAdministrarSalas();
int menuAdministrarTarifas();
int menuAdministrarHorarios();
int menuAdministrarVenda();
int menuAdministrarVendaIngressos(int p_IdFilme);
int menuAdministrarBilhetaria();
int menuAdministrarSistema();
int menuPrincipal();

//view
int viewAdicionarFilme();
int viewAdicionarFilmeProgramacao();
int viewRemoverFilme();
int viewEditarFilme();
int viewExibirFilmes(char mensagem[50]);

int viewRemoverSessao();
int viewEditarHorario();
int viewAdicionarHorario();
int viewExibirHorarios(char mensagem[50]);

int viewRemoverTarifa();
int viewEditarTarifa();
int viewAdicionarTarifa();

int viewEditarSala();
int viewRemoverSala();
int viewAdicionarSala();
int viewExibirSalas(char mensagem[50]);

int viewExibirProgramacao(char* mensagem);


int getSizeRegistroTarifa();

int viewImprimirBilhete(TTransacoes p_transacao, TBilhetes p_bilhete);

int adicionarTransacao(TTransacoes* pTransacao);

int loadTransacoes();

struct transacao getTransacaoById(int pTransacaoId);
TSalas getSalaById(int p_SalaId);


int gerarIdSequenciaTransacao();



//geral
int loadProgramacaoes();
int removerProgramacao(int p_IdProgramacao);
TProgramacoes getProgramacaoById(int p_IdProgramacao);
int viewExibirLugares(int p_programacaoId);


void getString(char* p_StringParameter);



#endif // ASSINATURAS_H_INCLUDED
