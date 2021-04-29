#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define NOME_MAX 1000
#define CIDADE_MAX 50
#define PESSOA_MAX 1100
#define DATA_MAX 11
#define UF_MAX 500
#define LOCAL_MAX 60

//copiar logica de divisao da struct no relatoriofinal para listacidade e listaestado

typedef struct // struct que armazena as informações de uma pessoa
{
    char nome[NOME_MAX];
    char sexo[2];
    char data[DATA_MAX];
    char cidade[CIDADE_MAX];
    char UF[3];
    int idade;
} PESSOA;

typedef struct // struct que armazena as informações de uma cidade
{
    char cidade[CIDADE_MAX];
    char UF[3];
} CIDADE;

// Declaracoes das funcoes auxiliares
void cadastrapessoa(PESSOA habitante);
void registracidade();
void registraestado();
void registrapessoa(PESSOA habitante);
void listaestado(PESSOA habitante);
void listacidade(PESSOA habitante);
void consultapessoa();
void excluipessoa();
void relatoriofinal();
int verificanome(PESSOA habitante);
int verificadata(PESSOA habitante);
int verificacidade_UF(PESSOA habitante);
int verificacidade(PESSOA habitante);
int verificaUF(PESSOA habitante);
char menu();
void telainicial();
int calculaidade(PESSOA habitante);

int main()
{
    int opcoes;
    PESSOA habitante;

    telainicial();

    do
    {
        opcoes = menu();
        fflush(stdin);
        if(opcoes == 1)
        {
            registraestado();
        }

        if(opcoes == 2)
        {
            registracidade();
        }

        if(opcoes == 3)
        {
            cadastrapessoa(habitante);
        }

        if(opcoes == 4)
        {
            listaestado(habitante);
        }

        if(opcoes == 5)
        {
            listacidade(habitante);
        }

        if(opcoes == 6)
        {
            consultapessoa();
        }

        if(opcoes == 7)
        {
            excluipessoa();
        }

        if(opcoes == 8)
        {
            relatoriofinal();
        }

        if(opcoes < 1 || opcoes > 9)
        {
            printf("Se quiser finalizar o programa, digite 9 e aperte enter;\ncaso tenha digitado errado, pode continuar a mexer como quiser. :)\n\n");
            system("pause");
            system("cls");
        }

    }
    while(opcoes!=9);

    return 0;
}

//---------Calcula Idade---------------------------------------------------------------------------------------
int calculaidade(PESSOA habitante) // funcao que calcula a idade do habitante a partir do ano
{

    int i;
    int idade = 0;
    int p = 0;
    char ano[5];
    for(int k = 6; k <= 9; k++)
    {
        ano[p] = habitante.data[k];
        p++;
    }
    int anoi = atoi(ano);// convertendo o ano obtido na string acima para int

    if((anoi%100 != 0) && (anoi%4 == 0) && (anoi%400 == 0) &&
            (habitante.data[0] == '2') && (habitante.data[1] == '9')) // calcula a idade de um individuo caso
    {
        //tenha nascido dia 29 de fevereiro
        for(i = anoi; i < 2021; i++)
        {
            if((anoi%100 != 0) && (anoi%4 == 0) && (anoi%400 == 0))
            {
                idade++;
            }
        }
    }
    else
    {
        idade = 2021 * 365 - anoi * 365;
        idade /= 365;
    }

    return idade;// retornando a idade para a funçao de cadastro
}

//---------Verifica Nome---------------------------------------------------------------------------------------
int verificanome(PESSOA habitante)
{
    int nome = 0, erro = 0, espinicio = 0, esp = 0;// para verificacoes de validacao do nome

    for(int i = 0; i < strlen(habitante.nome); i++)
    {
        if((habitante.nome[i] >= 'A'  && habitante.nome[i] <= 'Z'))
        {
            nome++;
            esp = 0;
        }
        else
        {
            erro++;     // se tiver algo alem de letras, nao sera possivel entrar
        }
        if(i == 0 && habitante.nome[i] == ' ')
        {
            espinicio++;// se o nome comecar com espacos, nao permite cadastro
        }
        if(espinicio == 0 && (isspace(habitante.nome[i])))
        {
            esp++;      //
            erro--;
        }
    }

    if((nome > 1) && (erro == 0) && (espinicio == 0) && (esp == 0))// verificando se o nome nao eh vazio ou se eh formado por letras
    {
        return 0;
    }
    else if(erro > 0 && espinicio == 0)
    {
        return 1;
    }
    else if(nome == 1)
    {
        return 2;
    }
    else if(espinicio > 0)
    {
        return 3;
    }
}

