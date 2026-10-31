#ifndef PARAMETROS_H
#define PARAMETROS_H

#include <stdbool.h>

typedef struct{
    int N; //numero de pessoas da cidade
    int P; //percentual de pessoas infectadas no dia 0;
    int L; //probabilidade de um infectado no estado 2 infectar um saudavel
    int K; //probabilidade (%) de um doente do estado 3 infectar um saudável (K > L);
    int F; //probabilidade (%) de um infectado (estado 2) desenvolver a doença;
    int M; //probabilidade (%) de um doente (estado 3) vir a óbito;
    int D; //duração da simulação, em dias;
    int R; //dia em que a vacina passa a ser distribuída;
    int Y; //a cada dia, a partir de R, são distribuídas N/Y vacinas.
}Parametros;

#endif