#include <stdio.h>

#include "cliente.h"
#include "funcionario.h"
#include "quarto.h"
#include "estadia.h"

void menu() {
    int escolha;

    do {
        printf("\n -- Menu Hotel Descanso Garantido -- \n\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Cadastrar funcionario\n");
        printf("3 - Cadastrar quarto\n");
        printf("4 - Cadastrar estadia\n");
        printf("5 - Dar baixa em estadia\n");
        printf("6 - Pesquisar cliente\n");
        printf("7 - Pesquisar funcionario\n");
        printf("8 - Mostrar estadias de um cliente\n");
        printf("9 - Calcular pontos de um cliente\n");
        printf("0 - Sair\n");
        printf("\n\nEscolha uma opcao: ");
        scanf("%d", &escolha);

        switch(escolha) {
            case 1:
                printf("\e[1;1H\e[2J");
                cadastrarCliente();
                break;
            case 2:
                printf("\e[1;1H\e[2J");
                cadastrarFuncionario();
                break;
            case 3:
                printf("\e[1;1H\e[2J");
                cadastrarQuarto();
                break;
            case 4:
                printf("\e[1;1H\e[2J");
                cadastrarEstadia();
                break;
            case 5:
                printf("\e[1;1H\e[2J");
                darBaixaEstadia();
                break;
            case 6:
                printf("\e[1;1H\e[2J");
                pesquisarCliente();
                break;
            case 7:
                printf("\e[1;1H\e[2J");
                pesquisarFuncionario();
                break;
            case 8:
                printf("\e[1;1H\e[2J");
                mostrarEstadiasCliente();
                break;
            case 9: {
                printf("\e[1;1H\e[2J");
                int codigo;
                printf("Digite o codigo do cliente: ");
                scanf("%d", &codigo);
                int pontos = calcularPontos(codigo);
                printf("Pontos do cliente: %d\n", pontos);
                break;
            }
            case 0:
                printf("\e[1;1H\e[2J");
                printf("Saindo...\n");
                break;
            default:
                printf("\e[1;1H\e[2J");
                break;
        }
    } while (escolha != 0);
}

int main() {
    menu();
    return 0;
}