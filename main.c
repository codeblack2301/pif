#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    char nome[50];
    float conta;
    int id;
} conta_model;

int main()
{
    int id_;
    char opcao[1];
    int numero_contas;
    printf("-------QUANTAS CONTAS VC DESEJA CADASTRAR--------\n");
    printf(": ");

    scanf("%d", &numero_contas);

    conta_model contas[5];

    int cont = 0;
    bool condicao = true;
    for (int i = 0; i < numero_contas; i++)
    {
        printf("insira o seu nome: ");
        scanf("%s", &contas[i].nome);
        printf("insira o numero da sua conta: ");
        scanf("%d", &contas[i].conta);
        printf("insira o id da sua conta: ");
        scanf("%d", &contas[i].id);
    }

    printf("---------VC DESEJA FAZER MAIS ALGUMA OPERAÇÃO?\n");
    printf("s / n");
    scanf("%c", &opcao);

    while (opcao == "s")
    {
        printf("insira o id da conta: ");
        scanf("%d", &id_);

        printf("---------VC DESEJA FAZER MAIS ALGUMA OPERAÇÃO?\n");
        printf("s / n");
        scanf("%c", &opcao);
        return 0;
    }
}
