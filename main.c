#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int numeroConta;
    char nome[50];
    float saldo;
} Cliente;

void limparBuffer()
{
    while (getchar() != '\n')
        ;
}

int contaExiste(FILE *arquivo, int conta)
{
    Cliente cliente;

    rewind(arquivo);

    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1)
    {
        if (cliente.numeroConta == conta)
        {
            return 1;
        }
    }

    return 0;
}

void cadastrarCliente(FILE *arquivo)
{
    Cliente cliente;
    int posicao;

    printf("Posicao para cadastrar: ");
    scanf("%d", &posicao);

    if (posicao < 0)
    {
        printf("Posicao invalida.\n");
        return;
    }

    printf("Numero da conta: ");
    scanf("%d", &cliente.numeroConta);

    if (cliente.numeroConta <= 0)
    {
        printf("Numero de conta invalido.\n");
        return;
    }

    if (contaExiste(arquivo, cliente.numeroConta))
    {
        printf("Ja existe um cliente com essa conta.\n");
        return;
    }

    limparBuffer();

    printf("Nome: ");
    fgets(cliente.nome, sizeof(cliente.nome), stdin);
    cliente.nome[strcspn(cliente.nome, "\n")] = '\0';

    printf("Saldo: ");
    scanf("%f", &cliente.saldo);

    if (cliente.saldo < 0)
    {
        printf("Saldo nao pode ser negativo.\n");
        return;
    }

    if (fseek(arquivo, posicao * sizeof(Cliente), SEEK_SET) != 0)
    {
        printf("Erro ao posicionar arquivo.\n");
        return;
    }

    if (fwrite(&cliente, sizeof(Cliente), 1, arquivo) != 1)
    {
        printf("Erro ao gravar cliente.\n");
        return;
    }

    fflush(arquivo);

    printf("Cliente cadastrado com sucesso!\n");
}

void consultarCliente(FILE *arquivo)
{
    Cliente cliente;
    int conta;
    int encontrou = 0;

    printf("Numero da conta: ");
    scanf("%d", &conta);

    rewind(arquivo);

    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1)
    {
        if (cliente.numeroConta == conta)
        {
            printf("\nConta: %d\n", cliente.numeroConta);
            printf("Nome: %s\n", cliente.nome);
            printf("Saldo: %.2f\n", cliente.saldo);

            encontrou = 1;
            break;
        }
    }

    if (!encontrou)
    {
        printf("Cliente nao encontrado.\n");
    }
}

void atualizarSaldo(FILE *arquivo)
{
    Cliente cliente;
    int conta;
    int encontrou = 0;

    printf("Numero da conta: ");
    scanf("%d", &conta);

    rewind(arquivo);

    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1)
    {
        if (cliente.numeroConta == conta)
        {
            printf("Saldo atual: %.2f\n", cliente.saldo);

            printf("Novo saldo: ");
            scanf("%f", &cliente.saldo);

            if (cliente.saldo < 0)
            {
                printf("Saldo invalido.\n");
                return;
            }

            fseek(arquivo, -(long)sizeof(Cliente), SEEK_CUR);

            if (fwrite(&cliente, sizeof(Cliente), 1, arquivo) != 1)
            {
                printf("Erro ao atualizar saldo.\n");
                return;
            }

            fflush(arquivo);

            printf("Saldo atualizado!\n");

            encontrou = 1;
            break;
        }
    }

    if (!encontrou)
    {
        printf("Cliente nao encontrado.\n");
    }
}

void encerrarConta(FILE *arquivo)
{
    Cliente cliente;
    int conta;
    int encontrou = 0;

    printf("Numero da conta: ");
    scanf("%d", &conta);

    rewind(arquivo);

    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1)
    {
        if (cliente.numeroConta == conta)
        {
            cliente.numeroConta = 0;
            strcpy(cliente.nome, "");
            cliente.saldo = 0;

            fseek(arquivo, -(long)sizeof(Cliente), SEEK_CUR);

            if (fwrite(&cliente, sizeof(Cliente), 1, arquivo) != 1)
            {
                printf("Erro ao encerrar conta.\n");
                return;
            }

            fflush(arquivo);

            printf("Conta encerrada!\n");

            encontrou = 1;
            break;
        }
    }

    if (!encontrou)
    {
        printf("Cliente nao encontrado.\n");
    }
}

void listarClientes(FILE *arquivo)
{
    Cliente cliente;
    int encontrou = 0;

    rewind(arquivo);

    printf("\n===== CLIENTES =====\n");

    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1)
    {
        if (cliente.numeroConta != 0)
        {
            printf("Conta: %d\n", cliente.numeroConta);
            printf("Nome: %s\n", cliente.nome);
            printf("Saldo: %.2f\n", cliente.saldo);
            printf("-------------------\n");

            encontrou = 1;
        }
    }

    if (!encontrou)
    {
        printf("Nenhum cliente cadastrado.\n");
    }
}

int main()
{
    FILE *arquivo;
    int opcao;

    arquivo = fopen("clientes.dat", "rb+");

    if (arquivo == NULL)
    {
        arquivo = fopen("clientes.dat", "wb+");

        if (arquivo == NULL)
        {
            printf("Erro ao abrir arquivo.\n");
            return 1;
        }
    }

    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Consultar cliente\n");
        printf("3 - Atualizar saldo\n");
        printf("4 - Encerrar conta\n");
        printf("5 - Listar clientes\n");
        printf("6 - Rewind\n");
        printf("7 - Sair\n");
        printf("Opcao: ");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastrarCliente(arquivo);
            break;

        case 2:
            consultarCliente(arquivo);
            break;

        case 3:
            atualizarSaldo(arquivo);
            break;

        case 4:
            encerrarConta(arquivo);
            break;

        case 5:
            listarClientes(arquivo);
            break;

        case 6:
            rewind(arquivo);
            printf("Ponteiro reposicionado para o inicio do arquivo.\n");
            break;

        case 7:
            printf("Encerrando sistema...\n");
            break;

        default:
            printf("Opcao invalida.\n");
        }

    } while (opcao != 7);

    fclose(arquivo);

    return 0;
}