//---------Verifica Data---------------------------------------------------------------------------------------
int verificadata(PESSOA habitante) // funcao para verificar se a data da pessoa cadastrada eh verdadeira
{

    int i, p, anoi, k;
    char data[DATA_MAX], ano[5];

    p = 0;

    for(i = 0; i < 10; i++)
    {
        data[i] = habitante.data[i];// transferindo a data inserida para uma string auxiliar
    }


    for(k = 6; k <= 9; k++)
    {
        ano[p] = data[k];// isolando a string do ano para calculos especificos
        p++;
    }

    p = 0;
    anoi = atoi(ano);

    // a partir daqui são verificacoes para saber se a data eh valida

    if(strlen(data) < 10)
    {
        return 1;
    }

    else
    {
        if((data[3] == '0' && data[4] == '1') || (data[3] == '0' && data[4] == '3') ||
                (data[3] == '0' && data[4] == '5') || (data[3] == '0' && data[4] == '7') ||
                (data[3] == '0' && data[4] == '8') || (data[3] == '1' && data[4] == '0') ||
                (data[3] == '1' && data[4] == '2'))
        {
            if((data[0] == '0' && data[1] > '1' && data[1] <= '9') || (data[0] == '1' &&
                    data[1] >= '0' && data[1] <= '9') || (data[0] == '2' && data[1] >= '0' &&
                            data[1] <= '9') || (data[0] == '3' && data[1] >= '0' && data[1] <= '1'))
            {
                if(data[2] == '/' && data[5] == '/')
                {
                    if(anoi > 2021 || anoi < 1890)
                    {
                        return 2;// retorna 2 caso o ano seja do futuro ou mais antigo que a pessoa mais velha que ja viveu
                    }
                    return 0;// retorna 0 caso nao tenha erro
                }
            }
        }

        if((data[3] == '0' && data[4] == '4') || (data[3] == '0' && data[4] == '6') ||
                (data[3] == '0' && data[4] == '9') || (data[3] == '1' && data[4] == '1'))
        {
            if((data[0] == '0' && data[1] > '1' && data[1] <= '9') || (data[0] == '1' &&
                    data[1] >= '0' && data[1] <= '9') || (data[0] == '2' && data[1] >= '0' &&
                            data[1] <= '9') || (data[0] == '3' && data[1] == '0'))
            {
                if(data[2] == '/' && data[5] == '/')
                {
                    if(anoi > 2021 || anoi < 1890)
                    {
                        return 2;
                    }
                    return 0;
                }
            }
        }

        if(data[3] == '0' && data[4] == '2')
        {
            if((data[0] == '0' && data[1] > '1' && data[1] <= '9') || (data[0] == '1' &&
                    data[1] >= '0' && data[1] <= '9') || (data[0] == '2' && data[1] >= '0' &&
                            data[1] <= '8'))
            {
                if(data[2] == '/' && data[5] == '/')
                {
                    if(anoi > 2021 || anoi < 1890)
                    {
                        return 2;// retorna 2 caso o ano seja do futuro ou mais antigo que a pessoa mais velha que ja viveu
                    }
                    return 0;
                }
            }
            else if((data[0] == '0' && data[1] > '1' && data[1] <= '9') || (data[0] == '1' &&
                    data[1] >= '0' && data[1] <= '9') || (data[0] == '2' && data[1] >= '0' &&
                            data[1] <= '9'))
            {
                if(data[2] == '/' && data[5] == '/')
                {
                    if((anoi%100 != 0) && (anoi%4 == 0) && (anoi%400 == 0))
                    {
                        if(anoi > 2021 || anoi < 1890)
                        {
                            return 2;// retorna 2 caso o ano seja do futuro ou mais antigo que a pessoa mais velha que ja viveu
                        }
                        return 0;
                    }
                }
            }
        }
        else
        {
            return 1;
        }
    }

    return 1;// retorna erro caso tenha algum erro na data ou ela nao exista

}

//---------Verifica Cidade e UF--------------------------------------------------------------------------------
int verificacidade_UF(PESSOA habitante) // funcao que verifica se a cidade esta registrada
{
    FILE *cidades_registradas_txt;
    int procura_cidade_registrada = 0, procuraUF_igual = 0, certo = 0;
    char cidades_registradas[CIDADE_MAX];
    char cidade_formatada[CIDADE_MAX];
    char cidadetemp[CIDADE_MAX];

    cidades_registradas_txt = fopen("cidades registradas.txt", "rb");

    strcpy(cidadetemp, habitante.cidade);
    strcat(habitante.cidade, "-");
    strcat(habitante.cidade, habitante.UF);
    strcpy(cidade_formatada, habitante.cidade);
    strcpy(habitante.cidade, cidadetemp);
    strcat(cidade_formatada, "\n");

    if(strlen(habitante.cidade)==0)
    {
        return 4;
    }

    if(cidades_registradas_txt)
    {
        while(fgets(cidades_registradas, 1500, cidades_registradas_txt))
        {
            if(strstr(cidades_registradas, habitante.cidade)) // buffer para verificar se a cidade esta registrada)
            {
                procura_cidade_registrada++;                 // contador para verificar quantas vezes a cidade aparece
                if(strstr(cidades_registradas, habitante.UF))// se a cidade for igual, também verifico se a uf é igual
                {
                    procuraUF_igual++;                      // contador para verificar quantas vezes a UF aparece
                }
            }
            if(strcmp(cidade_formatada, cidades_registradas) == 0)
            {
                certo++;
            }
        }
        if(certo == 1)// se a cidade aparece mais de uma vez e a UF apenas uma vez, a cidade eh valida
        {
            return 0;// caso esteja correto
        }
        else if((procura_cidade_registrada > 0) && (procuraUF_igual == 0))// se a cidade aparece mais de uma vez mas a UF nao, a cidade eh invalida
        {
            return 1;// caso a cidade nao esteja cadastrada na UF
        }
        else if((procura_cidade_registrada == 0) && (procuraUF_igual == 0))// se a cidade nao aparece nenhuma vez nem a UF, a cidade eh invalida
        {
            return 3;// caso a cidade nao esteja cadastrada
        }
        else
        {
            return 3;// algum outro erro
        }
    }
    else
        return 2;// caso o arquivo nao abra, provavelmente nenhuma cidade foi cadastrada

    fclose(cidades_registradas_txt);

}

//---------Verifica UF-----------------------------------------------------------------------------------------
int verificaUF(PESSOA habitante)    // funcao que verifica se a UF esta registrada
{
    FILE *uf;   // arquivo pra abrir o txt das UFs
    char uftxt[UF_MAX];    // buffer para armazenar o conteudo do txt, numero 100
    int procurastring = 0;   //string criada pra verificar se a UF digitada esta dentro do .txt das UFs registradas

    uf = fopen("UFregistrada.txt", "rb");

    if(uf)
    {
        if(strlen(habitante.UF) == 2)
        {
            do
            {
                fscanf(uf,"%s",uftxt);
                if(strstr(uftxt, habitante.UF))
                {
                    procurastring++;// se a UF aparece, o contador eh somado
                }
            }
            while(!feof(uf));
            if(procurastring != 0)
            {
                return 0;// caso seja valida
            }
            else
            {
                return 1;// caso nao apareça no txt
            }
        }
        else
        {
            return 1;// caso a escrita seja invalida
        }
    }
    else
    {
        return 2;// caso o arquivo nao abra, provavelmente nenhuma UF foi cadastrada
    }

    fclose(uf);

}

