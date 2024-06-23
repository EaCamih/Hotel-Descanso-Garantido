#include "estadia.h"
#include "quarto.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cadastrarEstadia() {
    FILE * file = fopen("estadias.bin", "ab");
    if(!file) {
        printf("Erro ao abrir o arquivo de estadias.\n");
        return;
    }

    Estadia estadia;
    estadia.codigoEstadia = gerarCodigo();

    printf("Digite o codigo do cliente: ");
    scanf(" %d", &estadia.codigoCliente);
    printf("Digite o numero do quarto: ");
    scanf(" %d", &estadia.numeroQuarto);
    printf("Digite a data de entrada (AAAA-MM-DD): ");
    scanf(" %s", estadia.dataEntrada);
    printf("Digite a data de saida (AAAA-MM-DD): ");
    scanf(" %s", estadia.dataSaida);

    estadia.quantidadeDiarias = calcularDias(estadia.dataEntrada, estadia.dataSaida);

    FILE *quartoFile = fopen("quartos.bin", "rb+");
    if(!quartoFile) {
        printf("Erro ao abrir o arquivo de quartos.\n");
        return;
    }

    Quarto quarto;
    while(fread(&quarto, sizeof(Quarto), 1, quartoFile)) {
        if(quarto.numero == estadia.numeroQuarto) {
            strcpy(quarto.status, "Ocupado");
            fseek(quartoFile, -sizeof(Quarto), SEEK_CUR);
            fwrite(&quarto, sizeof(Quarto), 1, quartoFile);
            break;
        }
    }
    fclose(quartoFile);
    fwrite(&estadia, sizeof(Estadia), 1, file);
    fclose(file);

    printf("Estadia cadastrada com sucesso.\n");
    printf("Codigo da estadia: %d\n", estadia.codigoEstadia);
}

void mostrarEstadiasCliente() {
    FILE *file = fopen("estadias.bin", "rb");
    if(!file) {
        printf("Erro ao abrir o arquivo de estadias.\n");
        return;
    }

    Estadia estadia;

    int codigoCliente;
    printf("Digite o codigo do cliente: ");
    scanf(" %d", &codigoCliente);

    int encontrou = 0;
    while(fread(&estadia, sizeof(Estadia), 1, file)) {
        if(estadia.codigoCliente == codigoCliente) {
            printf("\e[1;1H\e[2J");
            printf("Estadia encontrada!\n");
            printf("\nCodigo da estadia: %d\n", estadia.codigoEstadia);
            printf("Numero do quarto: %d\n", estadia.numeroQuarto);
            printf("Data de entrada: %s\n", estadia.dataEntrada);
            printf("Data de saida: %s\n", estadia.dataSaida);
            printf("Quantidade de diarias: %d\n", estadia.quantidadeDiarias);
            encontrou = 1;
        }
    }

    if(!encontrou) {
        printf("Nenhuma estadia encontrada para o cliente.\n");
    }

    fclose(file);
}

int calcularPontos(int codigoCliente) {
    FILE *file = fopen("estadias.bin", "rb");
    if(!file) {
        printf("Erro ao abrir o arquivo de estadias.\n");
        return;
    }

    Estadia estadia;
    int pontos = 0;

    while(fread(&estadia, sizeof(Estadia), 1, file)) {
        if(estadia.codigoCliente == codigoCliente) {
            pontos += estadia.quantidadeDiarias;
        }
    }

    fclose(file);
    return pontos;
}

void darBaixaEstadia() {
    FILE *file = fopen("estadias.bin", "rb+");
    if(!file) {
        printf("Erro ao abrir o arquivo de estadias.\n");
        return;
    }

    Estadia estadia;

    int codigoEstadia;
    printf("Digite o codigo da estadia: ");
    scanf(" %d", &codigoEstadia);

    int encontrou = 0;
    long pos;

    while((pos = ftell(file)) >= 0 && fread(&estadia, sizeof(Estadia), 1, file)) {
        if(estadia.codigoEstadia == codigoEstadia) {
            encontrou = 1;
            break;
        }
    }

    if(!encontrou) {
        printf("Estadia nao encontrada.\n");
        fclose(file);
        return;
    }

    FILE *quartoFile = fopen("quartos.bin", "rb+");
    if(!quartoFile) {
        printf("Erro ao abrir o arquivo de quartos.\n");
        return;
    }

    Quarto quarto;
    double total = 0.0;

    while(fread(&quarto, sizeof(Quarto), 1, quartoFile)) {
        if(quarto.numero == estadia.numeroQuarto) {
            total = estadia.quantidadeDiarias * quarto.valorDiaria;
            strcpy(quarto.status, "Livre");
            fseek(quartoFile, -sizeof(Quarto), SEEK_CUR);
            fwrite(&quarto, sizeof(Quarto), 1, quartoFile);
            break;
        }
    }
    fclose(quartoFile);

    printf("Estadia encerrada com sucesso.\n");
    printf("Total a pagar: %.2f\n", total);

    fseek(file, pos, SEEK_SET);
    fread(&estadia, sizeof(Estadia), 1, file);
    estadia.quantidadeDiarias = 0;
    fseek(file, -sizeof(Estadia), SEEK_CUR);
    fwrite(&estadia, sizeof(Estadia), 1, file);

    fclose(file);
}