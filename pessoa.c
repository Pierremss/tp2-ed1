#include <stdio.h>
#include <stdlib.h>
#include "pessoa.h"

 struct pessoa{
    int id;
    char nome[100];
    int idade;
    int estadoSaude; //1-saudavel, 2-infectado que nao desenvolveu a doenca, 3-infectado que desenvolveu a doenca, 4-faleceu, 5-imunizado pela vacina
};

Pessoa* criaPessoa(int id, char* nome, int idade, int estadoSaude){
    if(nome == NULL || idade < 0 || (estadoSaude < 0 || estadoSaude > 5))
        return NULL;

    Pessoa *p = (Pessoa*) malloc(sizeof(Pessoa));
    if(p == NULL)
        return NULL;

    p->id = id;
    strcpy(p->nome, nome);
    p->idade = idade;
    p->estadoSaude = estadoSaude;

    return p;
}

Pessoa* destroiPessoa(Pessoa *p){
    if(p == NULL)
        return NULL;

    free(p);
    return NULL;
}

int getIdPessoa(Pessoa *p){
    if(p == NULL)
        return -1;
    return p->id;
}

char* getNome(Pessoa *p){
    if(p == NULL)
        return NULL;

    return p->nome;
}

bool setNome(Pessoa *p, char *nome){
    if(p == NULL || nome == NULL)
        return false;

    strcpy(p->nome, nome);
    return true;
}

int getIdade(Pessoa *p){
    if(p == NULL)
        return -1;

    return p->idade;
}

bool setIdade(Pessoa *p, int idade){
    if(p == NULL || idade < 0)
        return false;

    p->idade = idade;
    return true;
}

int getEstadoSaude(Pessoa *p){
    if(p == NULL)
        return -1;

    return p->estadoSaude;
}

bool setEstadoSaude(Pessoa *p, int estadoSaude){
    if(p == NULL || (estadoSaude < 0 || estadoSaude > 5))
        return false;

    p->estadoSaude = estadoSaude;
    return true;
}

bool quemEhMaisVelho(Pessoa *p1, Pessoa *p2){
    if(p1 == NULL || p2 == NULL)
        return false;

    if (p1->idade != p2->idade) 
        return p1->idade > p2->idade;
        
    return p1->id < p2->id;

}