//---------Verifica Cidade-------------------------------------------------------------------------------------
int verificacidade(PESSOA habitante)
{
    FILE *cidades_registradas_txt;
    int procura_cidade_registrada = 0, certo = 0;
    char cidades_registradas[CIDADE_MAX];
    char cidade_formatada[CIDADE_MAX];
    char cidadetemp[CIDADE_MAX];

    cidades_registradas_txt = fopen("cidades registradas.txt", "rb");

    if(strlen(habitante.cidade)==0)
    {
        return 4;
    }

    if(cidades_registradas_txt)
    {
        while(fgets(cidades_registradas, 1500, cidades_registradas_txt))
        {
            if(strstr(cidades_registradas, habitante.cidade)) // buffer para verificar se a cidade esta registrada)
            {
                procura_cidade_registrada++;                 // contador para verificar quantas vezes a cidade aparece
            }
            if(strcmp(cidade_formatada, cidades_registradas) == 0)
            {
                certo++;
            }
        }
        if(certo == 1)// se a cidade aparece mais de uma vez e a UF apenas uma vez, a cidade eh valida
        {
            return 0;// caso esteja correto
        }
        else if(procura_cidade_registrada > 0)// se a cidade aparece mais de uma vez mas a UF nao, a cidade eh invalida
        {
            return 0;// caso a cidade nao esteja cadastrada na UF
        }
        else if((procura_cidade_registrada == 0))// se a cidade nao aparece nenhuma vez nem a UF, a cidade eh invalida
        {
            return 3;// caso a cidade nao esteja cadastrada
        }
        else
        {
            return 3;// algum outro erro
        }
    }
    else
        return 2;// caso o arquivo nao abra, provavelmente nenhuma cidade foi cadastrada

    fclose(cidades_registradas_txt);

}

//---------Cadastra Pessoa-------------------------------------------------------------------------------------
void cadastrapessoa(PESSOA habitante)
{
    /* funcao que ha de cadastrar a pessoa, primeiro verificando
    se os seus dados estão corretos, para ai sim registra-la no banco*/

    system("cls");

    printf("Digite o nome da pessoa: ");
    fflush(stdin);
    scanf("%[^\n]s", habitante.nome);// lendo o nome
    strupr(habitante.nome);// faco varias vezes pelo codigo para facilitar verificacao
    if(verificanome(habitante) == 0)// verificando se o nome nao eh vazio ou se eh formado por letras
    {
        printf("Digite o sexo da pessoa (M ou F): ");
        fflush(stdin);
        scanf("%[^\n]s", habitante.sexo);// lendo o sexo
        strupr(habitante.sexo);
        if(strcmp(habitante.sexo, "M") != 0 && strcmp(habitante.sexo, "F") != 0)// verificando se o sexo eh valido
        {
            printf("\nSexo invalido\n\n");
            system("pause");
            system("cls");
        }
        else
        {
            printf("Digite a data de nascimento da pessoa (DD/MM/AAAA): ");
            fflush(stdin);
            scanf("%[^\n]s", habitante.data);// lendo a data
            habitante.idade = calculaidade(habitante);// calculando a idade
            if(verificadata(habitante) == 2)/*  se o ano eh depois de 2021 ou muito antigo
                                                (mais antigo do que a pessoa mais velha que ja viveu) */
            {
                printf("\nEssa pessoa eh uma viajante do tempo :O\n\n");
                system("pause");
                system("cls");
            }
            else if(verificadata(habitante) == 1)// se a data foi digitada incorretamente ou nao existe
            {
                printf("\nEssa data eh invalida\n\n");
                system("pause");
                system("cls");
            }
            else if(verificadata(habitante) == 0)
            {
                printf("Digite a UF de onde a pessoa foi vacinada: ");
                fflush(stdin);
                scanf("%[^\n]s", habitante.UF);
                strupr(habitante.UF);
                if(verificaUF(habitante) == 1)// se a uf digitada for invalida (tamanho > 2 ou < 2) ou nao for registrada
                {
                    printf("\nEssa UF nao esta registrada ou eh invalida\nVerifique a escrita e tente novamente.\n\n");
                    system("pause");
                    system("cls");
                }
                else if(verificaUF(habitante) == 2)
                {
                    printf("\nNao foi possivel abrir o arquivo :(\n");
                    printf("Voce ja cadastrou alguma UF?\n\n");
                    system("pause");
                    system("cls");
                }
                else if(verificaUF(habitante) == 0)
                {
                    printf("Digite agora uma cidade registrada nessa UF: ");
                    fflush(stdin);
                    scanf("%[^\n]s", habitante.cidade);
                    strupr(habitante.cidade);
                    if(verificacidade_UF(habitante) == 1)
                    {
                        printf("\nEsta cidade pode estar registrada, porem nao nessa UF.\n");
                        printf("Verifique a escrita e tente novamente.\n\n");
                        system("pause");
                        system("cls");
                    }
                    else if(verificacidade_UF(habitante) == 2)
                    {
                        printf("Nao foi possivel abrir o arquivo :(\n");
                        printf("Voce ja cadastrou alguma cidade?\n\n");
                        system("pause");
                        system("cls");
                    }
                    else if(verificacidade_UF(habitante) == 3)
                    {
                        printf("\nEsta cidade nao esta registrada ou eh invalida.\n");
                        printf("Verifique a escrita e tente novamente.\n\n");
                        system("pause");
                        system("cls");
                    }
                    else if(verificacidade_UF(habitante) == 4)
                    {
                        printf("\nPor favor, digite algo para que possa ser feita a verificacao.\n\n");
                        system("pause");
                        system("cls");
                    }
                    else if(verificacidade_UF(habitante) == 0)
                    {
                        registrapessoa(habitante);// chama o procedimento que salva no arquivo apos verificacoes
                    }
                }
            }
        }
    }
    else if(verificanome(habitante) == 1)
    {
        printf("\nO nome deve ser formado apenas por letras\n\n");
        system("pause");
        system("cls");
    }
    else if(verificanome(habitante) == 2)
    {
        printf("\nDigite pelo menos mais de uma letra para o nome\n\n");
        system("pause");
        system("cls");
    }
    else if(verificanome(habitante) == 3)
    {
        printf("\nPor favor nao digite espaco(s) antes do nome\n\n");
        system("pause");
        system("cls");
    }

}

