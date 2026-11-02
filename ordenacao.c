#include "ordenacao.h"
#include "pessoa.h"
#include "lista.h"
#include <stdlib.h>

void insertionSort(Lista *pLista){ 
    int n = ListaTamanho(pLista);

    if (n <= 1)
        return; 

    Pessoa **v = malloc(n * sizeof(Pessoa*));
    if (v == NULL)
        return; //vendo se o malloc deu certo;

    for(int i = 0; i < n; i++)
        ListaRetiraPrimeiro(pLista, &v[i]); //vou passar pra um vetor auxiliar 

    for(int i = 1; i < n; i++){ //ordenando o vetor auxiliar
        Pessoa *maisVelho = v[i];
        int j = i - 1;
        while (j >= 0 && quemEhMaisVelho(maisVelho, v[j])){
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = maisVelho;
    }

    for(int i = 0; i < n; i++)
        ListaInsereFinal(pLista, v[i]);

    free(v);
    
}