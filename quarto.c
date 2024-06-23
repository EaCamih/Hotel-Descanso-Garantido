#include "quarto.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cadastrarQuarto() {
    FILE *file = fopen("quartos.bin", "ab");
    if(!file) {
        printf("Erro ao abrir o arquivo de quartos.\n");
        return;
    }

    Quarto quarto;

    printf("Digite o numero do quarto: ");
    scanf(" %d", &quarto.numero);
    printf("Digite a capacidade do quarto: ");
    scanf(" %d", &quarto.capacidade);
    printf("Digite o valor da diaria do quarto: ");
    scanf(" %lf", &quarto.valorDiaria);
    strcpy(quarto.status, "Livre");

    fwrite(&quarto, sizeof(Quarto), 1, file);
    fclose(file);

    printf("Quarto cadastrado com sucesso.\n");
}