#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "persistencia.h"
#include "utilitarios.h"
#include "apresentacao.h"
#include "globais.h"
#include "constantes.h"


extern int mQtdmFilmes;
extern int mQtdmSalas;
extern int mQtdmPrecos;
extern int mQtdmHorarios;


int adicionarSala(struct sala pSala) {

    FILE* fp = loadFile(SALAS_FILE,MODO_ESCRITA);
    if(fp)
    {
        char* linha= "";
        linha = malloc(1024+1+4);
        sprintf(linha, "%d;%d"
        ,gerarIdSequenciaSala()
        ,pSala.capacidade);

        adicionarLinhaArquivo(fp,linha);
        fecharArquivo(fp);
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;
}

int editarSala(struct sala pSala) {

    char line[1024];
    FILE* fp = loadFile(SALAS_FILE,MODO_ESCRITA);
    FILE* fpAux = fopen("copy.c", "w");

    if(fp)
    {
        while (fgets(line, 1024, fp))
        {

            if(pSala.id_sala == atoi(getfield(strdup(line), 1)))
            {
                char* linha= "";
                linha = malloc(1024+1+4);
                sprintf(linha, "%d", gerarIdSequenciaSala());
                linha = strcat(linha,";");
                linha = strcat(linha,strcat(pSala.capacidade,";"));
                fputs(linha, fpAux);
                continue;
            }
            fputs(line, fpAux);
            memset( line, '\0', sizeof(line) );

        }
        fclose(fp);
        fclose(fpAux);
        remove(SALAS_FILE);
        rename("copy.c", SALAS_FILE);
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;
}

int removerSala(int pSalaId) {

    char line[1024];
    int excluido = 0;
    FILE* fp = loadFile(SALAS_FILE,MODO_ESCRITA);
    FILE* fpAux = fopen("copy.c", "w");

    if(fp)
    {
        while (fgets(line, 1024, fp))
        {

            if(pSalaId==atoi(getfield(strdup(line), 1)))
            {
                excluido = 1;
                continue;

            }
            fputs(line, fpAux);
            memset( line, '\0', sizeof(line) );

        }
        fclose(fp);
        fclose(fpAux);
        remove(SALAS_FILE);
        rename("copy.c", SALAS_FILE);
    }
    else
    {
        return ERRO;
    }
    return SUCESSO;
}


int loadSalas()
{
    fflush(stdin);

    char line[1024];
    int count=0;
    FILE* fp = loadFile(SALAS_FILE,MODO_LEITURA);
    if(fp)
    {
        while (fgets(line, 1024, fp))
        {
            if(count == 0)
            {
                count++;
                continue;
            }
            mSalas[count].id_sala = atoi(getfield(strdup(line), 1));
            mSalas[count].capacidade = atoi(getfield(strdup(line), 2));

            count++;
            memset( line, '\0', sizeof(line) );

        }
        fecharArquivo(fp);
        mQtdmSalas = count;

    }
    else
    {
        return ERRO;
    }
    return SUCESSO;

}



