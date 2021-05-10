#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define NOME_MAX 1000
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

// Declaracoes das funcoes auxiliares
void cadastrapessoa(PESSOA habitante);
void registracidade(PESSOA habitante);
void registraestado(PESSOA habitante);
void registrapessoa(PESSOA habitante);
void listaestado(PESSOA habitante);
void listacidade(PESSOA habitante);
void consultapessoa();
void excluipessoa();
void confirmaexclusao();
void relatoriofinal();
int verificanome(PESSOA habitante);
int verificadata(PESSOA habitante);
int verificacidade_UF(PESSOA habitante, int funcao);
int verificacidade(PESSOA habitante);
int verificaUF(PESSOA habitante);
int menu();
void telainicial();

int main()
{
    int opcoes;
    PESSOA habitante;

    // Chamando a tela inicial
    telainicial();

    do
    {
        // Laco para a repeticao do menu
        opcoes = menu();
        fflush(stdin);
        if(opcoes == 1)
        {
            registraestado(habitante);
        }
        else if(opcoes == 2)
        {
            registracidade(habitante);
        }
        else if(opcoes == 3)
        {
            cadastrapessoa(habitante);
        }
        else if(opcoes == 4)
        {
            listaestado(habitante);
        }
        else if(opcoes == 5)
        {
            listacidade(habitante);
        }
        else if(opcoes == 6)
        {
            consultapessoa();
        }
        else if(opcoes == 7)
        {
            excluipessoa();
        }
        else if(opcoes == 8)
        {
            relatoriofinal();
        }
        else if(opcoes != 9)
        {
            printf("Se quiser finalizar o programa, digite 9 e aperte enter;\ncaso tenha digitado errado, pode continuar a mexer como quiser. :)\n\n");
            system("pause");
            system("cls");
        }
    }
    while(opcoes!=9);

    printf("\nAte mais!\n");

    return 0;
}

//---------Verifica Nome---------------------------------------------------------------------------------------
int verificanome(PESSOA habitante) // Funcao que verifica se o nome digitado eh valido
{
    int nome = 0, erro = 0, espinicio = 0, esp = 0;// Para verificacoes de validacao do nome

    for(int i = 0; i < strlen(habitante.nome); i++)
    {
        if((habitante.nome[i] >= 'A'  && habitante.nome[i] <= 'Z'))// Verifica se na posicao eh letra
        {
            nome++;
            esp = 0; // Zera o espaco para que nao deixe tambem terminar com espacos
        }
        else
        {
            erro++;     // Se tiver algo alem de letras, nao sera possivel entrar
        }
        if(i == 0 && habitante.nome[i] == ' ')
        {
            espinicio++;// Se o nome comecar com espacos, nao permite cadastro
        }
        if(espinicio == 0 && (isspace(habitante.nome[i])))
        {
            esp++;      // Nao permite espaco adicional ao fim e/ou ao inicio do nome se > 0
            erro--;
        }
    }

    if((nome > 1) && (erro == 0) && (espinicio == 0) && (esp == 0))// Verificando se o nome nao eh vazio ou se eh formado por letras
    {
        return 0;
    }
    else if(erro > 0)// Caso tenha algum caracter diferente de letras
    {
        return 1;
    }
    else if(nome == 1)// Caso so tenha uma letra
    {
        return 2;
    }
    else if(espinicio > 0)// Caso comece com espacos
    {
        return 3;
    }
    else
        return 1;// Caso de algum erro diferente
}

//---------Verifica Data---------------------------------------------------------------------------------------
int verificadata(PESSOA habitante) // Funcao para verificar se a data da pessoa cadastrada eh verdadeira
{                                  // e calcular sua idade

    int anoin, mesin, diain, verificador = 0, i = 0, erro = 0, l = 0, idade = -1;
    int dia_atual, mes_atual, ano_atual;
    char anoc[5], mesc[3], diac[3], *token, datatemp[11];
    struct tm *data_atual;// Armazenar data
    time_t segundos;// Armazenar o tempo em segundos

    time(&segundos);// Obtendo o tempo em segundos
    data_atual = localtime(&segundos);  // Convertendo para o tempo local
    dia_atual = data_atual->tm_mday;    // Armazenando o dia do mes
    mes_atual = data_atual->tm_mon+1;   // Armazenando o mes
    ano_atual = data_atual->tm_year+1900;// Armazenando o ano

    strcpy(datatemp, habitante.data);
    token = strtok(habitante.data, "/");// Dividindo a data em tokens para atribuicoes

    // Armazenando o mes e o ano
    while(token != NULL)
    {
        if(i == 0)
        {
            strcpy(diac, token);
        }
        if(i == 1)
        {
            strcpy(mesc, token);
        }
        if(i == 2)
        {
            strcpy(anoc, token);
        }
        i++;
        token = strtok(NULL, "/");
    }
    strcpy(habitante.data, datatemp);

    // Convertendo para int
    diain = atoi(diac);
    anoin = atoi(anoc);
    mesin = atoi(mesc);

    if(habitante.data[2] == '/' && habitante.data[5] == '/')
    {
        verificador++;
    }

    // A partir daqui são verificacoes para saber se a data eh valida, assim como sua formatacao
    if(strlen(habitante.data) < 10)
    {
        erro++;
    }
    else
    {
        if((habitante.data[3] == '0' && habitante.data[4] == '1') || (habitante.data[3] == '0' && habitante.data[4] == '3') ||
           (habitante.data[3] == '0' && habitante.data[4] == '5') || (habitante.data[3] == '0' && habitante.data[4] == '7') ||
           (habitante.data[3] == '0' && habitante.data[4] == '8') || (habitante.data[3] == '1' && habitante.data[4] == '0') ||
           (habitante.data[3] == '1' && habitante.data[4] == '2'))
        {
            if((habitante.data[0] == '0' && habitante.data[1] > '1' && habitante.data[1] <= '9') || (habitante.data[0] == '1' &&
                                                                                                     habitante.data[1] >= '0' && habitante.data[1] <= '9') || (habitante.data[0] == '2' && habitante.data[1] >= '0' &&
                                                                                                                                                               habitante.data[1] <= '9') || (habitante.data[0] == '3' && habitante.data[1] >= '0' && habitante.data[1] <= '1'))
            {
                verificador++;
            }
        }

        if((habitante.data[3] == '0' && habitante.data[4] == '4') || (habitante.data[3] == '0' && habitante.data[4] == '6') ||
           (habitante.data[3] == '0' && habitante.data[4] == '9') || (habitante.data[3] == '1' && habitante.data[4] == '1'))
        {
            if((habitante.data[0] == '0' && habitante.data[1] > '1' && habitante.data[1] <= '9') || (habitante.data[0] == '1' &&
                                                                                                     habitante.data[1] >= '0' && habitante.data[1] <= '9') || (habitante.data[0] == '2' && habitante.data[1] >= '0' &&
                                                                                                                                                               habitante.data[1] <= '9') || (habitante.data[0] == '3' && habitante.data[1] == '0'))
            {
                verificador++;
            }
        }

        if(habitante.data[3] == '0' && habitante.data[4] == '2')
        {
            if((habitante.data[0] == '0' && habitante.data[1] > '1' && habitante.data[1] <= '9') || (habitante.data[0] == '1' &&
                                                                                                     habitante.data[1] >= '0' && habitante.data[1] <= '9') || (habitante.data[0] == '2' && habitante.data[1] >= '0' &&
                                                                                                                                                               habitante.data[1] <= '8'))
            {
                verificador++;
            }
            else if((habitante.data[0] == '0' && habitante.data[1] > '1' && habitante.data[1] <= '9') || (habitante.data[0] == '1' &&
                                                                                                          habitante.data[1] >= '0' && habitante.data[1] <= '9') || (habitante.data[0] == '2' && habitante.data[1] >= '0' &&
                                                                                                                                                                    habitante.data[1] <= '9'))
            {
                verificador++;
            }
        }

    }

    // Calculando a idade
    i = anoin;// Para calculo do ano bissexto
    if(anoin > 1870 && anoin <= ano_atual)
    {
        idade = 0;
        for(l = anoin; l <= ano_atual; l++)
        {
            if((anoin%400 == 0 || anoin%100 != 0) && (anoin%4 == 0) && (habitante.data[0] == '2') &&
               (habitante.data[1] == '9') && (habitante.data[3] == '0') && (habitante.data[4] == '2'))
            {
                if(i < ano_atual && i != anoin)// Calcula a idade se o ano for bissexto e o dia for 29/02
                {
                    idade++;// Soma de quatro em quatro anos
                    i += 4;
                }
                else
                    i++;
            }
            else
            {
                if(l < ano_atual && l != anoin)// Calculo idade normalmente ate ano atual
                {
                    idade++;
                }
                if(l == ano_atual)
                {
                    if(mes_atual > mesin)// Calculo se o mes ja tiver passado
                    {
                        idade++;
                    }
                    else if(mes_atual == mesin)// Se for o mes atual, verifico se ja passou o dia
                    {
                        if(dia_atual >= diain)// Se for o dia atual ou ja passou, calculo idade
                        {
                            idade++;
                        }
                    }
                }
            }
        }
    }
    if((verificador == 2 && erro == 0) && idade != -1)
    {
        return idade;
    }
    else
    {
        return ERRO;// Caso tenha algum erro na data
    }
}

