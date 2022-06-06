#include "stdbt.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#define MAX 10

short criaArquivoAleatorio( const char* nomeArquivo )
{
    register long i;
    long numAle, temp;
    long* vet = (long*)malloc(MAX * sizeof(long));
    FILE* fp = fopen(nomeArquivo, "w+");

    if ( !fp )
        return 0;

    for ( i = 0; i < MAX; ++i )
        vet[i] = i+1;

    srand( time(NULL) );

    for ( i = 0; i < MAX; ++i )
    {
        numAle = rand() % MAX;

        temp = vet[numAle];
        vet[numAle] = vet[i];
        vet[i] = temp;
    }

    for ( i = 0; i < MAX; ++i )
        fprintf(fp, "%li, ", vet[i]);

    free(vet);
    fclose(fp);
    return 1;
}

int main()
{
    register long i;
    long dado;
    short bol;
    binTree* root;
    const char* nomeArquivoE = "entrada.txt";
    const char* nomeArquivoS = "saida.txt";
    char* ptrLocale,* defaultLocale, newLocale[] = "portuguese";

    ptrLocale = setlocale(LC_ALL, NULL);
    defaultLocale = (char*)strdup(ptrLocale);
    if ( !defaultLocale )
    {
        printf("Erro no setlocale.");
        exit(51);
    }

    setlocale(LC_ALL, newLocale);

    bol = newRoot(&root);
    if ( bol )
        printf("A cria��o da raiz foi um sucesso!\n");
    else
    {
        printf("Erro ao criar a raiz.\n");
        exit(61);
    }

    printf("A �rvore est� vazia: %s.\n", (isTreeEmpty(root)) ? ("sim") : ("n�o"));

    bol = criaArquivoAleatorio(nomeArquivoE);
    if ( bol )
        printf("A cria��o do arquivo foi um sucesso!\n");
    else
    {
        printf("Erro ao criar o arquivo.\n");
        exit(72);
    }

    bol = finsertTree(nomeArquivoE, root);
    if ( bol )
        printf("A inser��o na �rvore foi um sucesso!\n");
    else
    {
        printf("Erro ao inserir na �rvore.\n");
        exit(81);
    }

    printf("Altura da �rvore: %li.\n"
           "N�mero de n�s: %li.\n"
           "N�mero de n�s folhas: %li.\n"
           "N�mero de n�s n�o folhas: %li.\n", treesHeight(root), nodeCount(root), leafCount(root), noLeafCount(root));

    system("pause");

    system("cls");
    printf("Iniciando impress�o em ordem, pr� ordem e p�s ordem:\n");
    bol = printInOrder(root);
    printf("\n");
    bol = printPreOrder(root);
    printf("\n");
    bol = printPostOrder(root);

    printf("\n");
    for ( i = 0; i < MAX / 5; ++i )
    {
        printf("Qual o %li� dado que voc� deseja remover: ", i+1);
        scanf(" %li", &dado);

        bol = deleteNode(root, dado);
        if ( !bol )
        {
            printf("Erro ao remover n� da �rvore.\n");
            exit(111);
        }
    }

    system("cls");
    printf("Dados removidos com sucesso!\n");
    printf("Iniciando impress�o em ordem, pr� ordem e p�s ordem:\n");
    bol = printInOrder(root);
    printf("\n");
    bol = printPreOrder(root);
    printf("\n");
    bol = printPostOrder(root);
    printf("\n");

    printf("Altura da �rvore: %li\n"
           "N�mero de n�s: %li\n"
           "N�mero de n�s folhas: %li\n"
           "N�mero de n�s n�o folhas: %li\n", treesHeight(root), nodeCount(root), leafCount(root), noLeafCount(root));

    system("pause");

    system("cls");
    bol = ftreeQuery(nomeArquivoE, root, nomeArquivoS);
    if ( bol )
        printf("A consulta na �rvore foi um sucesso!\n");
    else
    {
        printf("Erro ao consultar a �rvore.\n");
        exit(137);
    }

    bol = freeTree(root);
    if ( bol )
        printf("A �rvore foi liberada!\n");
    else
    {
        printf("Erro ao liberar a �rvore.\n");
        exit(146);
    }

    free(defaultLocale);
    return 0;
}
