#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include "pessoa.h"

typedef struct lista Lista;

Lista* ListaInicia();
bool ListaInsereFinal(Lista *pLista, Pessoa *pessoa);
bool ListaInsereInicio(Lista *pLista, Pessoa *pessoa);
bool ListaRetiraPrimeiro(Lista *pLista, Pessoa **pPessoa);
bool ListaEhVazia(Lista *pLista);
int ListaTamanho(Lista *pLista);
void ImprimirLista(Lista *pLista);
Lista* ListaLibera(Lista *pLista);

#endif
