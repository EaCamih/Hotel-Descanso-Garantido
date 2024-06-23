#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

typedef struct {
    int codigo;
    char nome [100];
    char endereco[200];
    char telefone[15];
    char cargo[50];
    double salario;
} Funcionario;

void cadastrarFuncionario();
void pesquisarFuncionario();

#endif