//---------Registra Estado-------------------------------------------------------------------------------------
void registraestado() // procedimento que registra os estados por suas siglas no arquivo
{
    FILE *estados_registrados_txt;
    char UFs_registradas[100], UFnova[4];
    char *procuraUF_registrada;
    int contador = 0;

    estados_registrados_txt = fopen("UFregistrada.txt", "a+b"); // abrindo o arquivo das UFs registradas
    printf("\nDigite a UF que deseja registrar: ");
    fflush(stdin);
    scanf("%[^\n]s", UFnova);   // armazenando a UF a ser cadastrada
    strupr(UFnova);             // transformando em maiusculo para facilitar a verificacao


    if(estados_registrados_txt)     // verificando se o arquivo foi criado ou ja existe
    {
        do
        {
            fscanf(estados_registrados_txt, "%[^\n]s", UFs_registradas);// transferindo o texto do txt para uma string
        }
        while(!feof(estados_registrados_txt)); // realizando a funcao ate o fim do arquivo
        procuraUF_registrada = strstr(UFs_registradas, UFnova); // buffer que verifica se a uf digitada ja esta registrada
        for(int j = 0; j < 3; j++)
        {
            if(UFnova[j] > 64 && UFnova[j] < 91)
            {
                contador++;// verificando a escrita da UF
            }
        }
        if(contador == 2)                         // verifica se a UF eh valida
        {
            if(procuraUF_registrada == NULL)      // verifica se a UF ja esta registrada
            {
                fseek(estados_registrados_txt,0,SEEK_END);      // colocando o ponteiro no fim do .txt
                fprintf(estados_registrados_txt,"%s ",UFnova); // escrevendo a UF inserida no arquivo
                printf("\nUF armazenada com sucesso :D\n\n");
                system("pause");
                system("cls");
            }
            else
            {
                printf("\nEssa UF ja esta registrada :)\n\n");
                system("pause");
                system("cls");
            }
        }
        else
        {
            printf("\nEssa UF nao e valida, verifique a escrita e tente novamente...\n");
            system("pause");
            system("cls");
        }
    }
    else
    {
        printf("\nNao foi possivel abrir/criar o arquivo :(\n\n");
        system("pause");
        system("cls");
    }

    fclose(estados_registrados_txt);
}

//---------Registra Cidade-------------------------------------------------------------------------------------
void registracidade() // procedimento que registra as cidades no arquivo
{
    FILE *cidades_registradas_txt, *UFs_registradas_txt;
    CIDADE cidadenova;
    int contadorcidade = 0, tamanho_cidade, contadorUF = 0, tamanho_UF, procura_cidade_registrada = 0;
    int procuraUF_registrada = 0, erro = 0;
    char UFs_registradas[100], cidades_registradas[500], nome_formatado[550];

    cidades_registradas_txt = fopen("cidades registradas.txt", "a+b");  // abrindo o arquivo das cidades já registradas
    UFs_registradas_txt = fopen("UFregistrada.txt", "a+b");

    printf("Digite o nome da cidade que deseja registrar: ");
    fflush(stdin);
    scanf("%[^\n]s", cidadenova.cidade);// buffer para armazenar a cidade a ser registrada
    printf("Digite a UF a qual essa cidade pertence: ");
    fflush(stdin);
    scanf("%[^\n]s", cidadenova.UF);    // buffer para armazenar a UF da cidade
    strupr(cidadenova.cidade);
    strupr(cidadenova.UF);          // transformando as duas strings em maiusculo para melhor verificacao

    tamanho_cidade = strlen(cidadenova.cidade); // armazenando o tamanho da string para verificar se eh formada apenas por letras
    tamanho_UF = strlen(cidadenova.UF);         // armazenando o tamanho da string para verificar se esta escrita corretamente

    for(int i = 0; i < tamanho_cidade; i++)
    {
        if((cidadenova.cidade[i] > 64 && cidadenova.cidade[i] < 91) || (cidadenova.cidade[i] == 32))
        {
            contadorcidade++;// conta quantas letras tem na string
        }
        else
        {
            erro++;
        }
    }

    strcpy(nome_formatado, cidadenova.cidade);
    strcat(nome_formatado, "-");
    strcat(nome_formatado, cidadenova.UF);// buffer para verificacao de uf caso cidade seja igual
    strcat(nome_formatado, "\n");

    for(int k = 0; k < 2; k++)
    {
        if(cidadenova.UF[k] > 64 && cidadenova.UF[k] < 91)
        {
            contadorUF++;// conta quantas letras tem na string
        }
    }
    if(cidades_registradas_txt)
    {
        if((contadorcidade > 1) && erro == 0)  // verifica se a cidade esta escrita corretamente
        {
            if(UFs_registradas_txt)
            {
                if(tamanho_UF == 2 && contadorUF == 2)  // verifica se a UF esta escrita corretamente
                {
                    do
                    {
                        fscanf(UFs_registradas_txt,"%s\n", UFs_registradas);// transferindo o texto do txt para uma string
                        if(strstr(UFs_registradas, cidadenova.UF))
                        {
                            procuraUF_registrada++;// se a UF esta no txt, o contador aumenta
                        }
                    }
                    while(!feof(UFs_registradas_txt));
                    if(procuraUF_registrada != 0) // verifica se a UF esta registrada
                    {
                        int procuraUF_igual = 0;// contador para saber quantas vezes a UF aparece
                        while(fgets(cidades_registradas, 1500, cidades_registradas_txt))
                        {
                            if(strstr(cidades_registradas, cidadenova.cidade)) // buffer para verificar se a cidade esta incluida na string
                            {
                                procura_cidade_registrada++;
                                if(strstr(cidades_registradas, cidadenova.UF))// se a cidade for incluida, também verifico se a uf esta incluida
                                {
                                    if(strcmp(nome_formatado, cidades_registradas) == 0)// se a uf estiver incluida, verifico se a string eh exatamente igual
                                    {
                                        procuraUF_igual++;
                                    }
                                }
                            }
                        }
                        if(procura_cidade_registrada == 0)   // verifica se a cidade ja esta registrada
                        {
                            fseek(cidades_registradas_txt,0,SEEK_END); // colocando o ponteiro no fim do .txt
                            fprintf(cidades_registradas_txt,"%s-%s\n",cidadenova.cidade,cidadenova.UF);
                            printf("\nCidade armazenada com sucesso :)\n\n");
                            system("pause");
                            system("cls");
                        }
                        else
                        {
                            if(procuraUF_igual == 0)  // se a cidade tiver sido igual, porem com UF diferente, eh cadastrada
                            {
                                fseek(cidades_registradas_txt,0,SEEK_END); // colocando o ponteiro no fim do .txt
                                fprintf(cidades_registradas_txt,"%s-%s\n",cidadenova.cidade,cidadenova.UF);
                                printf("\nCidade armazenada com sucesso :)\n\n");
                                system("pause");
                                system("cls");
                            }
                            else
                            {
                                printf("\nA cidade ja esta registrada com essa UF.\n\n");
                                system("pause");
                                system("cls");
                            }
                        }
                    }
                    else
                    {
                        printf("\nA UF nao esta registrada. Registre primeiramente o estado e tente novamente.\n\n");
                        system("pause");
                        system("cls");
                    }
                }
                else
                {
                    printf("\nA UF digitada eh invalida. Verifique a escrita e tente novamente.\n\n");
                    system("pause");
                    system("cls");
                }
            }
            else
            {
                printf("\nNao foi possivel abrir o arquivo :(\n\n");
                system("pause");
                system("cls");
            }
        }
        else if(erro != 0)
        {
            printf("\nA cidade deve conter apenas letras. Verifique a escrita e tente novamente.\n\n");
            system("pause");
            system("cls");
        }
        else if(contadorcidade <= 1)
        {
            printf("\nDigite pelo menos mais de uma letra para cadastrar uma cidade.\n\n");
            system("pause");
            system("cls");
        }
    }
    else
    {
        printf("\nNao foi possivel abrir o arquivo :(\n\n");
        system("pause");
        system("cls");
    }

    fclose(UFs_registradas_txt);
    fclose(cidades_registradas_txt);
}