//---------Verifica Cidade e UF--------------------------------------------------------------------------------
int verificacidade_UF(PESSOA habitante, int funcao)
{
    /*  Funcao que verifica se a cidade esta registrada para o cadastro de pessoas (funcao == 1),
        ou se eh valida para cadastro (funcao == 2)*/

    FILE *cidades_registradas_txt;
    int procura_cidade_registrada = 0, procuraUF_igual = 0, certo = 0, i = 0;
    int cidade = 0, esp = 0, espinicio = 0, erro = 0;
    char cidades_registradas[CIDADE_MAX];
    char cidade_formatada[CIDADE_MAX];
    char cidadetemp[CIDADE_MAX];
    char *token;

    cidades_registradas_txt = fopen("cidades registradas.txt", "rb");// Abro so para ler
    strcpy(cidadetemp, habitante.cidade);
    strcat(habitante.cidade, "-");
    strcat(habitante.cidade, habitante.UF);
    strcpy(cidade_formatada, habitante.cidade);
    strcpy(habitante.cidade, cidadetemp);
    strcat(cidade_formatada, "\n");

    for(i = 0; i < strlen(habitante.cidade); i++)
    {
        if((habitante.cidade[i] >= 'A'  && habitante.cidade[i] <= 'Z'))// Verifica se na posicao eh letra
        {
            cidade++;
            esp = 0; // Zera o espaco para que nao deixe tambem terminar com espacos
        }
        else
        {
            erro++;     // Se tiver algo alem de letras, nao sera possivel entrar
        }
        if(i == 0 && habitante.cidade[i] == ' ')
        {
            espinicio++;// Se o nome comecar com espacos, nao permite cadastro
        }
        if(espinicio == 0 && (isspace(habitante.cidade[i])))
        {
            esp++;      // Nao permite espaco adicional ao fim do nome se > 0
            erro--;
        }
    }

    if(cidades_registradas_txt)
    {
        if(funcao == 1) // Funcao de cadastrar pessoa
        {
            while(fgets(cidades_registradas, 1500, cidades_registradas_txt))
            {
                i = 0;
                strcpy(cidadetemp, cidades_registradas);
                token = strtok(cidades_registradas, "-");
                // Dividindo a estrutura CIDADE-UF
                while(token != NULL)
                {
                    i++;
                    if(i == 1)
                    {
                        strcat(token, "\n");
                        if(strstr(token, habitante.cidade)) // Verifico se a cidade esta registrada pelo buffer
                        {
                            procura_cidade_registrada++;    // Contador para verificar quantas vezes a cidade aparece
                        }
                    }
                    if(i == 2)
                    {
                        if(strstr(token, habitante.UF))// Também verifico se a uf eh igual da cidade, se nao for, aviso que a cidade eh de outra uf
                        {
                            procuraUF_igual++;         // Contador para verificar quantas vezes a UF aparece
                        }
                    }
                    token = strtok(NULL, "-");
                }
                if(strcmp(cidade_formatada, cidadetemp) == 0)// Se a cidade estiver registrada na UF, soma o int certo
                {
                    certo++;
                }
            }
            if(certo == 1)
            {
                fclose(cidades_registradas_txt);
                return 0;// Caso esteja correto
            }
            else if((procura_cidade_registrada > 0) && (procuraUF_igual == 0))// Se a cidade aparece mais de uma vez mas a UF nao, a cidade eh invalida
            {
                fclose(cidades_registradas_txt);
                return 1;// Caso a cidade nao esteja cadastrada na UF
            }
            else if((procura_cidade_registrada == 0) && (procuraUF_igual == 0))// Se a cidade nao aparece nenhuma vez nem a UF, a cidade eh invalida
            {
                fclose(cidades_registradas_txt);
                return 3;// Caso a cidade nao esteja cadastrada
            }
            else
            {
                fclose(cidades_registradas_txt);
                return 3;// Algum outro erro
            }
        }
        else // Funcao de registrar cidade
        {
            if((cidade <= 1) || (erro > 0) || (espinicio > 0) || (esp > 0))
            {
                fclose(cidades_registradas_txt);
                return 4;// Caso a cidade nao siga a formatacao correta
            }
            while(fgets(cidades_registradas, 1500, cidades_registradas_txt))
            {
                if(strcmp(cidade_formatada, cidades_registradas) == 0)// Se a cidade estiver registrada na UF, soma o int certo
                {
                    certo++;
                }
            }
            if(certo == 0)
            {
                fclose(cidades_registradas_txt);
                return 0;// Caso a cidade ainda nao esteja registrada
            }
            else
            {
                return 1;// Caso a cidade esteja registrada
            }
        }
    }
    else
    {
        fclose(cidades_registradas_txt);
        return 2;// Caso o arquivo nao abra, provavelmente nenhuma cidade foi cadastrada
    }

    fclose(cidades_registradas_txt);

}

//---------Verifica UF-----------------------------------------------------------------------------------------
int verificaUF(PESSOA habitante)    // Funcao que verifica se a UF esta registrada
{
    FILE *uf;               // Arquivo pra abrir o txt das UFs
    char uftxt[UF_MAX];     // String para armazenar o conteudo do txt, numero 100
    int procurastring = 0, UF = 0;   // String criada pra verificar se a UF digitada esta dentro do .txt das UFs registradas

    uf = fopen("UFregistrada.txt", "rb");/* Abro so pra ler para caso
                                            nao tenha sido nenhuma registrada */

    for(int i = 0; i < strlen(habitante.UF); i++)
    {
        if((habitante.UF[i] >= 'A'  && habitante.UF[i] <= 'Z'))// Verifica se na posicao eh letra
        {
            UF++;
        }
    }

    if(uf)
    {
        if(strlen(habitante.UF) == 2 && UF == 2)
        {
            do
            {
                fscanf(uf,"%s",uftxt);// Transferindo o conteudo do txt para uma string
                if(strstr(uftxt, habitante.UF))
                {
                    procurastring++;// Se a UF aparece, o contador eh somado
                }
            }
            while(!feof(uf));
            if(procurastring != 0)
            {
                fclose(uf);
                return 0;// Caso apareca no txt
            }
            else
            {
                fclose(uf);
                return 1;// Caso nao apareça no txt
            }
        }
        else
        {
            fclose(uf);
            return 3;// Caso a escrita seja invalida
        }
    }
    else
    {
        fclose(uf);
        return 2;// Caso o arquivo nao abra, provavelmente nenhuma UF foi cadastrada
    }

    fclose(uf);

}

