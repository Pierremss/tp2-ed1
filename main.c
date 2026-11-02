#include <stdio.h>
#include "simulacao.h"

int main() {
    Parametros parametros = lerParametros();
    Pessoa **cidade = lerPessoas(parametros.N);
    if (cidade == NULL) 
      return 1;

    double media[5];
    simulacaoExecutar(parametros, cidade, 10, media);  

    for (int i = 0; i < 5; i++)
        printf("Estado %d: %.2f%%\n", i, media[i]);

    liberarPessoas(cidade, parametros.N);
    return 0;
}


