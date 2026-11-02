#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "simulacao.h"
 
static uint32_t xorshift32(void) {
    static uint32_t state = 12345;
    uint32_t x = state;
 
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
 
    state = x;
    return x;
}
 
static int sorteia(int prob) {
    int valor_sorteado = (int)(xorshift32() % 100u);
    return valor_sorteado < prob;
}
 
struct simulacao {
    Parametros par;
    Lista *estado[5];
    Fila  *novosInfectados;
    Fila  *novosDoentes;
    Pilha *historico;
    int dia;
};
 
void simulacaoDestruir(Simulacao *s) {
    if (s == NULL)
        return;
 
    for (int i = 0; i < 5; i++)
        ListaLibera(s->estado[i]);
 
    FilaLibera(s->novosInfectados);
    FilaLibera(s->novosDoentes);
    PilhaLibera(s->historico);
    free(s);
}
 
Simulacao* simulacaoCriar(Parametros par) {
    Simulacao *s = calloc(1, sizeof(Simulacao));
    if (s == NULL)
        return NULL;
 
    s->par = par;
    s->dia = 0;
 
    for (int i = 0; i < 5; i++) {
        s->estado[i] = ListaInicia();
        if (s->estado[i] == NULL) {
            simulacaoDestruir(s);
            return NULL;
        }
    }
 
    s->novosInfectados = FilaInicia();
    s->novosDoentes    = FilaInicia();
    s->historico       = PilhaInicia();
 
    if (s->novosInfectados == NULL || s->novosDoentes == NULL || s->historico == NULL) {
        simulacaoDestruir(s);
        return NULL;
    }
 
    return s;
}
 
void mover(Simulacao *s, Pessoa *p, int de, int para) {
    setEstadoSaude(p, para);
    PilhaPush(s->historico, criarEvento(getIdPessoa(p), de, para, s->dia));
}
 
void simulacaoReiniciar(Simulacao *s, Pessoa **cidade) {
    Pessoa *p;
    Evento e;
 
    for (int i = 0; i < 5; i++)
        while (ListaRetiraPrimeiro(s->estado[i], &p));
 
    while (FilaDesenfileira(s->novosInfectados, &p));
    while (FilaDesenfileira(s->novosDoentes, &p));
    while (PilhaPop(s->historico, &e));
 
    for (int i = 0; i < s->par.N; i++) {
        setEstadoSaude(cidade[i], 1);
        ListaInsereInicio(s->estado[0], cidade[i]);
    }
 
    insertionSort(s->estado[0]);
    s->dia = 0;
}
 
void infectarInicial(Simulacao *s) {
    int qtd = s->par.N * s->par.P / 100;
    Pessoa *p;
 
    for (int i = 0; i < qtd; i++) {
        if (!ListaRetiraPrimeiro(s->estado[0], &p))
            break;
        ListaInsereInicio(s->estado[1], p);
        mover(s, p, 1, 2);
    }
}
 
void vacinar(Simulacao *s) {
    if (s->dia < s->par.R || s->par.Y <= 0)
        return;
 
    int qtd = s->par.N / s->par.Y;
    Pessoa *p;
 
    for (int i = 0; i < qtd; i++) {
        if (!ListaRetiraPrimeiro(s->estado[0], &p))
            break;
        ListaInsereInicio(s->estado[4], p);
        mover(s, p, 1, 5);
    }
}
 
void faseInfeccao(Simulacao *s, int origem, int prob) {
    Lista *aux = ListaInicia();
    Pessoa *p, *alvo;
    int tam = ListaTamanho(s->estado[origem]);
 
    for (int i = 0; i < tam; i++) {
        ListaRetiraPrimeiro(s->estado[origem], &p);
 
        if (!ListaEhVazia(s->estado[0]) && sorteia(prob)) {
            ListaRetiraPrimeiro(s->estado[0], &alvo);
            FilaEnfileira(s->novosInfectados, alvo);
            mover(s, alvo, 1, 2);
        }
 
        ListaInsereInicio(aux, p);
    }
 
    while (ListaRetiraPrimeiro(aux, &p))
        ListaInsereInicio(s->estado[origem], p);
 
    ListaLibera(aux);
}
 
