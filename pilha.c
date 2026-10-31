#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

struct evento {
    int idPessoa;
    int estadoAnterior; 
    int novoEstado;
    int diaOcorrencia;
};

struct celula {
    Evento evento;
    struct celula *prox;
};

struct pilha {
    struct celula *cab;
    int n; // numero de elementos na pilha
};

Pilha* PilhaInicia() {
    Pilha *pPilha = malloc(sizeof(Pilha));

    if (pPilha == NULL)
        return NULL;

    pPilha->cab = NULL;

    return pPilha;
}

bool PilhaEhVazia(Pilha *pPilha) { 
    return pPilha == NULL || pPilha->cab == NULL;
}

bool PilhaPush(Pilha *pPilha, Evento evento) {
    if (pPilha == NULL)
        return false;

    struct celula *nova = malloc(sizeof(struct celula));
    if (nova == NULL)
        return false;

    nova->evento = evento;
    nova->prox = pPilha->cab;
    pPilha->cab = nova;

    return true;
}

bool PilhaPop(Pilha *pPilha, Evento *pEvento) {
    if (pPilha == NULL || pPilha->cab == NULL)
        return false;

    struct celula *aux = pPilha->cab;
    *pEvento = aux->evento;
    pPilha->cab = aux->prox;
    free(aux);

    return true;
}


Pilha* PilhaLibera(Pilha *pPilha) {
    if (pPilha == NULL)
        return NULL;

    ListaLibera(pPilha->cab);
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
        Evento eventoVazio = {0, 0, 0, 0}; // Retorna um evento vazio em caso de pilha vazia
        return eventoVazio;
    }

    return pPilha->cab->evento;
}