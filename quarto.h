#ifndef QUARTO_H
#define QUARTO_H

typedef struct {
    int numero;
    int capacidade;
    double valorDiaria;
    char status[10];
} Quarto;

void cadastrarQuarto();
void atualizarStatus(int numero, const char* status);

#endif