//---------Verifica Cidade-------------------------------------------------------------------------------------
int verificacidade(PESSOA habitante)// Verifica se a cidade existe para a funcao listacidade
{
    FILE *cidades_registradas_txt;
    int procura_cidade_registrada = 0, letras = 0, i = 0;
    char cidades_registradas[CIDADE_MAX];
    char cidadetemp[CIDADE_MAX];
    char *token;

    cidades_registradas_txt = fopen("cidades registradas.txt", "rb");// Abrindo o arquivo das cidades registradas

    strupr(habitante.cidade);
    int tamanho = strlen(habitante.cidade);

    for(i = 0; i < tamanho; i++)
    {
        if((habitante.cidade[i] >= 'A' && habitante.cidade[i] <= 'Z') || isspace(habitante.cidade[i]))
        {
            letras++;// Verificando se eh formado por letras e/ou espacos
        }
    }

    if(letras != tamanho || tamanho == 0)
    {
        fclose(cidades_registradas_txt);
        return 4;// Caso tenha algo diferente de letras
    }

    if(cidades_registradas_txt)
    {
        while(fgets(cidades_registradas, 1500, cidades_registradas_txt))
        {
            i = 0;
            strcpy(cidadetemp, cidades_registradas);// Armazenando a info das cidades para verificacao
            // Dividindo a estrutura CIDADE-UF
            token = strtok(cidades_registradas, "-");
            while(token != NULL)
            {
                i++;
                if(i == 1)
                {
                    strcat(token, "\n");// Boto um \n para seguir a estrutura de habitante.cidade
                    if(strstr(token, habitante.cidade)) // Buffer para verificar se a cidade esta registrada
                    {
                        procura_cidade_registrada++;    // Contador para verificar quantas vezes a cidade aparece
                    }
                }
                token = strtok(NULL, "-");
            }
        }

        if(procura_cidade_registrada == 1)// Se a cidade aparece so uma vez, eh ela
        {
            fclose(cidades_registradas_txt);
            return 0;// Caso a cidade nao esteja cadastrada na UF
        }
        else if(procura_cidade_registrada > 1)// Se aparece mais de uma vez, acontece outra verificacao no procedimento
        {
            return 1;
        }
        else if(procura_cidade_registrada == 0)// Se a cidade nao aparece nenhuma vez, a cidade eh invalida
        {
            fclose(cidades_registradas_txt);
            return 3;// Caso a cidade nao esteja cadastrada
        }
        else
        {
            fclose(cidades_registradas_txt);
            return 3;// Algum outro erro
        }
    }
    else
    {
        fclose(cidades_registradas_txt);
        return 2;// Caso o arquivo nao abra, provavelmente nenhuma cidade foi cadastrada
    }


    fclose(cidades_registradas_txt);

}

//---------Cadastra Pessoa-------------------------------------------------------------------------------------
void cadastrapessoa(PESSOA habitante)
{
    /* Funcao que ha de cadastrar a pessoa, primeiro verificando
    se os seus dados estão corretos, para ai sim registra-la no banco*/
    int verificador = 0, funcao = 1;
    char opcao[2];

    system("cls");

    printf("Digite o nome da pessoa: ");
    fflush(stdin);
    scanf("%[^\n]s", habitante.nome);// Lendo o nome
    strupr(habitante.nome);
    verificador = verificanome(habitante);
    if(verificador == 0)// Caso o nome nao seja vazio, comece e termine com letras, e seja formado apenas por letras
    {
        printf("Digite o sexo da pessoa (M ou F): ");
        fflush(stdin);
        scanf("%[^\n]s", habitante.sexo);// Lendo o sexo
        strupr(habitante.sexo);
        if(strcmp(habitante.sexo, "M") == 0 || strcmp(habitante.sexo, "F") == 0)// Verificando se o sexo eh valido
        {
            printf("Digite a data de nascimento da pessoa (DD/MM/AAAA): ");
            fflush(stdin);
            scanf("%[^\n]s", habitante.data);// Lendo a data
            habitante.idade = verificadata(habitante);
            if(habitante.idade < 151)// O retorno eh a idade, que passa se morar no conjunto [0,150]
            {
                printf("Digite a UF de onde a pessoa foi vacinada: ");
                fflush(stdin);
                scanf("%[^\n]s", habitante.UF);
                printf("Digite agora a cidade: ");
                fflush(stdin);
                scanf("%[^\n]s", habitante.cidade);
                strupr(habitante.UF);
                strupr(habitante.cidade);
                verificador = verificacidade_UF(habitante, funcao);
                if(verificador == 0)// Caso a cidade e a UF sejam cadastradas e a cidade pertenca a UF
                {
                    do
                    {
                        // Verificacao do cadastro
                        printf("\nVoce realmente deseja cadastrar os dados de %s?(S/N): ", habitante.nome);
                        fflush(stdin);
                        scanf("%[^\n]s", opcao);
                        strupr(opcao);
                    }while(strcmp(opcao, "N") != 0 && strcmp(opcao, "S") != 0);
                    if(strcmp(opcao, "S") == 0)// Caso haja confirmacao do cadastro
                    {
                        registrapessoa(habitante);// Chama o procedimento que salva no arquivo apos verificacoes
                    }
                    else if(strcmp(opcao, "N") == 0)
                    {
                        printf("\n%s nao foi cadastrado(a).\n\n", habitante.nome);
                    }
                }
                else if(verificador == 1)
                {
                    printf("\nEsta cidade pode estar registrada, porem nao nessa UF.\n");
                    printf("Verifique a escrita e tente novamente.\n\n");
                }
                else if(verificador == 2)
                {
                    printf("Nao foi possivel abrir o arquivo :(\n");
                    printf("Voce ja cadastrou alguma cidade?\n\n");
                }
                else if(verificador == 3)
                {
                    printf("\nEsta cidade nao esta registrada ou eh invalida.\n");
                    printf("Verifique a escrita e tente novamente.\n\n");
                }
                else if(verificador == 4)
                {
                    printf("\nPor favor, verifique a escrita e tente novamente.\n");
                    if(strlen(habitante.UF) != 2)
                    {
                        printf("Lembre-se: as UFs sao formadas por duas letras.\n\n");
                    }
                }
            }
            else if(habitante.idade == ERRO)// Se a data foi digitada incorretamente ou nao existe, ou eh muito antiga
            {
                printf("\nEssa data eh invalida\n\n");
            }
        }
        else
        {
            printf("\nSexo invalido.\n\n");
        }
    }
    else if(verificador == 1)
    {
        printf("\nO nome deve ser formado apenas por letras\n");
        printf("Verifique se digitou algum espaco adicional\n\n");
    }
    else if(verificador == 2)
    {
        printf("\nDigite pelo menos mais de uma letra para o nome\n\n");
    }
    else if(verificador == 3)
    {
        printf("\nPor favor nao digite espaco(s) antes do nome\n\n");
    }

    system("pause");
    system("cls");

}