//---------Registra Pessoa-------------------------------------------------------------------------------------
void registrapessoa(PESSOA habitante) // procedimento que registra as pessoas no arquivo
{
    FILE *txt_pessoas;

    txt_pessoas = fopen("pessoas.txt", "a+b");// abrindo o .txt com as pessoas registradas
    if(txt_pessoas)
    {
        fseek(txt_pessoas,0,SEEK_END);// colocando o ponteiro no fim do .txt
        fprintf(txt_pessoas,"%s,%s-%s,Idade:%d,Sexo:%s \n",
                habitante.nome, habitante.cidade, habitante.UF, habitante.idade, habitante.sexo);// escrevendo toda a struct no arquivo
        printf("Dados de %s armazenados com sucesso!\n\n", habitante.nome);
        system("pause");
        system("cls");
    }
    else
    {
        printf("Erro ao abrir arquivo :(\n\n");
        system("pause");
        system("cls");
    }

    fclose(txt_pessoas);
}

//---------Lista Pessoas por Estado----------------------------------------------------------------------------
void listaestado(PESSOA habitante)// procedimento que lista as pessoas de acordo com suas UFs
{
    system("cls");
    FILE *pessoas_txt, *UFs_registradas_txt;
    int contadorUF = 0;
    char lixo[PESSOA_MAX];  // para separar informacoes
    int i = 0;              // sera necessario para guardar somente o estado
    char estado_linha[3];   // buffer para guardar o estado da pessoa

    pessoas_txt = fopen("pessoas.txt", "rb");
    UFs_registradas_txt = fopen("UFregistrada.txt", "rb"); // abrindo os arquivos das pessoas e das UFs

    lixo[0] = '\0';

    if(pessoas_txt)
    {
        if(UFs_registradas_txt)
        {
            printf("Digite a UF do estado que deseja listar: ");
            fflush(stdin);
            scanf("%[^\n]s", habitante.UF);
            strupr(habitante.UF);
            if(verificaUF(habitante) == 0)// verifica se a estrutura da uf digitada eh valida e esta registrada
            {
                printf("Segue(m) a(s) pessoa(s) registradas neste estado:\n\n");
                char pessoas_registradas[PESSOA_MAX];// buffer pra armazenar as linhas de cada pessoa
                int pessoas = 0;// caso nao tenha nenhuma pessoa, continuara zero
                printf("---------------------------------------------------------------------------\n");
                while(fgets(pessoas_registradas,NOME_MAX,pessoas_txt))
                {
                    i = 0;
                    lixo[0] = '\0';
                    do
                    {
                        lixo[i] = pessoas_registradas[i];
                        i++;
                    }
                    while(pessoas_registradas[i]!=',');
                    do
                    {
                        lixo[i] = pessoas_registradas[i];
                        i++;
                    }
                    while(pessoas_registradas[i]!='-');
                    i++;
                    estado_linha[0] = pessoas_registradas[i];
                    i++;
                    estado_linha[1] = pessoas_registradas[i];// guardando apenas o estado na string
                    if(strcmp(estado_linha, habitante.UF) == 0) // buffer para listar as pessoas pelo estado
                    {
                        printf(pessoas_registradas);
                        printf("---------------------------------------------------------------------------\n");
                        pessoas++;
                    }
                }
                if(pessoas == 0)
                {
                    printf("---------------------------------------------------------------------------\n");
                    printf("\nAinda nao foram cadastradas pessoas neste estado.\n\n");
                    system("pause");
                    system("cls");
                }
                if(pessoas != 0)
                {
                    printf("\n");
                    system("pause");
                    system("cls");
                }
            }
            else if(verificaUF(habitante) == 1)
            {
                printf("\nEsta UF nao foi registrada ou a escrita eh invalida\n");
                printf("Lembre-se: as UFs sao formadas e registradas com apenas duas letras\n\n");
                system("pause");
                system("cls");
            }
        }
        else
        {
            printf("Nao foi possivel abrir o arquivo :(\n");
            printf("Voce cadastrou alguma pessoa?\n\n");
            system("pause");
            system("cls");
        }
    }
    else
    {
        printf("Nao foi possivel abrir o arquivo :(\n");
        printf("Voce cadastrou alguma UF?\n\n");
        system("pause");
        system("cls");
    }

    fclose(pessoas_txt);
    fclose(UFs_registradas_txt);
}

