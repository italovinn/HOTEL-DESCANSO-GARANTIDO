#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <time.h>

#define MAX_CLIENTES 100
#define MAX_FUNCIONARIOS 100
#define MAX_QUARTOS 100
#define MAX_ESTADIAS 100

//esses são as structs contendo as informações necessarias para o funcionamento do programa//
struct Cliente{
    int codigo;
    char nome[100];
    char endereco[100];
    char telefone[15];
};

struct Funcionario{
    int codigo;
    char nome[100];
    char telefone[15];
    char cargo[100];
    float salario;
};

struct Estadia{
    int codigoEstadia;
    int diaEntrada, mesEntrada, anoEntrada;
    int diaSaida, mesSaida, anoSaida;
    int quantidadeDiaria;
    int codigoCliente;
    int numeroQuarto;
};

struct Quarto{
    int numeroQuarto;
    int quantidadeHospedes;
    int valorEstadia;
    int status;
};

struct Estadia estadias[100];
struct Quarto quartos[100];

struct Cliente clientes[MAX_CLIENTES];
struct Funcionario funcionarios[MAX_FUNCIONARIOS];
struct Estadia estadias[MAX_ESTADIAS];
struct Quarto quartos[MAX_QUARTOS];

int codigosClientes[100];
int codigosFuncionarios[100];
int codigosEstadia[100];
int numDosQuartos[100];

int numClientes = 0;
int numFuncionarios = 0;
int numEstadias = 0;
int numQuartos = 0;

