#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>
#include "lista.h"

typedef struct pilha Pilha;
typedef struct evento Evento;
typedef struct celulaPilha CelulaPilha;

struct evento {
    int idPessoa;
    int estadoAnterior; 
    int novoEstado;
    int diaOcorrencia;
};

Pilha* PilhaInicia();
bool PilhaPush(Pilha *pPilha, Evento evento); //adiciona uma pessoa na pilha
bool PilhaPop(Pilha *pPilha, Evento *pEvento); //remove uma pessoa da pilha
bool PilhaEhVazia(Pilha *pPilha);
Pilha* PilhaLibera(Pilha *pPilha);

Evento criarEvento(int idPessoa, int estadoAnterior, int novoEstado, int diaOcorrencia);
int consultarIdPessoa(Evento *evento);
int consultarEstadoAnterior(Evento *evento);
int consultarNovoEstado(Evento *evento);
int consultarDia(Evento *evento);
Evento consultarTopo(Pilha *pPilha); //retorna o evento do topo da pilha sem removê-lo

#endif