//---------Registra Estado-------------------------------------------------------------------------------------
void registraestado(PESSOA habitante) // Procedimento que registra os estados por suas siglas no arquivo
{
    system("cls");

    FILE *estados_registrados_txt;
    char UFs_registradas[100];      // Para armazenar as UFs registradas
    int contador = 0;               // Para contar quantos estados ja estao registrados
    char opcao[2];                  // Para ler a opcao do usuario
    int verificador;                // Para atribuir a funcao verificaUF

    estados_registrados_txt = fopen("UFregistrada.txt", "a+b"); // Abrindo o arquivo das UFs registradas

    if(estados_registrados_txt)     // Verificando se o arquivo foi criado ou ja existe
    {
        printf("UFs ja registradas (ordem de cadastro): \n\n");
        fseek(estados_registrados_txt,0,SEEK_SET);
        do
        {
            // Listando as UFs que ja foram registradas
            fscanf(estados_registrados_txt, "%s ", UFs_registradas);
            if(strlen(UFs_registradas) > 1)
            {
                printf("- ");
                printf("%s\n", UFs_registradas);
                contador++;
            }
        }while(!feof(estados_registrados_txt));
    }
    if(contador == 0)// Caso nenhuma UF tenha sido registrada
    {
        printf("Ainda nao foram cadastradas UFs.\n");
    }
    printf("\n");
    system("pause");
    // Processo de registro
    printf("\nDigite a UF que deseja registrar: ");
    fflush(stdin);
    scanf("%[^\n]s", habitante.UF);   // Armazenando a UF a ser cadastrada
    strupr(habitante.UF);
    verificador = verificaUF(habitante);
    if(verificador == 1)// Caso siga as regras para registro de UF e nao exista ainda
    {
        // Verificando a certeza do registro e cadastrando caso "S"
        do
        {
            printf("Tem certeza que deseja registrar essa UF?(S/N): ");
            fflush(stdin);
            scanf("%[^\n]s", opcao);
            strupr(opcao);
        }while(strcmp(opcao, "N") != 0 && strcmp(opcao, "S") != 0);
        if(strcmp(opcao, "S") == 0)
        {
            fseek(estados_registrados_txt,0,SEEK_END);          // Colocando o ponteiro no fim do .txt
            fprintf(estados_registrados_txt,"%s ",habitante.UF);// Escrevendo a UF inserida no arquivo
            printf("\nUF armazenada com sucesso :D\n\n");
        }
        else if(strcmp(opcao, "N") == 0)
        {
            printf("\nA UF nao foi registrada.\n\n");
        }
    }
    else if(verificador == 0)
    {
        printf("\nEssa UF ja esta registrada.\n\n");
    }
    else if(verificador == 2)
    {
        printf("\nNao foi possivel abrir o arquivo de UFs.\n\n");
    }
    else if(verificador == 3)
    {
        printf("\nUF invalida\nLembre-se: a UF eh formada por duas letras.\n\n");
    }

    system("pause");
    system("cls");

    fclose(estados_registrados_txt);
}

//---------Registra Cidade-------------------------------------------------------------------------------------
void registracidade(PESSOA habitante) // Procedimento que registra as cidades no arquivo
{
    system("cls");

    FILE *cidades_registradas_txt, *UFs_registradas_txt;
    int contadorcidade = 0, verificador, funcao = 2;
    char cidades_registradas[500];
    char opcao[2];

    cidades_registradas_txt = fopen("cidades registradas.txt", "a+b");
    UFs_registradas_txt = fopen("UFregistrada.txt", "a+b");         // Abrindo o arquivo das cidades e UFs já registradas


    if(cidades_registradas_txt)
    {
        // Listando as cidades ja registradas
        printf("Cidades ja registradas e suas respectivas UFs (ordem de cadastro): \n\n");
        while(fgets(cidades_registradas, 1500, cidades_registradas_txt))
        {
            printf("- ");
            printf("%s", cidades_registradas);
            contadorcidade++;
        }
        if(contadorcidade == 0)
        {
            printf("Ainda nao foram cadastradas cidades.\n");
        }
        printf("\n");
        system("pause");
        // Processo de registro
        printf("\nDigite o nome da cidade que deseja registrar: ");
        fflush(stdin);
        scanf("%[^\n]s", habitante.cidade);// Armazenando a cidade a ser registrada
        printf("Digite a UF a qual essa cidade pertence: ");
        fflush(stdin);
        scanf("%[^\n]s", habitante.UF);    // Armazenando a UF da cidade
    }
    else
    {
        printf("\nNao foi possivel abrir o arquivo das cidades\n\n");
    }

    strupr(habitante.cidade);
    strupr(habitante.UF);          // Transformando as duas strings em maiusculo para melhor verificacao
    verificador = verificaUF(habitante);

    if(verificador == 0)// Caso a UF seja valida e cadastrada
    {
        verificador = verificacidade_UF(habitante, funcao);
        if(verificador == 0)// Caso a cidade seja valida e nao cadastrada nessa UF
        {
            do
            {
                // Verificando a certeza do registro e cadastrando caso "S"
                printf("Tem certeza que deseja registrar essa cidade?(S/N): ");
                fflush(stdin);
                scanf("%[^\n]s", opcao);
                strupr(opcao);
            }while(strcmp(opcao, "N") != 0 && strcmp(opcao, "S") != 0);
            if(strcmp(opcao, "S") == 0)
            {
                fseek(cidades_registradas_txt,0,SEEK_END); // Colocando o ponteiro no fim do .txt
                fprintf(cidades_registradas_txt,"%s-%s\n",habitante.cidade,habitante.UF);
                printf("\nCidade armazenada com sucesso :)\n\n");
            }
            else if(strcmp(opcao, "N") == 0)
            {
                printf("\nA cidade nao foi registrada.\n\n");
            }
        }
        else if(verificador == 4)
        {
            printf("\nCidade invalida!\n");
            if(strlen(habitante.cidade) == 0)
            {
                printf("Digite algo para que possa ser feito o cadastro da cidade.\n\n");
            }
            else
            {
                printf("As cidades sao formadas somente e com pelo menos mais de uma letra.");
                printf("\nVerifique se ha algum espaco adicional\n\n");
            }
        }
    }
    else
    {
        printf("\nEssa UF nao esta cadastrada ou eh invalida\n\n");
    }

    system("pause");
    system("cls");

    fclose(UFs_registradas_txt);
    fclose(cidades_registradas_txt);
}

//---------Registra Pessoa-------------------------------------------------------------------------------------
void registrapessoa(PESSOA habitante) // Procedimento que registra as pessoas no arquivo
{
    FILE *txt_pessoas;

    txt_pessoas = fopen("pessoas.txt", "a+b");// Abrindo o .txt com as pessoas registradas
    if(txt_pessoas)
    {
        fseek(txt_pessoas,0,SEEK_END);// Colocando o ponteiro no fim do .txt
        fprintf(txt_pessoas,"%s,%s-%s,Idade:%d,Sexo:%s \n",
                habitante.nome, habitante.cidade, habitante.UF, habitante.idade, habitante.sexo);// Escrevendo toda a struct no arquivo
        printf("Dados de %s armazenados com sucesso!\n\n", habitante.nome);
    }
    else
    {
        printf("Erro ao abrir arquivo :(\n\n");
    }

    fclose(txt_pessoas);
}

