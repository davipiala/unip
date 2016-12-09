#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utilitarios.h"
#include "apresentacao.h"
#include "globais.h"
#include "constantes.h"
#include "colors.h"

int main ()
{
    clear();
    if(bootStrap()==ERRO)
    {
        return ERRO;

    }
	menuPrincipal();
    return 0;
}
