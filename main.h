#ifndef MAIN_H
#define MAIN_H

#define NOME_MAX 1100
#define CIDADE_MAX 50
#define PESSOA_MAX 1100 // Tamanho maximo de uma estrutura PESSOA
#define DATA_MAX 11
#define UF_MAX 500      // Tamanho para ler a linha do txt de UFs
#define LOCAL_MAX 60    // Tamanho maximo de uma estrutura CIDADE-UF
#define ERRO 1111

typedef struct // Struct que armazena as informações de uma pessoa
{
    char nome[NOME_MAX];
    char sexo[2];
    char data[DATA_MAX];
    char cidade[CIDADE_MAX];
    char UF[3];
    int idade;
} PESSOA;

#endif
