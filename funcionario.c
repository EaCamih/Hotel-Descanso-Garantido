#include "funcionario.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cadastrarFuncionario() {
    FILE *file = fopen("funcionarios.bin", "rb");
    if(!file) {
        printf("Erro ao abrir o arquivo de funcionarios.\n");
        return;
    }

    Funcionario funcionario;
    funcionario.codigo = gerarCodigo();

    printf("Digite o nome do funcionario: ");
    scanf(" %[^\n]", funcionario.nome);
    printf("Digite o endereco do funcionario: ");
    scanf(" %[^\n]", funcionario.endereco);
    printf("Digite o cargo do funcionario: ");
    scanf(" %[^\n]", funcionario.cargo);
    printf("Digite o salario do funcionario: ");
    scanf(" %lf", &funcionario.salario);

    fwrite(&funcionario, sizeof(Funcionario), 1, file);
    fclose(file);

    printf("Funcionario cadastrado com sucesso.\n");
    printf("Codigo do funcionario: %d\n", funcionario.codigo);
}

void pesquisarFuncionario() {
    FILE *file = fopen("funcionarios.bin", "rb");
    if(!file) {
        printf("Erro ao abrir o arquivo de funcionarios.\n");
        return;
    }

    Funcionario funcionario;

    int codigo;
    char nome[100];
    printf("Pesquisar por (1) codigo ou (2) nome? ");
    int escolha;
    scanf(" %d", &escolha);

    int encontrado = 0;

    if(escolha == 1) {
        printf("Digite o codigo do funcionario: ");
        scanf(" %d", &codigo);

        while(fread(&funcionario, sizeof(funcionario), 1, file)) {
            if(funcionario.codigo == codigo) {
                printf("\e[1;1H\e[2J");
                printf("Funcionario encontrado!\n");
                printf("Codigo: %d\n", funcionario.codigo);
                printf("Nome: %s\n", funcionario.nome);
                printf("Endereco: %s\n", funcionario.endereco);
                printf("Telefone: %s\n", funcionario.telefone);
                encontrado = 1;
                break;
            }
        }
    }else if(escolha == 2) {
        printf("Digite o nome do funcionario: ");
        scanf(" %[^\n]", nome);

        while (fread(&funcionario, sizeof(funcionario), 1, file)) {
            if(strcmp(funcionario.nome, nome) == 0) {
                printf("\e[1;1H\e[2J");
                printf("Funcionario encontrado!\n");
                printf("Codigo: %d\n", funcionario.codigo);
                printf("Nome: %s\n", funcionario.nome);
                printf("Endereco: %s\n", funcionario.endereco);
                printf("Telefone: %s\n", funcionario.telefone);
                printf("Cargo: %s\n", funcionario.cargo);
                printf("Salario: %.2lf\n", funcionario.salario);
                encontrado = 1;
                break;
            }
        }
    }else {
        printf("Opcao invalida.\n");
    }

    if((escolha == 1 || escolha == 2) && !encontrado) {
        printf("Funcionario nao encontrado.\n");
    }

    fclose(file);
}
