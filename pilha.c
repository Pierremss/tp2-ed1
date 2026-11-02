#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>


struct celulaPilha {
    Evento evento;
    struct celulaPilha *prox;
};

struct pilha {
    struct celulaPilha *cab;
    int n; // numero de elementos na pilha
};

Pilha* PilhaInicia() {
    Pilha *pPilha = malloc(sizeof(Pilha));

    if (pPilha == NULL)
        return NULL;

    pPilha->cab = NULL;
    pPilha->n = 0;

    return pPilha;
}

bool PilhaEhVazia(Pilha *pPilha) { 
    return pPilha == NULL || pPilha->cab == NULL;
}

bool PilhaPush(Pilha *pPilha, Evento evento) {
    if (pPilha == NULL)
        return false;

    struct celulaPilha *nova = malloc(sizeof(struct celulaPilha));
    if (nova == NULL)
        return false;

    nova->evento = evento;
    nova->prox = pPilha->cab;
    pPilha->cab = nova;
    pPilha->n++;
    return true;
}

bool PilhaPop(Pilha *pPilha, Evento *pEvento) {
    if (pPilha == NULL || pPilha->cab == NULL)
        return false;

    struct celulaPilha *aux = pPilha->cab;
    *pEvento = aux->evento;
    pPilha->cab = aux->prox;
    free(aux);
    pPilha->n--;
    return true;
}


Pilha* PilhaLibera(Pilha *pPilha) {
    Evento e;
    while (PilhaPop(pPilha, &e));
    free(pPilha);

    return NULL;
}

Evento criarEvento(int idPessoa, int estadoAnterior, int novoEstado, int diaOcorrencia) {
    Evento evento;
    evento.idPessoa = idPessoa;
    evento.estadoAnterior = estadoAnterior;
    evento.novoEstado = novoEstado;
    evento.diaOcorrencia = diaOcorrencia;
    return evento;
}

int consultarIdPessoa(Evento *evento) {
    return evento->idPessoa;
}

int consultarEstadoAnterior(Evento *evento) {
    return evento->estadoAnterior;
}

int consultarNovoEstado(Evento *evento) {
    return evento->novoEstado;
}

int consultarDia(Evento *evento) {
    return evento->diaOcorrencia;
}


Evento consultarTopo(Pilha *pPilha) {
    if (pPilha == NULL || pPilha->cab == NULL) {
        Evento eventoVazio = {0, 0, 0, 0}; 
        return eventoVazio;
    }

    return pPilha->cab->evento;
}