#include "cliente.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cadastrarCliente() {
    FILE *file = fopen("clientes.bin", "ab");
    if(!file) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    Cliente cliente;
    cliente.codigo = gerarCodigo();

    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]", cliente.nome);
    printf("Digite o endereco do cliente: ");
    scanf(" %[^\n]", cliente.endereco);
    printf("Digite o telefone do cliente: ");
    scanf(" %[^\n]", cliente.telefone);

    fwrite(&cliente, sizeof(Cliente), 1, file);
    fclose(file);

    printf("Cliente cadastrado com sucesso.\n");
    printf("Codigo do cliente: %d\n", cliente.codigo);
    printf("\n\n Pressione qualquer tecla para voltar ao menu principal.");
    getchar();
}

void pesquisarCliente() {
    FILE * file = fopen("clientes.bin", "rb");
    if(!file) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    Cliente cliente;

    int codigo;
    char nome[100];
    printf("Pesquisar por (1) codigo ou (2) nome? ");
    int escolha;
    scanf(" %d", &escolha);

    int encontrado = 0;

    if(escolha == 1) {
        printf("Digite o codigo do cliente: ");
        scanf(" %d", &codigo);

        while(fread(&cliente, sizeof(Cliente), 1, file)) {
            if(cliente.codigo == codigo) {
                printf("\e[1;1H\e[2J");
                printf("Cliente encontrado!\n");
                printf("Codigo: %d\n", cliente.codigo);
                printf("Nome: %s\n", cliente.nome);
                printf("Endereco: %s\n", cliente.endereco);
                printf("Telefone: %s\n", cliente.telefone);
                encontrado = 1;
                break;
            }
        }
    }else if(escolha == 2) {
        printf("Digite o nome do cliente: ");
        scanf(" %[^\n]", nome);

        while (fread(&cliente, sizeof(Cliente), 1, file)) {
            if(strcmp(cliente.nome, nome) == 0) {
                printf("\e[1;1H\e[2J");
                printf("Cliente encontrado!\n");
                printf("Codigo: %d\n", cliente.codigo);
                printf("Nome: %s\n", cliente.nome);
                printf("Endereco: %s\n", cliente.endereco);
                printf("Telefone: %s\n", cliente.telefone);
                encontrado = 1;
                break;
            }
        }
    }else {
        printf("Opcao invalida.\n");
    }

    if((escolha == 1 || escolha == 2) && !encontrado) {
        printf("Cliente nao encontrado.\n");
    }

    fclose(file);
}