#ifndef ESTADIA_H
#define ESTADIA_H

typedef struct {
    int codigoEstadia;
    int codigoCliente;
    int numeroQuarto;
    char dataEntrada[11];
    char dataSaida[11];
    int quantidadeDiarias;
} Estadia;

void cadastrarEstadia();
void mostrarEstadiasCliente();
void darBaixaEstadia();

int calcularPontos(int codigoCliente);

#endif