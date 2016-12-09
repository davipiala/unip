#include <stdio.h>
#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

//contantes base
#define FILMES_SEQ "persistencia/filmes.seq"
#define SALAS_SEQ "persistencia/salas.seq"
#define SESSOES_SEQ "persistencia/sessoes.seq"
#define TARIFAS_SEQ "persistencia/precos.seq"
#define TRANSACAO_SEQ "persistencia/transacoes.seq"
#define PROGRAMACOES_SEQ "persistencia/programacoes.seq"
#define FORMAPAGAMENTOS_SEQ "persistencia/formapagamentos.seq"
#define BILHETES_SEQ "persistencia/bilhetes.seq"

#define LUGARES_FILE "persistencia/lugares"
#define FILMES_FILE "persistencia/filmes.csv"
#define SALAS_FILE  "persistencia/salas.csv"
#define TARIFAS_FILE "persistencia/precos.csv"
#define PROGRAMACOES_FILE "persistencia/programacoes.csv"
#define SESSOES_FILE "persistencia/sessoes.csv"
#define TRANSACAO_FILE "persistencia/transacoes.csv"
#define BILHETES_FILE "persistencia/bilhetes.csv"
#define FORMAPAGAMENTOS_FILE "persistencia/formapagamentos.csv"

#define TMP_FILE "persistencia/temporary.tmp"
#define ESCAPE_ZERO '\0'


#define LIMPAR_TELA "\33[H\33[2J"

//modos de abertura de arquivos
#define MODO_LEITURA "r"
#define MODO_ESCRITA "r+"

//Tipificacao de erros
#define SUCESSO 1
#define ERRO 0
#define INFINITO 1


#endif // CONSTANTES_H_INCLUDED
