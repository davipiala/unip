#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "colors.h"
#include "constantes.h"

int getFloat(int *p_parametro)
{
    scanf("%f",p_parametro);
    dumpLine(stdin);
}

int getInteger(int *p_parametro)
{
    scanf("%d",p_parametro);
    dumpLine(stdin);
}

void getString(char* p_StringParameter)
{
    gets(p_StringParameter);

}

const char* getfield(char* line, int num)
{
	const char* tok;
	for (tok = strtok(line, ";");
			tok && *tok;
			tok = strtok(NULL, ";\n")) {
		if (!--num)
			return tok;
	}
	return NULL;
}

int clear()
{
    printf(LIMPAR_TELA);
}

void pressKey()
{
    getchar();
}

char* systemDate()
{
    char* l_data;
    l_data = calloc(1,13);


    time_t t;
    struct tm* tmp;
    t = time(NULL);
    tmp = localtime(&t);

    strftime(l_data, 13, "%d-%m-%Y", tmp);

    return l_data;

}

char* systemTime()
{
    return __TIME__;
}

void changeView(char* p_mensagem)
{
    clear();
    printf("________________________________________________________________________________\n");
    printf("| \t\t\t\t%s\t\t\t\t|\n",p_mensagem);
    printf("________________________________________________________________________________\n");
    sleep(1);
    clear();
}
void header(char* p_mensagem)
{
    printf("________________________________________________________________________________\n");
    printf("| \t\t\tCineXperience 2.0\t\t\t\t\t|\n");
    printf("| \tData: %s Horas: %s\t\t\t\t\t|\n",systemDate(), systemTime());
    printf("| \tTela %s\t\t\t\t\t\t\t|\n",p_mensagem);
    printf("________________________________________________________________________________\n");
}

int bootStrap()
{

    printf("________________________________________________________________________________\n");
    printf("| \t\t\tCineXperience 2.0\t\t\t\t\t|\n");
    printf("| \tData: %s Horas: %s\t\t\t\t\t|\n",systemDate(), systemTime());
    printf("| \t\t\tInicializando o sitema\n");
    printf("________________________________________________________________________________\n");

    sleep(1);
    printf("________________________________________________________________________________\n");
    printf("| \t\t\tVerificando base de dados");
    printf("________________________________________________________________________________\n");

    clear();
    if(loadFilmes() == ERRO)
    {
        messageError("FALHA AO CARREGAR ARQUIVO Filmes","ERRO01");
        pressKey();
        return ERRO;
    }

    if(loadSalas() == ERRO)
    {
        messageError("FALHA AO CARREGAR ARQUIVO Salas","ERRO02");
        pressKey();
        return ERRO;
    }

    if(loadTarifas() == ERRO)
    {
        messageError("FALHA AO CARREGAR ARQUIVO Tarifas","ERRO03");
        pressKey();
        return ERRO;
    }
    if(loadSessoes() == ERRO)
    {
        messageError("FALHA AO CARREGAR ARQUIVO Horarios","ERRO04");
        pressKey();
        return ERRO;
    }
    if(loadSessoes() == ERRO)
    {
        messageError("FALHA AO CARREGAR ARQUIVO Relacionamentos","ERRO05");
        pressKey();
        return ERRO;
    }
    changeView("Sistema carregado");
    return SUCESSO;
}

int continuar(m)
{
    char l_continuar[2];
    fflush(stdin);
    printf("Continuar [s/N]?:");
    getString(l_continuar);
    if(strcmp(l_continuar,"s")==0)
    {
        return 1;
    }
    return 0;
}