//---------Lista Pessoas por Estado----------------------------------------------------------------------------
void listaestado(PESSOA habitante)// Procedimento que lista as pessoas de acordo com suas UFs
{
    system("cls");
    FILE *pessoas_txt, *UFs_registradas_txt;
    int i = 0, j = 0;       // Para guardar somente o estado
    char *token1, *token2;  // Separar as categorias do struct da pessoa e separar cidade de estado
    char dados_pessoa[PESSOA_MAX];
    char pessoas_registradas[PESSOA_MAX];// String pra armazenar as linhas de cada pessoa
    int pessoas = 0;// Caso nao tenha nenhuma pessoa, continuara zero
    int verificador;

    pessoas_txt = fopen("pessoas.txt", "rb");
    UFs_registradas_txt = fopen("UFregistrada.txt", "rb"); // Abrindo os arquivos das pessoas e das UFs

    if(pessoas_txt)
    {
        if(UFs_registradas_txt)
        {
            printf("Digite a UF do estado que deseja listar: ");
            fflush(stdin);
            scanf("%[^\n]s", habitante.UF);
            strupr(habitante.UF);
            verificador = verificaUF(habitante);
            if(verificador == 0)// Verifica se a estrutura da uf digitada eh valida e esta registrada
            {
                printf("Segue(m) a(s) pessoa(s) registradas neste estado:\n\n");
                printf("---------------------------------------------------------------------------\n");
                while(fgets(pessoas_registradas,PESSOA_MAX,pessoas_txt))
                {
                    // Dividindo a struct para verificacao
                    strcpy(dados_pessoa, pessoas_registradas);// armazeno para printar depois caso seja a situacao
                    token1 = strtok(pessoas_registradas, ",");
                    i = 0;
                    j = 0;
                    while(token1 != NULL)
                    {
                        i++;
                        if(i == 2)
                        {
                            token2 = strtok(token1, "-");
                            while(token2 != NULL)
                            {
                                if(j == 1)
                                {
                                    if(strcmp(token2, habitante.UF) == 0) // buffer para listar as pessoas pelo estado
                                    {
                                        printf("%s", dados_pessoa);
                                        printf("---------------------------------------------------------------------------\n");
                                        pessoas++;// conto caso alguem esteja cadastrado na UF, caso contrario, dou um aviso
                                    }
                                }
                                token2 = strtok(NULL, "-");
                                j++;
                            }
                        }
                        token1 = strtok(NULL, ",");
                    }
                }
                if(pessoas == 0)
                {
                    printf("---------------------------------------------------------------------------\n");
                    printf("\n\nAinda nao foram cadastradas pessoas neste estado.\n\n");
                }
                if(pessoas != 0)
                {
                    printf("\n");
                }
            }
            else if(verificador == 1)
            {
                printf("\nEsta UF nao foi registrada ou a escrita eh invalida\n");
                printf("Lembre-se: as UFs sao formadas e registradas com apenas duas letras\n\n");
            }
        }
        else
        {
            printf("Nao foi possivel abrir o arquivo :(\n");
            printf("Voce cadastrou alguma pessoa?\n\n");
        }
    }
    else
    {
        printf("Nao foi possivel abrir o arquivo :(\n");
        printf("Voce cadastrou alguma UF?\n\n");
    }

    system("pause");
    system("cls");

    fclose(pessoas_txt);
    fclose(UFs_registradas_txt);
}

//---------Lista Pessoas por Cidade----------------------------------------------------------------------------
void listacidade(PESSOA habitante)// Procedimento que lista as pessoas de acordo com suas cidades
{
    system("cls");
    FILE *pessoas_txt, *cidades_registradas_txt;
    int i, numero, k, verificador = 0, contadorpessoas = 0;
    char cidades_registradas[LOCAL_MAX], pessoas_registradas[PESSOA_MAX], *token, cidadetemp[CIDADE_MAX];
    char cidadeprocurada[CIDADE_MAX], *token2, pessoatemp[PESSOA_MAX];

    pessoas_txt = fopen("pessoas.txt", "rb");
    cidades_registradas_txt = fopen("cidades registradas.txt", "rb");// Abrindo os arquivos de pessoas e cidades para leitura

    if(pessoas_txt)
    {
        if(cidades_registradas_txt)
        {
            printf("Digite a cidade que deseja listar: ");
            fflush(stdin);
            scanf("%[^\n]s", habitante.cidade);
            strupr(habitante.cidade);
            verificador = verificacidade(habitante);
            if(verificador == 0)// Verifica se a cidade possui apenas letras e esta cadastrada
            {
                printf("\nSegue(m) a(s) pessoa(s) desta cidade: \n\n");
                printf("---------------------------------------------------------------------------\n");
                while(fgets(pessoas_registradas, PESSOA_MAX, pessoas_txt))// Transferindo o txt pra uma string)
                {
                    strcpy(pessoatemp, pessoas_registradas);
                    // Separando a struct PESSOA para verificacao
                    token = strtok(pessoas_registradas, ",");
                    i = 0;
                    k = 0;
                    while(token != NULL)
                    {
                        i++;
                        if(i == 2)// Posicao de CIDADE-UF na struct
                        {
                            token2 = strtok(token, "-");// Obtenho apenas CIDADE da string da pessoa
                            if(k == 0)
                            {
                                if(strcmp(token2, habitante.cidade) == 0)// Verifico se a cidade eh igual
                                {
                                    printf("%s", pessoatemp);
                                    printf("---------------------------------------------------------------------------\n");
                                    contadorpessoas++;
                                }
                            }
                            k++;
                            token2 = strtok(NULL, "-");
                        }
                        token = strtok(NULL , ",");
                    }
                }
                printf("\n\n");
                if(contadorpessoas > 0)
                {
                    printf("\n");
                }
                else
                {
                    printf("---------------------------------------------------------------------------\n");
                    printf("\n\nAinda nao foram cadastradas pessoas nesta cidade\n\n");
                }
            }
            else if(verificador == 1)// Caso haja mais de uma cidade com UFs diferentes
            {
                printf("\nAs seguintes cidades foram encontradas: \n\n");
                k = 1;
                fseek(cidades_registradas_txt, 0, SEEK_SET);
                while(fgets(cidades_registradas, LOCAL_MAX, cidades_registradas_txt))
                {
                    strcpy(cidadetemp, cidades_registradas);
                    // Dividindo a struct CIDADE
                    token = strtok(cidades_registradas, "-");
                    i = 0;
                    while(token != NULL)
                    {
                        i++;
                        if(strcmp(token, habitante.cidade) == 0 && i == 1)
                        {
                            printf("%d.", k);
                            printf("%s", cidadetemp);// Printo toda a struct da cidade para escolha do usuario
                            k++;
                        }
                        token = strtok(NULL, "-");
                    }
                }
                do
                {
                    printf("\nDigite o numero da cidade que deseja listar: ");
                    fflush(stdin);
                    scanf("%d", &numero);
                }while(numero < 1 || numero > k-1);
                k = 1;
                printf("\nSegue(m) a(s) pessoa(s) registrada(s) nessa localizacao:\n\n");
                printf("---------------------------------------------------------------------------\n");
                fseek(cidades_registradas_txt, 0, SEEK_SET);
                while(fgets(cidades_registradas, LOCAL_MAX, cidades_registradas_txt))
                {
                    strcpy(cidadetemp, cidades_registradas);
                    // Dividindo a struct CIDADE para poder obter apenas a cidade procurada pelo usuario
                    token = strtok(cidades_registradas, "-");
                    i = 0;
                    while(token != NULL)
                    {
                        i++;
                        if(strcmp(token, habitante.cidade) == 0 && i == 1)
                        {
                            if(k == numero)// Se chegar no numero escolhido pelo usuario, eu armazeno a cidade
                            {
                                strcpy(cidadeprocurada, token);
                            }
                            k++;// Somo caso seja outra cidade que tenha entrado
                        }
                        if(strcmp(cidadeprocurada, habitante.cidade) == 0 && i == 2)// Armazenando a UF caso seja a cidade correta
                        {
                            strcat(cidadeprocurada,"-");
                            token[2] = '\0';// Para nao ocorrer erros na verificacao
                            strcat(cidadeprocurada, token);// Junto a UF com a cidade
                        }
                        token = strtok(NULL, "-");
                    }
                }
                fseek(pessoas_txt, 0, SEEK_SET);
                while(fgets(pessoas_registradas, PESSOA_MAX, pessoas_txt))
                {
                    // Printo somente os que realmente sao da cidade+uf
                    if((strstr(pessoas_registradas,cidadeprocurada)))
                    {
                        printf("%s", pessoas_registradas);
                        printf("---------------------------------------------------------------------------\n");
                        contadorpessoas++;// Conto para retornar depois se alguem foi listado
                    }
                }
                if(contadorpessoas == 0)
                {
                    printf("---------------------------------------------------------------------------\n\n");
                    printf("Nao existem pessoas cadastradas nessa localizacao\n\n");
                }
                else
                {
                    printf("\n");
                }
            }
            else if(verificador == 1)
            {
                printf("\nEssa cidade eh invalida ou nao esta cadastrada nessa UF\n");
                printf("Verifique a escrita e tente novamente.\n\n");
            }
            else if(verificador == 3)
            {
                printf("\nEssa cidade nao esta cadastrada\n");
                printf("Verifique a escrita e tente novamente\n\n");
            }
            else if(verificador == 4)
            {
                printf("\nPor favor, digite pelo menos uma letra para que possa ser feita a verificacao.\n");
            }
        }
        else
        {
            printf("\nNao foi possivel abrir o arquivo :(\n");
            printf("Voce cadastrou alguma cidade?\n\n");
        }
    }
    else
    {
        printf("Nao foi possivel abrir o arquivo :(\n");
        printf("Voce cadastrou alguma pessoa?\n\n");
    }

    system("pause");
    system("cls");

    fclose(cidades_registradas_txt);
    fclose(pessoas_txt);

}

