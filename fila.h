#ifndef FILA_H
#define FILA_H

#include "lista.h"

typedef struct fila Fila;

Fila* FilaInicia();
bool FilaEnfileira(Fila *pFila, Pessoa *pessoa);
bool FilaDesenfileira(Fila *pFila, Pessoa **pPessoa);
bool FilaEhVazia(Fila *pFila);
Fila* FilaLibera(Fila *pFila);

#endif 