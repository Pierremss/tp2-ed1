#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct celula {
    Pessoa *pessoa;
    struct celula *prox;
} Celula;

struct lista {
    int n; // numero de elementos na lista
    Celula *cab;
    Celula *ult;
};

Lista* ListaInicia() {
    Lista *pLista = malloc(sizeof(Lista));

    if (pLista == NULL)
        return NULL;

    pLista->cab = malloc(sizeof(Celula));

    if (pLista->cab == NULL) {
        free(pLista);
        return NULL;
    }

    pLista->cab->prox = NULL;
    pLista->ult = pLista->cab;
    pLista->n = 0;

    return pLista;
}

bool ListaInsereFinal(Lista *pLista, Pessoa *pessoa) {
    if (pLista == NULL)
        return false;

    Celula *nova = malloc(sizeof(Celula));

    if (nova == NULL)
        return false;

    nova->pessoa = pessoa;
    nova->prox = NULL;

    pLista->ult->prox = nova;
    pLista->ult = nova;
    pLista->n++;

    return true;
}

bool ListaInsereInicio(Lista *pLista, Pessoa *pessoa) {
    if (pLista == NULL)
        return false;

    Celula *nova = malloc(sizeof(Celula));

    if (nova == NULL)
        return false;

    nova->pessoa = pessoa;
    nova->prox = pLista->cab->prox;
    pLista->cab->prox = nova;

    if (pLista->n == 0)
        pLista->ult = nova;

    pLista->n++;

    return true;
}

bool ListaRetiraPrimeiro(Lista *pLista, Pessoa **pPessoa) {
    if (ListaEhVazia(pLista) || pPessoa == NULL)
        return false;

    Celula *aux = pLista->cab->prox;

    *pPessoa = aux->pessoa;
    pLista->cab->prox = aux->prox;

    if (pLista->ult == aux)
        pLista->ult = pLista->cab;

    free(aux);
    pLista->n--;

    return true;
}

bool ListaEhVazia(Lista *pLista) {
    return pLista == NULL || pLista->n == 0;
}

int ListaTamanho(Lista *pLista) {
    return pLista->n;
}

void ImprimirLista(Lista *pLista, Pessoa *pPessoa) {
    Celula *atual = pLista->cab->prox;

    while (atual != NULL) {
        printf("%d\n", getIdPessoa(atual->pessoa));
        printf("%s\n", getNome(atual->pessoa));
        printf("%d\n", getIdade(atual->pessoa));
        printf("%d\n", getEstadoSaude(atual->pessoa));
        atual = atual->prox;
    }

}

Lista* ListaLibera(Lista *pLista) {
    if (pLista == NULL)
        return NULL;

    Pessoa *pessoa;

    while (!ListaEhVazia(pLista))
        ListaRetiraPrimeiro(pLista, &pessoa);

    free(pLista->cab);
    free(pLista);

    return NULL;
}