void faseEvolucaoInfectados(Simulacao *s) {
    Pessoa *p;
    int tam = ListaTamanho(s->estado[1]);
 
    for (int i = 0; i < tam; i++) {
        ListaRetiraPrimeiro(s->estado[1], &p);
 
        if (sorteia(s->par.F)) {
            FilaEnfileira(s->novosDoentes, p);
            mover(s, p, 2, 3);
        } else {
            ListaInsereInicio(s->estado[0], p);
            mover(s, p, 2, 1);
        }
    }
}
 
void faseEvolucaoDoentes(Simulacao *s) {
    Pessoa *p;
    int tam = ListaTamanho(s->estado[2]);
 
    for (int i = 0; i < tam; i++) {
        ListaRetiraPrimeiro(s->estado[2], &p);
 
        if (sorteia(s->par.M)) {
            ListaInsereInicio(s->estado[3], p);
            mover(s, p, 3, 4);
        } else {
            ListaInsereInicio(s->estado[0], p);
            mover(s, p, 3, 1);
        }
    }
}
 
void fimDoDia(Simulacao *s) {
    Pessoa *p;
 
    while (FilaDesenfileira(s->novosInfectados, &p))
        ListaInsereInicio(s->estado[1], p);
 
    while (FilaDesenfileira(s->novosDoentes, &p))
        ListaInsereInicio(s->estado[2], p);
 
    insertionSort(s->estado[0]);
}
 
void simularDia(Simulacao *s) {
    vacinar(s);
    faseInfeccao(s, 1, s->par.L);
    faseInfeccao(s, 2, s->par.K);
    faseEvolucaoInfectados(s);
    faseEvolucaoDoentes(s);
    fimDoDia(s);
    s->dia++;
}
 
void simulacaoRodar(Simulacao *s) {
    infectarInicial(s);
 
    for (int d = 0; d < s->par.D; d++)
        simularDia(s);
}
 
void percentuais(const Simulacao *s, double out[5]) {
    for (int i = 0; i < 5; i++)
        out[i] = 100.0 * ListaTamanho(s->estado[i]) / s->par.N;
}
 
Parametros lerParametros(void) {
    Parametros p = {0, 0, 0, 0, 0, 0, 0, 0, 0};
 
    scanf("%d %d %d %d %d %d %d %d %d", &p.N, &p.P, &p.L, &p.K, &p.F, &p.M, &p.D, &p.R, &p.Y);
 
    return p;
}
 
Pessoa** lerPessoas(int n) {
    if (n <= 0)
        return NULL;
 
    Pessoa **pessoas = malloc(n * sizeof(Pessoa*));
    if (pessoas == NULL)
        return NULL;
 
    char nome[100];
    int id, idade;
 
    for (int i = 0; i < n; i++) {
        scanf("%99s %d %d", nome, &id, &idade);
 
        pessoas[i] = criaPessoa(id, nome, idade, 1);
        if (pessoas[i] == NULL) {
            liberarPessoas(pessoas, i);
            return NULL;
        }
    }
 
    return pessoas;
}
 
void liberarPessoas(Pessoa **cidade, int n) {
    if (cidade == NULL)
        return;
 
    for (int i = 0; i < n; i++)
        destroiPessoa(cidade[i]);
 
    free(cidade);
}
 
void simulacaoExecutar(Parametros parametros, Pessoa **cidade, int rep, double media[5]) {
    double atual[5];
 
    for (int i = 0; i < 5; i++)
        media[i] = 0.0;
 
    Simulacao *s = simulacaoCriar(parametros);
    if (s == NULL || rep <= 0)
        return;
 
    for (int r = 0; r < rep; r++) {
        simulacaoReiniciar(s, cidade);
        simulacaoRodar(s);
        percentuais(s, atual);
 
        for (int i = 0; i < 5; i++)
            media[i] += atual[i];
    }
 
    for (int i = 0; i < 5; i++)
        media[i] /= rep;
 
    simulacaoDestruir(s);
}
 