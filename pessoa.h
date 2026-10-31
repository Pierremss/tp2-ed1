#ifndef PESSOA_H
#define PESSOA_H

#include <stdbool.h>
#include <string.h>

typedef struct pessoa Pessoa;

int getIdPessoa(Pessoa *p);
char* getNome(Pessoa *p);
bool setNome(Pessoa *p, char* nome);
int getIdade(Pessoa *p);
bool setIdade(Pessoa *p, int idade);
int getEstadoSaude(Pessoa *p);
bool setEstadoSaude(Pessoa *p, int estadoSaude);
Pessoa* criaPessoa(int id, char* nome, int idade, int estadoSaude);
Pessoa* destroiPessoa(Pessoa *p);
bool quemEhMaisVelho(Pessoa *p1, Pessoa *p2); //retorna true se p1 for mais velho que p2


#endif