//---------Consulta Pessoa-------------------------------------------------------------------------------------
void consultapessoa()// Procedimento que mostra informacoes de uma pessoa em particular
{
    system("cls");
    FILE *pessoas_txt;
    char pessoa_desejada[NOME_MAX], lista_pessoas[PESSOA_MAX], infopessoa[PESSOA_MAX], dados_pessoa[PESSOA_MAX];
    int contador = 0, k = 0;
    char *token;

    pessoas_txt = fopen("pessoas.txt", "rb");// Abrindo arquivo de pessoas para leitura

    if(pessoas_txt)
    {
        printf("Digite o nome ou sobrenome da pessoa que deseja consultar: ");
        fflush(stdin);
        scanf("%[^\n]s", pessoa_desejada);
        strupr(pessoa_desejada);
        while(fgets(lista_pessoas,NOME_MAX,pessoas_txt))
        {
            strcpy(dados_pessoa, lista_pessoas);
            // Dividindo a struct PESSOA
            token = strtok(lista_pessoas, ",");
            k = 0;
            while(token != NULL)
            {
                k++;// Para diferenciar as posicoes do token
                if(strstr(token, pessoa_desejada) && k == 1)// O nome fica na posicao 1 na struct que vai para o arquivo
                {
                    contador++; // Contador para ver quantas vezes o nome aparece
                    strcpy(infopessoa, dados_pessoa); // Copio para outra string para depois apresentar o nome se so entrar uma vez nessa condicao
                }
                token = strtok(NULL, ",");
            }
        }
        if(contador == 0)// Caso nao entre nenhuma vez na condicao
        {
            printf("\nNao foi possivel encontrar esta pessoa\nVerifique a escrita e tente novamente.\n\n");
        }
        else if(contador > 1)// caso entre mais de uma vez(nomes repetidos)
        {
            printf("\nForam encontradas mais de uma pessoa:\n\n");
            fseek(pessoas_txt, 0, SEEK_SET);
            printf("---------------------------------------------------------------------------\n");
            while(fgets(lista_pessoas,PESSOA_MAX,pessoas_txt))
            {
                strcpy(dados_pessoa, lista_pessoas);
                token = strtok(lista_pessoas, ",");
                k = 0;
                while(token != NULL)
                {
                    k++;
                    if(strstr(token, pessoa_desejada) && k == 1)// Verifico se o nome da pessoa eh igual ao digitado
                    {
                        printf("%s", dados_pessoa);// Printo todas as pessoas pois podem existir pessoas diferentes com nomes iguais
                        printf("---------------------------------------------------------------------------\n");
                    }
                    token = strtok(NULL, ",");
                }

            }

            printf("\n\n");
        }
        else if(contador == 1)// Caso entre apenas uma vez, sera essa pessoa
        {
            printf("\nSeguem as informacoes da pessoa desejada: \n\n");
            printf("---------------------------------------------------------------------------\n");
            printf("%s", infopessoa);// Struct armazenada mais cedo
            printf("---------------------------------------------------------------------------\n");
            printf("\n\n");
        }
    }
    else
    {
        printf("Nao foi possivel abrir o arquivo :(\n");
        printf("Voce cadastrou alguma pessoa?\n\n");
    }

    system("pause");
    system("cls");

    fclose(pessoas_txt);
}

//---------Exclui Pessoa---------------------------------------------------------------------------------------
void excluipessoa()// Procedimento que confirma ou nao a exclusao
{
    system("cls");
    FILE *original;
    char lista_pessoas[PESSOA_MAX]; // String para armazenar os dados das pessoas para verificacao
    char opcao[2];
    int contador = 0;        // Para a listagem de pessoas

    original = fopen("pessoas.txt", "rb");// Abrindo o arquivo existente com as pessoas

    if(original)
    {
        do
        {
            printf("Deseja ver todas as pessoas cadastradas antes de excluir alguem?(S/N): ");
            fflush(stdin);
            scanf("%[^\n]s", opcao);
            strupr(opcao);
        }while(strcmp(opcao, "N") != 0 && strcmp(opcao, "S") != 0);
        if(strcmp(opcao, "N") == 0)
        {
            fclose(original);
            confirmaexclusao(original);// Chamando o procedimento de exclusao sem mostrar a lista
        }
        else if(strcmp(opcao, "S") == 0)
        {
            // Listando as pessoas ja cadastradas com todos os seus dados
            printf("Essas sao todas as pessoas cadastradas ate o momento: \n");
            printf("\n");
            fseek(original, 0, SEEK_SET);
            while(fgets(lista_pessoas,PESSOA_MAX,original))
            {
                printf("- ");
                printf("%s",lista_pessoas);
                contador++;
            }
            if(contador == 0)
            {
                printf("Ninguem foi cadastrado ate o momento.\n\n");
                system("pause");
                system("cls");
            }
            else
            {
                printf("\n");
                fclose(original);
                confirmaexclusao(original);
            }
        }
    }
    else
    {
        printf("Nao foi possivel abrir o arquivo de pessoas.\n");
        printf("Verifique se voce ja cadastrou alguem.\n\n");
        system("pause");
        system("cls");
    }

    fclose(original);

}