//---------Lista Pessoas por Cidade----------------------------------------------------------------------------
void listacidade(PESSOA habitante)// procedimento que lista as pessoas de acordo com suas cidades
{
    system("cls");
    FILE *pessoas_txt, *cidades_registradas_txt;
    int contadorcidade = 0;
    int pessoas = 0;// verificar quantas pessoas tem na cidade
    int i, numero;
    char cidade[CIDADE_MAX];
    char cidades_registradas[LOCAL_MAX];
    int procuracidade_registrada = 0;
    char pessoas_registradas[PESSOA_MAX];
    int contadorpessoas = 0;

    pessoas_txt = fopen("pessoas.txt", "rb");
    cidades_registradas_txt = fopen("cidades registradas.txt", "rb");

    if(pessoas_txt)
    {
        if(cidades_registradas_txt)
        {
            printf("Digite a cidade que deseja listar: ");
            fflush(stdin);
            scanf("%[^\n]s", habitante.cidade);
            strupr(habitante.cidade);
            if(verificacidade(habitante) == 0)// verifica se a cidade possui apenas letras e esta cadastrada
            {
                while(fgets(cidades_registradas, LOCAL_MAX, cidades_registradas_txt))
                {
                    
                    if(strstr(cidades_registradas, habitante.cidade))
                    {
                        procuracidade_registrada++;
                    }
                }
                if(procuracidade_registrada == 1) // verifica se a UF digitada foi encontrada no txt de estados registrados
                {
                    printf("\nSegue(m) a(s) pessoa(s) desta cidade: \n\n");
                    printf("---------------------------------------------------------------------------\n");
                    while(fgets(pessoas_registradas, PESSOA_MAX, pessoas_txt))// transferindo o txt pra uma string)
                    {
                        if(strstr(pessoas_registradas, habitante.cidade))
                        {
                            printf("%s", pessoas_registradas);
                            printf("---------------------------------------------------------------------------\n");
                            pessoas++;
                        }
                    }
                    printf("\n\n");
                    if(pessoas > 0)
                    {
                        system("pause");
                        system("cls");
                    }
                    else
                    {
                        printf("---------------------------------------------------------------------------\n");
                        printf("\n\nAinda nao foram cadastradas pessoas nesta cidade\n\n");
                        system("pause");
                        system("cls");
                    }
                }
                else if(procuracidade_registrada > 1)
                {
                    printf("\nAs seguintes cidades foram encontradas: \n\n");
                    fseek(cidades_registradas_txt, 0, SEEK_SET);
                    i = 1;
                    while(fgets(cidades_registradas, LOCAL_MAX, cidades_registradas_txt))
                    {
                        if(strstr(cidades_registradas, habitante.cidade))
                        {
                            printf("%d.", i);
                            printf("%s", cidades_registradas);
                            i++;
                        }
                    }
                    do
                    {
                        printf("\nDigite o numero da cidade que deseja listar: ");
                        fflush(stdin);
                        scanf("%d", &numero);
                    }while(numero < 1 || numero > i-1);
                    i = 1;
                    printf("\nSegue(m) a(s) pessoa(s) registrada(s) nessa localizacao:\n\n");
                    printf("---------------------------------------------------------------------------\n");
                    fseek(cidades_registradas_txt, 0, SEEK_SET);
                    while(fgets(cidades_registradas, LOCAL_MAX, cidades_registradas_txt))
                    {
                        if(strstr(cidades_registradas, habitante.cidade))
                        {
                            if(i == numero)
                            {
                                
                                
                            }
                        }
                        
                    }
                    fseek(pessoas_txt, 0, SEEK_SET);
                    pessoas_registradas[0] = '\0';
                    while(fgets(pessoas_registradas, PESSOA_MAX, pessoas_txt))
                    {
                        if((strstr(pessoas_registradas,cidade)))
                        {
                            printf("%s", pessoas_registradas);
                            printf("---------------------------------------------------------------------------\n");
                            contadorpessoas++;
                        }
                    }
                    if(contadorpessoas == 0)
                    {
                        printf("---------------------------------------------------------------------------\n\n");
                        printf("Nao existem pessoas cadastradas nessa localizacao\n\n");
                        system("pause");
                        system("cls");
                    }
                    else
                    {
                        system("pause");
                        system("cls");
                    }
                }
                else if(procuracidade_registrada == 0)
                {
                    printf("\nEssa cidade nao esta registrada.\n\n");
                    system("pause");
                    system("cls");
                }
            }
            else if(verificacidade(habitante) == 1)
            {
                printf("\nEssa cidade eh invalida ou nao esta cadastrada nessa UF\n");
                printf("Verifique a escrita e tente novamente.\n\n");
                system("pause");
                system("cls");
            }
            else if(verificacidade(habitante) == 3)
            {
                printf("\nEssa cidade nao esta cadastrada\n");
                printf("Verifique a escrita e tente novamente\n\n");
                system("pause");
                system("cls");
            }
            else if(verificacidade(habitante) == 4)
            {
                printf("\nPor favor, digite algo para que possa ser feita a verificacao.\n\n");
                system("pause");
                system("cls");
            }
        }
        else
        {
            printf("\nNao foi possivel abrir o arquivo :(\n");
            printf("Voce cadastrou alguma cidade?\n\n");
            system("pause");
            system("cls");
        }
    }
    else
    {
        printf("Nao foi possivel abrir o arquivo :(\n");
        printf("Voce cadastrou alguma pessoa?\n\n");
        system("pause");
        system("cls");
    }

    fclose(cidades_registradas_txt);
    fclose(pessoas_txt);

}