int isNumber(const char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

int arquivoExiste(const char *nomeArquivo) {
    struct stat buffer;
    return (stat(nomeArquivo, &buffer) == 0);
}

int clienteExiste(int codigoCliente) {
    for (int i = 0; i < numClientes; i++) {
        if (clientes[i].codigo == codigoCliente) {
            return 1;
        }
    }
    return 0;
}

void salvarClientes(struct Cliente *clientes, int numClientes, const char *nomeArquivo){
    FILE *file = fopen(nomeArquivo, "w");
    if(file == NULL){
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    for(int i = 0; i < numClientes; i++){
        fprintf(file, "%d;%s;%s;%s\n", clientes[i].codigo, clientes[i].nome, clientes[i].endereco, clientes[i].telefone);
    }

    fclose(file);
}

void salvarFuncionarios(struct Funcionario *funcionarios, int numFuncionarios, const char *nomeArquivo){
    FILE *file = fopen(nomeArquivo, "w");
    if(file == NULL){
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    for(int i = 0; i < numFuncionarios; i++){
        fprintf(file, "%d;%s;%s;%s;%.2f\n", funcionarios[i].codigo, funcionarios[i].nome, funcionarios[i].telefone, funcionarios[i].cargo, funcionarios[i].salario);
    }

    fclose(file);
}

void salvarEstadias(struct Estadia *estadias, int numEstadias, const char *nomeArquivo){
    FILE *file = fopen(nomeArquivo, "w");
    if(file == NULL){
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    for(int i = 0; i < numEstadias; i++){
        fprintf(file, "%d;%d-%d-%d;%d-%d-%d;%d;%d;%d\n", estadias[i].codigoEstadia, estadias[i].diaEntrada, estadias[i].mesEntrada, estadias[i].anoEntrada, estadias[i].diaSaida, estadias[i].mesSaida, estadias[i].anoSaida, estadias[i].quantidadeDiaria, estadias[i].codigoCliente, estadias[i].numeroQuarto);
    }

    fclose(file);
}

void salvarQuartos(struct Quarto *quartos, int numQuartos, const char *nomeArquivo){
    FILE *file = fopen(nomeArquivo, "w");
    if(file == NULL){
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    for(int i = 0; i < numQuartos; i++){
        fprintf(file, "%d;%d;%d;%d\n", quartos[i].numeroQuarto, quartos[i].quantidadeHospedes, quartos[i].valorEstadia, quartos[i].status);
    }

    fclose(file);
}

int carregarClientes(struct Cliente *clientes, const char *nomeArquivo){
    if (!arquivoExiste(nomeArquivo)) {
        FILE *file = fopen(nomeArquivo, "w");
        if (file != NULL) {
            fclose(file);
        }
    }

    FILE *file = fopen(nomeArquivo, "r");
    if(file == NULL){
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return 0;
    }

    int i = 0;
    while(fscanf(file, "%d;%99[^;];%99[^;];%14[^\n]\n", &clientes[i].codigo, clientes[i].nome, clientes[i].endereco, clientes[i].telefone) == 4){
        i++;
    }

    fclose(file);
    return i;
}

int carregarFuncionarios(struct Funcionario *funcionarios, const char *nomeArquivo){
    if (!arquivoExiste(nomeArquivo)) {
        FILE *file = fopen(nomeArquivo, "w");
        if (file != NULL) {
            fclose(file);
        }
    }

    FILE *file = fopen(nomeArquivo, "r");
    if(file == NULL){
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return 0;
    }

    int i = 0;
    while(fscanf(file, "%d;%99[^;];%14[^;];%99[^;];%f\n", &funcionarios[i].codigo, funcionarios[i].nome, funcionarios[i].telefone, funcionarios[i].cargo, &funcionarios[i].salario) == 5){
        i++;
    }

    fclose(file);
    return i;
}

int carregarEstadias(struct Estadia *estadias, const char *nomeArquivo){
    if (!arquivoExiste(nomeArquivo)) {
        FILE *file = fopen(nomeArquivo, "w");
        if (file != NULL) {
            fclose(file);
        }
    }

    FILE *file = fopen(nomeArquivo, "r");
    if(file == NULL){
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return 0;
    }

    int i = 0;
    while(fscanf(file, "%d;%d-%d-%d;%d-%d-%d;%d;%d;%d\n", &estadias[i].codigoEstadia, &estadias[i].diaEntrada, &estadias[i].mesEntrada, &estadias[i].anoEntrada, &estadias[i].diaSaida, &estadias[i].mesSaida, &estadias[i].anoSaida, &estadias[i].quantidadeDiaria, &estadias[i].codigoCliente, &estadias[i].numeroQuarto) == 10){
        i++;
    }

    fclose(file);
    return i;
}

int carregarQuartos(struct Quarto *quartos, const char *nomeArquivo){
    if (!arquivoExiste(nomeArquivo)) {
        FILE *file = fopen(nomeArquivo, "w");
        if (file != NULL) {
            fclose(file);
        }
    }

    FILE *file = fopen(nomeArquivo, "r");
    if(file == NULL){
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return 0;
    }

    int i = 0;
    while(fscanf(file, "%d;%d;%d;%d\n", &quartos[i].numeroQuarto, &quartos[i].quantidadeHospedes, &quartos[i].valorEstadia, &quartos[i].status) == 4){
        i++;
    }

    fclose(file);
    return i;
}

int codigoDuplicado(int codigo, int *codigos, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (codigos[i] == codigo) {
            return 1;
        }
    }
    return 0;
}

int gerarCodigoUnico(int *codigos, int tamanho) {
    int codigo;

    while (1) {
        codigo = rand() % 1000 + 1;
        if (!codigoDuplicado(codigo, codigos, tamanho)) {
            break;
        }
    }
    return codigo;
}

int calcularQuantidadeDeDiarias(int diaEntrada, int mesEntrada, int anoEntrada, int diaSaida, int mesSaida, int anoSaida);

struct Cliente criarcliente(){
    struct Cliente c;

    c.codigo = gerarCodigoUnico(codigosClientes, numClientes);
    codigosClientes[numClientes++] = c.codigo;

    printf("Codigo de Cliente gerado: %d\n", c.codigo);

    printf("Informe o nome do Cliente: ");
    fgets(c.nome, sizeof(c.nome), stdin);
    c.nome[strcspn(c.nome, "\n")] = '\0';

    printf("Informe o Endereco do Cliente: ");
    fgets(c.endereco, sizeof(c.endereco), stdin);
    c.endereco[strcspn(c.endereco, "\n")] = '\0';

    printf("Informe o numero de Telefone do Cliente(00 00000-0000): ");
    fgets(c.telefone, sizeof(c.telefone), stdin);
    c.telefone[strcspn(c.telefone, "\n")] = '\0';

    salvarClientes(clientes, numClientes, "clientes.txt");

    return c;
}

struct Funcionario criarfuncionario(){
    struct Funcionario f;

    f.codigo = gerarCodigoUnico(codigosFuncionarios, numFuncionarios);
    codigosFuncionarios[numFuncionarios++] = f.codigo;

    printf("Codigo de Funcionario gerado: %d\n", f.codigo);

    printf("Informe o nome do Funcionario: ");
    fgets(f.nome, sizeof(f.nome), stdin);
    f.nome[strcspn(f.nome, "\n")] = '\0';

    printf("Informe o numero de telefone do Funcionario(00 00000-0000): ");
    fgets(f.telefone, sizeof(f.telefone), stdin);
    f.telefone[strcspn(f.telefone, "\n")] = '\0';

    printf("Informe o cargo do Funcionario: ");
    fgets(f.cargo, sizeof(f.cargo), stdin);
    f.cargo[strcspn(f.cargo, "\n")] = '\0';

    printf("Informe o salario do Funcionario: ");
    scanf("%f", &f.salario);
    getchar();

    salvarFuncionarios(funcionarios, numFuncionarios, "funcionarios.txt");


    return f;
}

struct Quarto criarquarto(){
    struct Quarto q;

    q.numeroQuarto = numQuartos + 1;

    printf("Informe o numero do quarto: ");
    scanf("%d", &q.numeroQuarto);

    printf("Informe a Quantidade de Hopedes: ");
    scanf("%d", &q.quantidadeHospedes);
    getchar();

    printf("Informe o Valor da Estadia: ");
    scanf("%d", &q.valorEstadia);
    getchar();

    q.status = 0; //0 disponivel e 1 ocupado//

    printf("Quarto Criado com SUCESSO.");

    return q;
}

int quartoDisponivel(int numeroQuarto, int diaEntrada, int mesEntrada, int anoEntrada, int diaSaida, int mesSaida, int anoSaida);

int quartoDisponivel(int numeroQuarto, int diaEntrada, int mesEntrada, int anoEntrada, int diaSaida, int mesSaida, int anoSaida) {
    for (int i = 0; i < numEstadias; i++) {
        if (estadias[i].numeroQuarto == numeroQuarto) {
            if (!((anoSaida < estadias[i].anoEntrada) ||
                  (anoSaida == estadias[i].anoEntrada && mesSaida < estadias[i].mesEntrada) ||
                  (anoSaida == estadias[i].anoEntrada && mesSaida == estadias[i].mesEntrada && diaSaida < estadias[i].diaEntrada) ||
                  (anoEntrada > estadias[i].anoSaida) ||
                  (anoEntrada == estadias[i].anoSaida && mesEntrada > estadias[i].mesSaida) ||
                  (anoEntrada == estadias[i].anoSaida && mesEntrada == estadias[i].mesSaida && diaEntrada > estadias[i].diaSaida))) {
                return 0;
            }
        }
    }
    return 1;
}

struct Estadia criarEstadia(){
    struct Estadia e;

    char entrada[100];

    e.codigoEstadia = gerarCodigoUnico(codigosEstadia, numEstadias);
    codigosEstadia[numEstadias++] = e.codigoEstadia;

    printf("Codigo da Estadia gerado: %d\n", e.codigoEstadia);

    e.quantidadeDiaria = calcularQuantidadeDeDiarias(e.diaEntrada, e.mesEntrada, e.anoEntrada, e.diaSaida, e.mesSaida, e.anoSaida);

    printf("Informe o codigo ou o nome do Cliente para criar: ");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0';

    if (!clienteExiste(e.codigoCliente)) {
        printf("Cliente com código %d não existe.\n", e.codigoCliente);
        e.codigoEstadia = 0;
        return e;
    }

    printf("Informe o numero do Quarto: ");
    scanf("%d", &e.numeroQuarto);

    printf("Informe a data de entrada (dia-mes-ano): ");
    scanf("%d-%d-%d", &e.diaEntrada, &e.mesEntrada, &e.anoEntrada);
    getchar();

    printf("Informe a data de saida (dia-mes-ano): ");
    scanf("%d-%d-%d", &e.diaSaida, &e.mesSaida, &e.anoSaida);
    getchar();

    if (!quartoDisponivel(e.numeroQuarto, e.diaEntrada, e.mesEntrada, e.anoEntrada, e.diaSaida, e.mesSaida, e.anoSaida)) {
        printf("Quarto não está disponível para as datas selecionadas.\n");
        e.codigoEstadia = 0;
    }

    return e;
}

void pesquisarCliente(struct Cliente *clientes, int numClientes){
    char entrada[100];

    printf("Informe o codigo ou o nome do Cliente para pesquisar: ");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0';

    if (isNumber(entrada)) {
        int codigo = atoi(entrada);
        for (int i = 0; i < numClientes; i++) {
            if (clientes[i].codigo == codigo) {
                printf("Cliente encontrado:\n");
                printf("Codigo: %d\n", clientes[i].codigo);
                printf("Nome: %s\n", clientes[i].nome);
                printf("Endereco: %s\n", clientes[i].endereco);
                printf("Telefone: %s\n", clientes[i].telefone);
                return;
            }
        }
        printf("Cliente com codigo %d nao encontrado.\n", codigo);
    } else {
        for (int i = 0; i < numClientes; i++) {
            if (strcmp(clientes[i].nome, entrada) == 0) {
                printf("Cliente encontrado:\n");
                printf("Codigo: %d\n", clientes[i].codigo);
                printf("Nome: %s\n", clientes[i].nome);
                printf("Endereco: %s\n", clientes[i].endereco);
                printf("Telefone: %s\n", clientes[i].telefone);
                return;
            }
        }
        printf("Cliente com nome %s nao encontrado.\n", entrada);
    }
}

void pesquisarFuncionario(struct Funcionario *funcionarios, int numFuncionarios){
    char entrada[100];

    printf("Informe o codigo ou o nome do Funcionario para pesquisar: ");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0';

    if (isNumber(entrada)) {
        int codigo = atoi(entrada);
        for (int i = 0; i < numFuncionarios; i++) {
            if (funcionarios[i].codigo == codigo) {
                printf("Funcionario encontrado:\n");
                printf("Codigo: %d\n", funcionarios[i].codigo);
                printf("Nome: %s\n", funcionarios[i].nome);
                printf("Telefone: %s\n", funcionarios[i].telefone);
                printf("Cargo: %s\n", funcionarios[i].cargo);
                printf("Salario: %.2f\n", funcionarios[i].salario);
                return;
            }
        }
        printf("Funcionario com codigo %d nao encontrado.\n", codigo);
    } else {
        for (int i = 0; i < numFuncionarios; i++) {
            if (strcmp(funcionarios[i].nome, entrada) == 0) {
                printf("Funcionario encontrado:\n");
                printf("Codigo: %d\n", funcionarios[i].codigo);
                printf("Nome: %s\n", funcionarios[i].nome);
                printf("Telefone: %s\n", funcionarios[i].telefone);
                printf("Cargo: %s\n", funcionarios[i].cargo);
                printf("Salario: %.2f\n", funcionarios[i].salario);
                return;
            }
        }
        printf("Funcionario com nome %s nao encontrado.\n", entrada);
    }
}

int calcularQuantidadeDeDiarias(int diaEntrada, int mesEntrada, int anoEntrada, int diaSaida, int mesSaida, int anoSaida);

void darBaixaEstadia(struct Estadia *estadias, int *numEstadias) {
    int codigoEstadia;
    int diaAtual, mesAtual, anoAtual;

    printf("Informe o codigo da Estadia: ");
    scanf("%d", &codigoEstadia);
    getchar();

    printf("Informe a data atual (dia-mes-ano): ");
    scanf("%d-%d-%d", &diaAtual, &mesAtual, &anoAtual);
    getchar();

    for (int i = 0; i < *numEstadias; i++) {
        if (estadias[i].codigoEstadia == codigoEstadia) {
            if (anoAtual > estadias[i].anoSaida ||
                (anoAtual == estadias[i].anoSaida && mesAtual > estadias[i].mesSaida) ||
                (anoAtual == estadias[i].anoSaida && mesAtual == estadias[i].mesSaida && diaAtual >= estadias[i].diaSaida)) {

                printf("Estadia encerrada com sucesso.\n");

                for (int j = 0; j < numQuartos; j++) {
                    if (quartos[j].numeroQuarto == estadias[i].numeroQuarto) {
                        quartos[j].status = 1; // Desocupado
                        salvarQuartos(quartos, numQuartos, "quartos.txt");
                        break;
                    }
                }
            } else {
                printf("A estadia não pode ser encerrada antes da data de saída.\n");
            }
            return;
        }
    }
    printf("Estadia com o código %d não foi encontrada.\n", codigoEstadia);
}

float calcularValorEstadia(int codigoEstadia) {
    for (int i = 0; i < numEstadias; i++) {
        if (estadias[i].codigoEstadia == codigoEstadia) {
            int dias = calcularQuantidadeDeDiarias(estadias[i].diaEntrada, estadias[i].mesEntrada, estadias[i].anoEntrada, estadias[i].diaSaida, estadias[i].mesSaida, estadias[i].anoSaida);
            for (int j = 0; j < numQuartos; j++) {
                if (quartos[j].numeroQuarto == estadias[i].numeroQuarto) {
                    return dias * quartos[j].valorEstadia;
                }
            }
        }
    }
    return 0;
}

void mostrarEstadiasCliente(struct Estadia *estadias, int numEstadias, int codigoCliente){
    printf("Estadias do Cliente:\n");

    for(int i = 0; i < numEstadias; i++){
        if(estadias[i].codigoCliente == codigoCliente){
            printf("Codigo de Estadia: %d\n", estadias[i].codigoEstadia);
            printf("Data de Entrada: %d%d%d\n", estadias[i].diaEntrada, estadias[i].mesEntrada, estadias[i].anoEntrada);
            printf("Data de Saida: %d/%d/%d\n", estadias[i].diaSaida, estadias[i].mesSaida, estadias[i].anoSaida);
            printf("Numero do Quarto: %d\n\n", estadias[i].numeroQuarto);
        }
    }
}

struct Quarto* encontrarQuartoDisponivel(int quantidadeHospedes, int diaEntrada, int mesEntrada, int anoEntrada, int diaSaida, int mesSaida, int anoSaida){
    for(int i = 0; i < numQuartos; i++){
        if(quartos[i].quantidadeHospedes >= quantidadeHospedes && quartoDisponivel(quartos[i].numeroQuarto, diaEntrada, mesEntrada, anoEntrada, diaSaida, mesSaida, anoSaida)){
            return &quartos[i];
        }
    }
    return NULL;
}

int calcularQuantidadeDeDiarias(int diaEntrada, int mesEntrada, int anoEntrada, int diaSaida, int mesSaida, int anoSaida) {
    int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (anoEntrada == anoSaida && mesEntrada == mesSaida) {
        return diaSaida - diaEntrada;
    } else {
        int diasEntrada = diasPorMes[mesEntrada - 1] - diaEntrada + 1;
        int diasSaida = diaSaida;

        int diasIntermediarios = 0;
        for (int mes = mesEntrada; mes < mesSaida - 1; mes++) {
            diasIntermediarios += diasPorMes[mes];
        }

        int diarias = (diaSaida - diaEntrada) + (mesSaida - mesEntrada) * 30 + (anoSaida - anoEntrada) * 365;
        return diarias;
        
        return diarias;
    }
}

void consultarDisponibilidade(){
    struct Quarto quartos[100];
    numQuartos = carregarQuartos(quartos, "quartos.txt");

    printf("Quartos disponíveis:\n");

    for(int i = 0; i < numQuartos; i++){
        if(quartos[i].status == 0){
        printf("Quarto %d está disponível\n", quartos[i].numeroQuarto);
        }
    }
}

int main(){
    srand(time(NULL));
    int opcao;
    int codigoCliente;

    numClientes = carregarClientes(clientes, "clientes.txt");
    numFuncionarios = carregarFuncionarios(funcionarios, "funcionarios.txt");
    numEstadias = carregarEstadias(estadias, "estadias.txt");
    numQuartos = carregarQuartos(quartos, "quartos.txt");

    printf("\n\n\nBEM VINDO AO HOTEL DESCANSO GARANTIDO!!\n\n");

    do{
        printf("\nMenu:\n");
        printf("1. Cadastrar Cliente;\n");
        printf("2. Cadastrar Funcionario\n");
        printf("3. Cadastrar Quarto\n");
        printf("4. Cadastrar Estadia\n");
        printf("5. Consultar Disponibilidade do Quarto\n");
        printf("6. Pesquisar Cliente\n");
        printf("7. Pesquisar Funcionario\n");
        printf("8. Dar Baixa em Estadia\n");
        printf("9. Pesquisar Estadias do Cliente\n");
        printf("0. Sair\n");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
            case 1:
                printf("\nCadastro de Cliente:\n");
                clientes[numClientes++] = criarcliente();
                salvarClientes(clientes, numClientes, "clientes.txt");
            break;
            case 2:
                printf("\nCadastro de Funcionario:\n");
                funcionarios[numFuncionarios++] = criarfuncionario();
                salvarFuncionarios(funcionarios, numFuncionarios, "funcionarios.txt");
            break;
            case 3:
                printf("\nCadastro de Quarto:\n");
                criarquarto();
                salvarQuartos(quartos, numQuartos, "quartos.txt");
            break;
            case 4:
                printf("\nCadastro de Estadia:\n");
                estadias[numEstadias++] = criarEstadia();
                salvarEstadias(estadias, numEstadias, "estadias.txt");
            break;
            case 5:
                printf("\nConsultar Disponibilidade de Quarto:\n");
                consultarDisponibilidade();
            break;
            case 6:
                printf("\nPesquisar Cliente:\n");
                pesquisarCliente(clientes, numClientes);
            break;
            case 7:
                printf("\nPesquisar Funcionario:\n");
                pesquisarFuncionario(funcionarios, numFuncionarios);
            break;
            case 8:
                printf("\nDar Baixa em Estadia:\n");
                darBaixaEstadia(estadias, &numEstadias);
                salvarEstadias(estadias, numEstadias, "estadias.txt");
            break;
            case 9:
                printf("\nMostrar Estadias de um Cliente:\n");
                printf("Informe o código do cliente: ");
                scanf("%d", &codigoCliente);
                mostrarEstadiasCliente(estadias, numEstadias, codigoCliente);
            break;
            case 0:
                printf("Saindo...\n");
            break;
            default:
                printf("Selecione uma opcao valida\n");
            break;
        }
    }while(opcao != 0);

    return 0;
}