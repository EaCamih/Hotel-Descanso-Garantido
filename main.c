#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int codigo;
    char nome[100];
    char endereco[200];
    char telefone[15];
} Cliente;

typedef struct {
    int codigo;
    char nome [100];
    char endereco[200];
    char cargo[50];
    double salario;
} Funcionario;

typedef struct {
    int numero;
    int capacidade;
    double valorDiaria;
    char status[10];
} Quarto;

typedef struct {
    int codigoEstadia;
    int codigoCliente;
    int numeroQuarto;
    char dataEntrada[11];
    char dataSaida[11];
    int quantidadeDiarias;
} Estadia;

void cadastrarCliente();
void cadastrarFuncionario();
void cadastrarQuarto();
void cadastrarEstadia();

// void darBaixaEstadia();
void pesquisarCliente(char* nome);
// void pesquisarFuncionario(char* nome);
// void mostrarEstadiasCliente(int codigoCliente);
// void calcularPontos(int codigoCliente);

void menu();

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
}

void cadastrarFuncionario() {
    FILE *file = fopen("funcionarios.bin", "ab");
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

    if(!encontrado) {
        printf("Cliente nao encontrado.\n");
    }

    fclose(file);
}

void menu() {
    int escolha;

    do {
        printf("\e[1;1H\e[2J");
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
            // case 5:
            //     printf("\e[1;1H\e[2J");
            //     darBaixaEstadia();
            //     break;
            case 6:
                printf("\e[1;1H\e[2J");
                pesquisarCliente();
                break;
            // case 7:
            //     printf("\e[1;1H\e[2J");
            //     pesquisarFuncionario();
            //     break;
            // case 8:
            //     printf("\e[1;1H\e[2J");
            //     mostrarEstadiasCliente();
            //     break;
            // case 9: {
            //     printf("\e[1;1H\e[2J");
            //     int codigo;
            //     printf("Digite o codigo do cliente: ");
            //     scanf("%d", &codigo);
            //     int pontos = calcularPontos(codigo);
            //     printf("Pontos do cliente: %d\n", pontos);
            //     break;
            // }
            case 0:
                printf("\e[1;1H\e[2J");
                printf("Saindo...\n");
                break;
            default:
                break;
        }
    } while (escolha != 0);
}

int main() {
    menu();
    return 0;
}