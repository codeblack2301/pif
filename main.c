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
    conta_model contas[5];

    int cont = 0;
    bool condicao = true;
    for (int i = 0; i < 5; i++)
    {
        printf("insira o seu nome: ");
        scanf("%s", &contas[i].nome);
        printf("insira o numero da sua conta: ");
        scanf("%d", &contas[i].conta);
        printf("insira o id da sua conta: ");
        scanf("%d", &contas[i].id);
    }

    return 0;
}
