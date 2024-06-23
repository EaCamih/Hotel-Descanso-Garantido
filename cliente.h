#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct {
    int codigo;
    char nome[100];
    char endereco[200];
    char telefone[15];
} Cliente;

void cadastrarCliente();
void pesquisarCliente();

#endif