//---------Consulta Pessoa-------------------------------------------------------------------------------------
void consultapessoa()// procedimento que mostra informacoes de uma pessoa em particular
{
    system("cls");
    FILE *pessoas_txt;
    char pessoa_desejada[NOME_MAX], lista_pessoas[PESSOA_MAX], infopessoa[PESSOA_MAX], *nome_pessoa;
    char dados_pessoa[PESSOA_MAX], tamanho_string[PESSOA_MAX];
    int contador = 0, i = 1, numero, j = 0;

    pessoas_txt = fopen("pessoas.txt", "rb");

    if(pessoas_txt)
    {
        printf("Digite o nome ou sobrenome da pessoa que deseja consultar: ");
        fflush(stdin);
        scanf("%[^\n]s", pessoa_desejada);
        strupr(pessoa_desejada);
        while(fgets(lista_pessoas,NOME_MAX,pessoas_txt))
        {
            dados_pessoa[0] = '\0';
            strcpy(dados_pessoa, lista_pessoas);
            nome_pessoa = "\0";
            nome_pessoa = strtok(lista_pessoas, ",");;
            if(strstr(nome_pessoa, pessoa_desejada))
            {
                contador++; // contador para ver quantas vezes o nome aparece
                strcpy(infopessoa, dados_pessoa); // copio para outra string para depois apresentar o nome se so entrar uma vez nessa condicao
            }
        }
        if(contador == 0)// caso nao entre nenhuma vez na condicao
        {
            printf("\nNao foi possivel encontrar esta pessoa\nVerifique a escrita e tente novamente.\n\n");
            system("pause");
            system("cls");
        }
        else if(contador > 1)// caso entre mais de uma vez(nomes repetidos)
        {
            printf("Foram encontradas mais de uma pessoa:\n\n");
            fseek(pessoas_txt, 0, SEEK_SET);
            while(fgets(lista_pessoas,PESSOA_MAX,pessoas_txt))
            {
                dados_pessoa[0] = '\0';
                strcpy(dados_pessoa, lista_pessoas);
                nome_pessoa = "\0";
                nome_pessoa = strtok(lista_pessoas, ",");;
                if(strstr(nome_pessoa, pessoa_desejada))
                {
                    printf("%d-", i);// listando as pessoas de maneira ordenada para futura escolha
                    printf(nome_pessoa);
                    printf("\n");
                    i++;
                }
            }
            do
            {
                printf("\nDigite o numero da pessoa que deseja obter os dados: ");
                fflush(stdin);
                scanf("%d", &numero);
            }
            while(numero < 1 || numero > i-1);
            fseek(pessoas_txt, 0, SEEK_SET);
            i = 1;
            printf("Seguem os dados da pessoa desejada: \n\n");
            while(fgets(lista_pessoas,NOME_MAX,pessoas_txt))
            {
                dados_pessoa[0] = '\0';
                strcpy(dados_pessoa, lista_pessoas);
                nome_pessoa = "\0";
                nome_pessoa = strtok(lista_pessoas, ",");
                if(strstr(nome_pessoa, pessoa_desejada))
                {
                    if(i == numero)
                    {
                        for(j = 0; j < strlen(dados_pessoa)-1; j++)
                        {
                            printf("-");
                        }
                        printf("\n");
                        printf("%s", dados_pessoa);
                        strcpy(tamanho_string, dados_pessoa);
                    }
                    i++;
                }
            }
            for(j = 0; j < strlen(tamanho_string)-1; j++)
            {
                printf("-");
            }
            printf("\n\n");
            system("pause");
            system("cls");
        }
        else if(contador == 1)// caso entre apenas uma vez, sera essa pessoa
        {
            printf("Seguem as informacoes da pessoa desejada: \n\n");
            for(j = 0; j < strlen(infopessoa)-1; j++)
            {
                printf("-");
            }
            printf("\n");
            printf("%s", infopessoa);
            for(j = 0; j < strlen(infopessoa)-1; j++)
            {
                printf("-");
            }
            printf("\n\n");
            system("pause");
            system("cls");
        }
    }
    else
    {
        printf("Nao foi possivel abrir o arquivo :(\n");
        printf("Voce cadastrou alguma pessoa?\n\n");
        system("pause");
        system("cls");
    }

    fclose(pessoas_txt);
}

