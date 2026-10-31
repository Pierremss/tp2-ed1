#include "ordenacao.h"
#include "pessoa.h"
#include "lista.h"

// void insertionSort(Lista *pLista){ //ta muito errado ainda
//     int n = ListaTamanho(pLista), j;
//     Celula *aux = pLista->cab;
//     for (int i = 0; i < n; i++){
//          aux = aux->prox;
//         j = i - 1;
//         while(j >= 0 && quemEhMaisVelho(aux, pLista[j])){ //quem eh mais velho fica na frente
//             j--;
//             pLista[j + 1] = pLista[j];
//         }
//         pLista[j + 1] = aux;
//     }
// }