//---------Confirma Exclusao-----------------------------------------------------------------------------------
void confirmaexclusao()// Procedimento que exclui a pessoa desejada
{
    FILE *alterado, *original;
    char pessoa_desejada[NOME_MAX];// Nome da pessoa que deseja excluir
    char lista_pessoas[PESSOA_MAX];// String para armazenar os dados das pessoas para verificacao
    int  i = 1, contador = 0, numero, k;// Contadores para verificacoes futuras
    char *nome_pessoa;// Para armazenar o nome de cada pessoa
    char infopessoa[PESSOA_MAX], dados_pessoa[PESSOA_MAX];// Strings para armazenar as infos das pessoas
    char opcao[2];

    alterado = fopen("alterado.txt", "w+b");// Criando um arquivo novo de saída
    original = fopen("pessoas.txt", "rb");// Abrindo o arquivo existente com as pessoas

    system("pause");
    printf("\n");
    printf("Digite o nome ou sobrenome da pessoa que deseja excluir: ");
    fflush(stdin);
    scanf("%[^\n]s", pessoa_desejada);// Obtendo o nome desejado para exclusao
    strupr(pessoa_desejada);

    if(original)
    {
        if(alterado)
        {
            fseek(original, 0, SEEK_SET);
            while(fgets(lista_pessoas,PESSOA_MAX,original))
            {
                k = 0;
                strcpy(dados_pessoa, lista_pessoas);
                // Dividindo a struct PESSOA
                nome_pessoa = strtok(lista_pessoas, ",");
                while(nome_pessoa)
                {
                    k++;
                    if(k == 1)
                    {
                        if(strstr(nome_pessoa, pessoa_desejada))
                        {
                            contador++; // Contador para ver quantas vezes o nome aparece
                            strcpy(infopessoa, dados_pessoa); // Copio para outra string para exclusao sem verificacao caso o nome so apareca uma vez
                        }
                    }
                    nome_pessoa = strtok(NULL, ",");
                }
            }
            if(contador == 0)// Caso nao entre nenhuma vez na condicao
            {
                printf("\nNao foi possivel encontrar esta pessoa\nVerifique a escrita e tente novamente.\n\n");
            }
            else if(contador > 1)// Caso entre mais de uma vez(nomes repetidos)
            {
                printf("Foram encontradas mais de uma pessoa:\n\n");
                fseek(original, 0, SEEK_SET);
                while(fgets(lista_pessoas,PESSOA_MAX,original))
                {
                    k = 0;
                    strcpy(dados_pessoa, lista_pessoas);
                    // Dividindo a struct PESSOA
                    nome_pessoa = strtok(lista_pessoas, ",");
                    while(nome_pessoa)
                    {
                        k++;
                        if(k == 1)
                        {
                            if(strstr(nome_pessoa, pessoa_desejada))
                            {
                                printf("%d-", i);// Listando as pessoas de maneira ordenada para futura escolha
                                printf("%s",dados_pessoa);
                                i++;
                            }
                        }
                        nome_pessoa = strtok(NULL, ",");
                    }
                }
                do
                {
                    printf("\nDigite o numero da pessoa que deseja excluir: ");
                    fflush(stdin);
                    scanf("%d", &numero);
                }while(numero < 1 || numero > i-1);
                i = 1;                              // Para listagem ordenada
                fseek(original, 0, SEEK_SET);
                while(fgets(lista_pessoas,PESSOA_MAX,original))
                {
                    k = 0;
                    strcpy(dados_pessoa, lista_pessoas);
                    nome_pessoa = strtok(lista_pessoas, ",");
                    while(nome_pessoa)
                    {
                        k++;
                        if(k == 1)
                        {
                            if(strstr(nome_pessoa, pessoa_desejada))// Verifico se o nome eh igual
                            {
                                if(i != numero)
                                {
                                    fseek(alterado,0,SEEK_END);
                                    fputs(dados_pessoa,alterado);// Escrevo caso o nome seja igual porem nao o escolhido
                                }
                                else
                                {
                                    do
                                    {
                                        // Verifico se deseja-se realmente excluir a pessoa
                                        printf("Tem certeza que deseja excluir os dados de %s?(S/N): ", nome_pessoa);
                                        fflush(stdin);
                                        scanf("%[^\n]s", opcao);
                                        strupr(opcao);
                                    }while(strcmp(opcao, "N") != 0 && strcmp(opcao, "S") != 0);
                                    if(strcmp(opcao, "S") == 0)
                                    {
                                        printf("\nDados de %s excluidos com sucesso :)\n\n", nome_pessoa);// Nao escrevo o nome no novo arquivo
                                    }
                                    else
                                    {
                                        fseek(alterado,0,SEEK_END);
                                        fputs(dados_pessoa,alterado);
                                        printf("\nDados de %s preservados com sucesso :)\n\n", nome_pessoa);
                                    }
                                }
                                i++;
                            }
                            else
                            {
                                fseek(alterado,0,SEEK_END);
                                fputs(dados_pessoa,alterado);// Escrevo no arquivo novo caso nao seja a pessoa a ser excluida
                            }
                        }
                        nome_pessoa = strtok(NULL, ",");
                    }
                }
                fclose(alterado);
                fclose(original);
                remove("pessoas.txt");// Removo o arquivo original
                rename("alterado.txt","pessoas.txt");// Renomeio o novo arquivo para o nome do arquivo antigo
            }
            else if(contador == 1)
            {
                fseek(original, 0, SEEK_SET);
                while(fgets(lista_pessoas,PESSOA_MAX,original))
                {
                    k = 0;//Para pegar apenas o nome na divisao de tokens
                    strcpy(dados_pessoa, lista_pessoas);
                    nome_pessoa = strtok(lista_pessoas, ",");
                    while(nome_pessoa)
                    {
                        k++;
                        if(k == 1)
                        {
                            if(strstr(infopessoa, dados_pessoa))
                            {
                                do
                                {
                                    printf("Tem certeza que deseja excluir os dados de %s?(S/N): ", nome_pessoa);
                                    fflush(stdin);
                                    scanf("%[^\n]s", opcao);
                                    strupr(opcao);
                                }
                                while(strcmp(opcao, "N") != 0 && strcmp(opcao, "S") != 0);
                                if(strcmp(opcao, "S") == 0)
                                {
                                    printf("\nDados de %s excluidos com sucesso :)\n\n", nome_pessoa);
                                }
                                else
                                {
                                    fseek(alterado,0,SEEK_END);
                                    fputs(dados_pessoa,alterado);
                                    printf("\nDados de %s preservados com sucesso :)\n\n", nome_pessoa);
                                }
                            }
                            else
                            {
                                fseek(alterado,0,SEEK_END);
                                fputs(dados_pessoa,alterado);
                            }
                        }
                        nome_pessoa = strtok(NULL, ",");
                    }
                }
                fclose(alterado);
                fclose(original);
                remove("pessoas.txt");
                rename("alterado.txt","pessoas.txt");
            }
        }
        else
        {
            printf("Nao foi possivel criar o arquivo novo de pessoas :(\n");
        }
    }
    else
    {
        printf("\n\nERRO\n\n\n");
    }

    system("pause");
    system("cls");
    fclose(original);
    fclose(alterado);
    remove("alterado.txt");// Caso saia das condicoes sem excluir o arquivo novo, excluo aqui para nao ocorrer algum tipo de problema
}

