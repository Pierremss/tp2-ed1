#ifndef SIMULACAO_H
#define SIMULACAO_H

#include <stdbool.h>
#include <stdint.h>
#include "parametros.h"
#include "pessoa.h"
#include "lista.h"
#include "fila.h"
#include "pilha.h"
#include "ordenacao.h"

typedef struct simulacao Simulacao;
 
Parametros lerParametros();
Pessoa** lerPessoas(int n);
void liberarPessoas(Pessoa **cidade, int n);
void simulacaoExecutar(Parametros parametros, Pessoa **cidade, int rep, double media[5]);
void simulacaoDestruir(Simulacao *s);
Simulacao* simulacaoCriar(Parametros parametros);
void simulacaoReiniciar(Simulacao *s, Pessoa **cidade);
void infeccaoInicial(Simulacao *simulacao);
void vacinar(Simulacao *s);
void faseInfeccao(Simulacao *s, int origem, int prob);
void faseEvolucaoInfectados(Simulacao *s);
void faseEvolucaoDoentes(Simulacao *s);
void fimDoDia(Simulacao *s);
void simularDia(Simulacao *s);
void simulacaoRodar(Simulacao *s);
void percentuais(const Simulacao *s, double out[5]);


#endif