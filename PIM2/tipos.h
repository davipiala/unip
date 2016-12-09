#ifndef TIPOS_H_INCLUDED
#define TIPOS_H_INCLUDED

typedef struct filme
{
	unsigned short id_filme;
	char nome[50];
	char descricao[50];
	char data_cadastro[11];
	char diretor[50];
	char sinopse[200];
	unsigned short classificacao;
} TFilmes;

typedef struct forma_pagamento
{
	unsigned short id_forma;
	char descricao[25];
}TFormaPagamentos;

typedef struct bilhete
{
    long id_bilhete;
    long id_transacao;
    int linha;
    char coluna[2];

} TBilhetes;

typedef struct tarifas
{
	unsigned short id_tarifa;
	char descricao[50];
	float valor;
}TTarifas;

typedef struct sessao
{
    unsigned short id_sessao;
	char hora_inicio[6];
}TSessoes;


typedef struct sala
{
	unsigned short id_sala;
	unsigned short capacidade;
	unsigned short qtd_linhas;
	unsigned short qtd_colunas;
}TSalas;

typedef struct lugares
{
	int posicao[20][20];
}TLugares;

typedef struct programacao
{
    long id_programacao;
    unsigned short id_sala;
    unsigned short id_sessao;
    long id_filme;
    unsigned short qtd_lugares;
}TProgramacoes;

typedef struct transacao
{
    long id_transacao;
    long id_programacao;
    char data_transacao[11];
    unsigned short qtd_ingressos;
    float valor_transacao;
    int id_forma;
    int id_tarifa;

}TTransacoes;
#endif // TIPOS_H_INCLUDED
