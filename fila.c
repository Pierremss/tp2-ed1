#include "fila.h"
#include <stdlib.h>


struct fila {
    Lista *lista;
};

Fila* FilaInicia() {
    Fila *pFila = malloc(sizeof(Fila));

    if (pFila == NULL)
        return NULL;

    pFila->lista = ListaInicia();

    if (pFila->lista == NULL) {
        free(pFila);
        return NULL;
    }

    return pFila;
}

bool FilaEnfileira(Fila *pFila, Pessoa *pessoa) {
    if (pFila == NULL)
        return false;

    return ListaInsereFinal(pFila->lista, pessoa);
}

bool FilaDesenfileira(Fila *pFila, Pessoa **pPessoa) {
    if (pFila == NULL)
        return false;

    return ListaRetiraPrimeiro(pFila->lista, pPessoa);
}

bool FilaEhVazia(Fila *pFila) {
    return pFila == NULL || ListaEhVazia(pFila->lista);
}

Fila* FilaLibera(Fila *pFila) {
    if (pFila == NULL)
        return NULL;

    ListaLibera(pFila->lista);
    free(pFila);

    return NULL;
}