void messageInfo(char* p_mensagem)
{
    printf("%s\n",p_mensagem);
}
void messageAlert(char* p_mensagem)
{
    sleep(1);
    clear();
    printf("________________________________________________________________________________\n");
    printf("| \t\t%s\t\t\t\t|\n",p_mensagem);
    printf("________________________________________________________________________________\n");

    pressKey();
}
void messageError(char* p_mensagem, char* p_erro)
{
    printf("________________________________________________________________________________\n");
    printf("| \t\t%s - %s |\n",p_erro);
    printf("________________________________________________________________________________\n");
    printf("|\t\tContate o administrador\n\n");
    printf("|\t\tPressione ENTER para SAIR da aplicacao\n\n");
    sleep(2);
    pressKey();


}


FILE* abrirArquivo(char p_nomeArquivo[120], char p_modo[2])
{
    FILE* lFp = fopen(p_nomeArquivo, p_modo);
    return lFp;
}

int fecharArquivo(FILE* p_arquivo){
    fclose(p_arquivo);
}

int adicionarLinhaArquivo( char* p_linhaRegistro, FILE* p_arquivo)
{
    fputs(p_linhaRegistro, p_arquivo);
}
void descartarHeader(FILE* p_arquivo, short p_tamanho)
{
    char* l_registroLinha;
    l_registroLinha = calloc(1,p_tamanho);
    fgets(l_registroLinha,p_tamanho, p_arquivo);
    free(l_registroLinha);

}
void posicionarFimArquivo(FILE* p_arquivo)
{
    fseek(p_arquivo, 0, SEEK_END) ;
}
void posicionarInicioArquivo(FILE* p_arquivo)
{
    fseek(p_arquivo, 0, SEEK_SET) ;
}

char* getNomeColuna(int p_coluna)
{
    char *l_nomeColuna;
    l_nomeColuna = calloc(1,5);
    l_nomeColuna = "";

    switch (p_coluna)
    {
        case 0:
            l_nomeColuna = "A";
            break;
        case 1:
            l_nomeColuna = "B";
            break;
        case 2:
            l_nomeColuna = "C";
            break;
        case 3:
            l_nomeColuna = "D";
            break;
        case 4:
            l_nomeColuna = "E";
            break;
        case 5:
            l_nomeColuna = "F";
            break;
        case 6:
            l_nomeColuna = "G";
            break;
        case 7:
            l_nomeColuna = "H";
            break;
        case 8:
            l_nomeColuna = "I";
            break;
        case 9:
            l_nomeColuna = "J";
            break;
        case 10:
            l_nomeColuna = "L";
            break;
        case 11:
            l_nomeColuna = "M";
            break;
        default:
            break;
    }
    return l_nomeColuna;


}


int getValorColuna(char p_nomeColuna[5])
{
    int l_valorColuna = 0;

    if(strcmp(p_nomeColuna,"A")==0)
    {
        l_valorColuna = 0;
    }

    if(strcmp(p_nomeColuna,"B")==0)
    {
        l_valorColuna = 1;
    }

    if(strcmp(p_nomeColuna,"C")==0)
    {
        l_valorColuna = 2;
    }

    if(strcmp(p_nomeColuna,"D")==0)
    {
        l_valorColuna = 3;
    }

    if(strcmp(p_nomeColuna,"E")==0)
    {
        l_valorColuna = 4;
    }

    if(strcmp(p_nomeColuna,"F")==0)
    {
        l_valorColuna = 5;
    }

    if(strcmp(p_nomeColuna,"G")==0)
    {
        l_valorColuna = 6;
    }

    if(strcmp(p_nomeColuna,"H")==0)
    {
        l_valorColuna = 7;
    }

    if(strcmp(p_nomeColuna,"I")==0)
    {
        l_valorColuna = 8;
    }

    if(strcmp(p_nomeColuna,"J")==0)
    {
        l_valorColuna = 9;
    }

    if(strcmp(p_nomeColuna,"L")==0)
    {
        l_valorColuna = 10;
    }

    return l_valorColuna;


}


void dumpLine( FILE * fp )
{
  int ch;

  while( (ch = fgetc(fp)) != EOF && ch != '\n' )
    /* null body */;
}