//---------Exclui Pessoa---------------------------------------------------------------------------------------
void excluipessoa()// procedimento que exclui a pessoa desejada
{
    FILE *original, *alterado;
    char pessoa_desejada[NOME_MAX];// nome da pessoa que deseja excluir
    char lista_pessoas[PESSOA_MAX];// buffer para armazenar os dados das pessoas para verificacao
    int  i = 1, contador = 0, numero;// contadores para verificacoes futuras
    char *nome_pessoa, dados_pessoa[PESSOA_MAX];// buffer para armazenar o nome de cada pessoa
    char infopessoa[PESSOA_MAX];// buffer para armazenar as infos da pessoa caso so exista uma com o nome digitado

    original = fopen("pessoas.txt", "rb");// abrindo o arquivo existente com as pessoas
    alterado = fopen("alterado.txt", "w+b");// criando um arquivo novo de saída

    nome_pessoa = "\0";
    dados_pessoa[0] = '\0';

    if(original)
    {
        if(alterado)
        {
            printf("Digite o nome ou sobrenome da pessoa que deseja excluir: ");
            fflush(stdin);
            scanf("%[^\n]s", pessoa_desejada);
            strupr(pessoa_desejada);
            while(fgets(lista_pessoas,PESSOA_MAX,original))
            {
                dados_pessoa[0] = '\0';
                strcpy(dados_pessoa, lista_pessoas);
                nome_pessoa = "\0";
                nome_pessoa = strtok(lista_pessoas, ",");
                if(strstr(nome_pessoa, pessoa_desejada))
                {
                    contador++; // contador para ver quantas vezes o nome aparece
                    strcpy(infopessoa, dados_pessoa); // copio para outra string para depois apresentar o nome se so entrar uma vez nessa condicao
                }
            }
            if(contador == 0)// caso nao entre nenhuma vez na condicao
            {
                printf("\nNao foi possivel encontrar esta pessoa\nVerifique a escrita e tente novamente.\n\n");
                system("pause");
                system("cls");
            }
            else if(contador > 1)// caso entre mais de uma vez(nomes repetidos)
            {
                printf("Foram encontradas mais de uma pessoa:\n\n");
                fseek(original, 0, SEEK_SET);
                while(fgets(lista_pessoas,PESSOA_MAX,original))
                {
                    nome_pessoa = "\0";
                    nome_pessoa = strtok(lista_pessoas, ",");
                    if(strstr(nome_pessoa, pessoa_desejada))
                    {
                        printf("%d-", i);// listando as pessoas de maneira ordenada para futura escolha
                        printf(nome_pessoa);
                        printf("\n");
                        i++;
                    }
                }
                do
                {
                    printf("\nDigite o numero da pessoa que deseja excluir: ");
                    fflush(stdin);
                    scanf("%d", &numero);
                }while(numero < 1 || numero > i-1);
                i = 1;
                fseek(original, 0, SEEK_SET);
                while(fgets(lista_pessoas,PESSOA_MAX,original))
                {
                    dados_pessoa[0] = '\0';
                    strcpy(dados_pessoa, lista_pessoas);
                    nome_pessoa = "\0";
                    nome_pessoa = strtok(lista_pessoas, ",");
                    if(strstr(nome_pessoa, pessoa_desejada)!=NULL)
                    {
                        if(i != numero)
                        {
                            fseek(alterado,0,SEEK_END);
                            fputs(dados_pessoa,alterado);
                        }
                        else
                        {
                            printf("\nDados de %s excluidos com sucesso :)\n\n", nome_pessoa);
                        }
                        i++;
                    }
                    else
                    {
                        fseek(alterado,0,SEEK_END);
                        fputs(dados_pessoa,alterado);
                    }
                }
                system("pause");
                system("cls");
                fclose(alterado);
                fclose(original);
                remove("pessoas.txt");
                rename("alterado.txt","pessoas.txt");
            }
            else if(contador == 1)
            {
                fseek(original, 0, SEEK_SET);
                while(fgets(lista_pessoas,PESSOA_MAX,original))
                {
                    dados_pessoa[0] = '\0';
                    strcpy(dados_pessoa, lista_pessoas);
                    nome_pessoa = "\0";
                    nome_pessoa = strtok(lista_pessoas, ",");
                    if(strstr(infopessoa, dados_pessoa))
                    {
                        printf("\nDados de %s excluidos com sucesso :)\n\n", nome_pessoa);
                    }
                    else
                    {
                        fseek(alterado,0,SEEK_END);
                        fputs(dados_pessoa,alterado);
                    }
                }
            fclose(alterado);
            fclose(original);
            remove("pessoas.txt");
            rename("alterado.txt","pessoas.txt");
            system("pause");
            system("cls");
            }
        }
        else
        {
        printf("Nao foi possivel criar o arquivo novo de pessoas :(\n");
        system("pause");
        system("cls");
        }
    }
    else
    {
        printf("Nao foi possivel abrir o arquivo de pessoas.\n");
        printf("Verifique se voce ja cadastrou alguem.\n\n");
        system("pause");
        system("cls");
    }


}

//---------Relatorio Final-------------------------------------------------------------------------------------
void relatoriofinal()
{
    FILE *pessoas_txt;
    char pessoa_dados[PESSOA_MAX];              // armazenar os dados das pessoas
    char lixo[PESSOA_MAX], idade[4], sexo[2];   // armazenar informacoes necessarias ou o que seria apenas temporario
    int i = 0, j = 0;                           // para contar os caracteres
    int idadeint;                               // para transformar a idade em inteiro
    // para contar pro relatorio
    double homem = 0, mulher = 0, habitante = 0;
    double zeroquinze = 0, dseisvnove = 0, trtqnove = 0;
    double cinqsess = 0, acima60 = 0;

    pessoas_txt = fopen("pessoas.txt", "rb");

    idade[0] = '\0';
    sexo[0] = '\0';
    lixo[0] = '\0';

    if(pessoas_txt)
    {
        // somando contadores de idade e de sexo
        while(fgets(pessoa_dados, PESSOA_MAX, pessoas_txt))
        {
            i = 0;
            j = 0;
            idade[0] = '\0';
            idade[1] = '\0';
            idade[2] = '\0';
            sexo[0] = '\0';
            lixo[0] = '\0';
            do
            {
                lixo[i] = pessoa_dados[i];
                i++;
            }while(pessoa_dados[i] != ':');
            i++;
            do
            {
                idade[j] = pessoa_dados[i];
                j++;
                i++;
            }while(pessoa_dados[i] != ',');
            printf("%s\n", idade);
            do
            {
                lixo[i] = pessoa_dados[i];
                i++;
            }while(pessoa_dados[i] != ':');
            i++;
            sexo[0] = pessoa_dados[i];
            idadeint = atoi(idade);
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
            system("cls");
            printf("Segue o Relatorio de Vacinacao:\n\n");
            //
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
            system("pause");
            system("cls");
        }
        else
        {
            printf("\nNenhuma pessoa foi cadastrada ate o momento.\n\n");
            system("pause");
            system("cls");
        }
    }
    else
    {
        printf("Nao foi possivel abrir o arquivo :(");
        printf("\nVoce cadastrou alguem???\n\n");
        system("pause");
        system("cls");
    }

    fclose(pessoas_txt);
}

//---------Menu------------------------------------------------------------------------------------------------
char menu() // funcao que retorna o menu para a funcao principal
{

    int i;
    int opcoes;

    printf("\n");
    for(i = 0; i < 50; i++) // printa as barras que decoram o menu
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
    scanf("%d", &opcoes);   // le a opcao que o usuario deseja

    return opcoes;

}

//---------Tela Inicial----------------------------------------------------------------------------------------
void telainicial()// a tela inicial mostrada antes do menu para informacoes sobre o programa
{
    int i;

    for(i = 0; i < 51; i++)
    {
        printf("%c", 254);                                //desta parte até o "system(pause)" são prints para decorar a tela inicial onde está
    }                                                     //escrito "Registro Demografico de Vacinacao" e a tela seguinte
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
    printf("- Seu sexo;                          ");            //  todos esses prints em for com 219 ou 254 são para estética
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
