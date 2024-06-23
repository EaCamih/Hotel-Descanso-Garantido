#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int gerarCodigo() {
    srand(time(NULL));
    return rand();
}

int calcularDias(const char* dataEntrada, const char* dataSaida) {
    struct tm tm_entrada = {0};
    struct tm tm_saida = {0};

    sscanf(dataEntrada, "%4d-%2d-%2d", &tm_entrada.tm_year, &tm_entrada.tm_mon, &tm_entrada.tm_mday);
    sscanf(dataSaida, "%4d-%2d-%2d", &tm_saida.tm_year, &tm_saida.tm_mon, &tm_saida.tm_mday);

    tm_entrada.tm_year -= 1900;
    tm_entrada.tm_mon -= 1;
    tm_saida.tm_year -= 1900;
    tm_saida.tm_mon -= 1;

    time_t timeEntrada = mktime(&tm_entrada);
    time_t timeSaida = mktime(&tm_saida);

    double diff = difftime(timeSaida, timeEntrada);
    return diff / (60 * 60 * 24);
}

void lerString(char *string, int tamanho) {
    fgets(string, tamanho, stdin);
    size_t ln = strlen(string);
    if(ln > 0 && string[ln - 1] == '\n') {
        string[ln - 1] = '\0';
    }
}