//---------Relatorio Final-------------------------------------------------------------------------------------
void relatoriofinal()// Procedimento para mostrar o relatorio das pessoas
{
    system("cls");

    FILE *pessoas_txt;
    char pessoa_dados[PESSOA_MAX], idade[4], sexo[1];// Armazenar os dados das pessoas
    int i = 0, k = 0;                                // Para dividir as condicoes do token
    int idadeint;                                    // Para transformar a idade em inteiro para contar pro relatorio
    double homem = 0, mulher = 0, habitante = 0, zeroquinze = 0, dseisvnove = 0, trtqnove = 0, cinqsess = 0, acima60 = 0; // Para somas
    char *token, *token2;                            // Para dividir as informacoes no txt

    pessoas_txt = fopen("pessoas.txt", "rb");



    if(pessoas_txt)
    {
        // Somando contadores de idade e de sexo
        while(fgets(pessoa_dados, PESSOA_MAX, pessoas_txt))
        {
            // Processo de separacao de dados
            token = strtok(pessoa_dados, ":");
            i = 0;
            while(token != NULL)
            {
                i++;
                if(i == 2)
                {
                    strcpy(token2, token);
                }
                if(i == 3)
                {
                    strcpy(sexo, token);
                }
                token = strtok(NULL, ":");
            }
            k = 0;
            do
            {
                idade[k] = token2[k];
                k++;
            }while(token2[k]!=',');
            idadeint = atoi(idade);
            // Soma para porcentagem
            if(sexo[0] == 'M')
            {
                homem++;
            }
            else if(sexo[0] == 'F')
            {
                mulher++;
            }
            if(idadeint >= 0 && idadeint < 16)
            {
                zeroquinze++;
            }
            else if(idadeint > 15 && idadeint < 30)
            {
                dseisvnove++;
            }
            else if(idadeint > 29 && idadeint < 50)
            {
                trtqnove++;
            }
            else if(idadeint > 49 && idadeint < 61)
            {
                cinqsess++;
            }
            else
            {
                acima60++;
            }
            habitante++;
        }
        if(habitante > 0)
        {
            printf("Segue o Relatorio de Vacinacao:\n\n");
            // Contas para a porcentagem final
            homem *= 100;
            homem /= habitante;
            mulher *= 100;
            mulher /= habitante;
            zeroquinze *= 100;
            zeroquinze /= habitante;
            dseisvnove *= 100;
            dseisvnove /= habitante;
            trtqnove *= 100;
            trtqnove /= habitante;
            cinqsess *= 100;
            cinqsess /= habitante;
            acima60  *= 100;
            acima60 /= habitante;
            printf("--------------------------------------\n");
            printf("Porcentagem de homens: %.2lf%%\n", homem);
            printf("--------------------------------------\n");
            printf("Porcentagem de mulheres: %.2lf%%\n", mulher);
            printf("--------------------------------------\n");
            printf("Porcentagem de 0 a 15 anos: %.2lf%%\n", zeroquinze);
            printf("--------------------------------------\n");
            printf("Porcentagem de 16 a 29 anos: %.2lf%%\n", dseisvnove);
            printf("--------------------------------------\n");
            printf("Porcentagem de 30 a 49 anos: %.2lf%%\n", trtqnove);
            printf("--------------------------------------\n");
            printf("Porcentagem de 50 a 60 anos: %.2lf%%\n", cinqsess);
            printf("--------------------------------------\n");
            printf("Porcentagem acima dos 60 anos: %.2lf%%\n", acima60);
            printf("--------------------------------------\n\n");
        }
        else
        {
            printf("\nNenhuma pessoa foi cadastrada ate o momento.\n\n");
        }
    }
    else
    {
        printf("Nao foi possivel abrir o arquivo :(");
        printf("\nVoce cadastrou alguem???\n\n");
    }

    system("pause");
    system("cls");

    fclose(pessoas_txt);
}

//---------Menu------------------------------------------------------------------------------------------------
int menu() // Funcao que retorna o menu para a funcao principal
{

    int i;
    int opcoes = 0;

    printf("\n");
    for(i = 0; i < 50; i++) // Printa as barras que decoram o menu
    {
        printf("%c", 254);
    }
    printf("\n");
    printf("1) Cadastrar Estado\n");
    printf("2) Cadastrar Cidade\n");
    printf("3) Cadastrar Pessoa\n");
    printf("4) Listar pessoas por Estado\n");
    printf("5) Listar pessoas por Cidade\n");
    printf("6) Consultar Pessoa por Nome\n");
    printf("7) Excluir pessoa\n");
    printf("8) Gerar relatorio de vacinacao\n");
    printf("9) Encerrar programa\n");
    for(i = 0; i < 50; i++)
    {
        printf("%c", 254);
    }
    printf("\n\n");
    fflush(stdin);
    scanf("%d", &opcoes);   // Le a opcao que o usuario deseja

    return opcoes;

}

//---------Tela Inicial----------------------------------------------------------------------------------------
void telainicial()// A tela inicial mostrada antes do menu para informacoes sobre o programa
{
    int i;

    for(i = 0; i < 51; i++)
    {
        printf("%c", 254);                                // Desta parte até o "system(pause)" são prints para decorar a tela inicial onde está
    }                                                     // escrito "Registro Demografico de Vacinacao" e a tela seguinte
    printf("\n\n");
    printf("                                           ");
    for(i = 0; i < 4; i++)
    {
        printf("%c", 219);
    }
    printf("\n");
    printf("                                           ");
    for(i = 0; i < 4; i++)
    {
        printf("%c", 219);
    }
    printf("\n");
    printf("Registro Demografico de Vacinacao      ");
    for(i = 0; i < 12; i++)
    {
        printf("%c", 219);
    }
    printf("\n");
    printf("do Ministerio da Saude                 ");
    for(i = 0; i < 12; i++)
    {
        printf("%c", 219);
    }
    printf("\n");
    printf("                                           ");
    for(i = 0; i < 4; i++)
    {
        printf("%c", 219);
    }
    printf("\n");
    printf("                                           ");
    for(i = 0; i < 4; i++)
    {
        printf("%c", 219);
    }
    printf("\n\n");

    for(i = 0; i < 51; i++)
    {
        printf("%c", 254);
    }
    printf("\n\n");
    system("pause");
    system("cls");
    printf("Ola! Seja muito bem vindo.\n\n");
    printf("Nesse programa voce podera cadastrar e\narmazenar dados de pessoas que foram vacinadas.\n\n");
    printf("Cada pessoa sera cadastrada a partir de:\n");
    printf("- Seu nome completo;                     ");
    for(i = 0; i < 4; i++)
    {
        printf("%c", 219);
    }
    printf("\n");
    printf("- Sua idade;                             ");
    for(i = 0; i < 4; i++)
    {
        printf("%c", 219);
    }
    printf("\n");
    printf("- Seu sexo;                          ");            // Todos esses prints em for com 219 ou 254 são para estetica
    for(i = 0; i < 12; i++)
    {
        printf("%c", 219);
    }
    printf("\n");
    printf("- Sua data de nascimento;            ");
    for(i = 0; i < 12; i++)
    {
        printf("%c", 219);
    }
    printf("\n");
    printf("- Sua cidade;                            ");
    for(i = 0; i < 4; i++)
    {
        printf("%c", 219);
    }
    printf("\n");
    printf("- E sua unidade da federacao.            ");
    for(i = 0; i < 4; i++)
    {
        printf("%c", 219);
    }
    printf("\n\n");
    printf("Agora vamos as opcoes:\n\n");
    system("pause");
    system("cls");
}
