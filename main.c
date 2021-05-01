#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NOME_MAX 1000
#define CIDADE_MAX 50
#define PESSOA_MAX 1100
#define DATA_MAX 11
#define UF_MAX 500      // tamanho para ler a linha do txt de UFs
#define LOCAL_MAX 60    // tamanho maximo de uma estrutura CIDADE-UF

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
void confirmaexclusao();
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

    // chamando a tela inicial
    telainicial();

    do
    {
        // laco para a repeticao do menu
        opcoes = menu();
        fflush(stdin);
        if(opcoes == 1)
        {
            registraestado();
        }
        else if(opcoes == 2)
        {
            registracidade();
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

//---------Calcula Idade---------------------------------------------------------------------------------------
int calculaidade(PESSOA habitante) // funcao que calcula a idade do habitante a partir do ano
{

    int i = 0;
    int idade = 0;
    int l = 0;
    char anoc[5], mesc[3];
    int anoin, mesin;
    char *token;

    token = strtok(habitante.data, "/");// dividindo a data em tokens para atribuicoes

    // armazenando o mes e o ano
    while(token != NULL)
    {
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

    // convertendo para int
    anoin = atoi(anoc);
    mesin = atoi(mesc);
    i = anoin;

    // calculando a idade usando 05/2021 como referencia
    for(l = anoin; l <= 2021; l++)
    {
        if((anoin%400 == 0 || anoin%100 != 0) && (anoin%4 == 0) && (habitante.data[0] == '2') &&
           (habitante.data[1] == '9') && (habitante.data[3] == '0') && (habitante.data[4] == '2'))
        {
            if(i < 2021 && i != anoin)// calcula a idade se o ano for bissexto
            {
                idade++;
                i += 4;
            }
            else
                i++;
        }
        else
        {
            if(i < 2021 && i != anoin)
            {
                idade++;
                i++;
            }
            else
            {
                i++;
            }
            if(mesin <= 5 && i == 2021)
            {
                idade++;
            }
        }
    }

    return idade;
}

//---------Verifica Nome---------------------------------------------------------------------------------------
int verificanome(PESSOA habitante) // funcao que verifica se o nome digitado eh valido
{
    int nome = 0, erro = 0, espinicio = 0, esp = 0;// para verificacoes de validacao do nome

    for(int i = 0; i < strlen(habitante.nome); i++)
    {
        if((habitante.nome[i] >= 'A'  && habitante.nome[i] <= 'Z'))// verifica se na posicao eh letra
        {
            nome++;
            esp = 0; // zera o espaco para que nao deixe tambem terminar com espacos
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
            esp++;      // nao permite espaco adicional ao fim do nome se > 0
            erro--;
        }
    }

    if((nome > 1) && (erro == 0) && (espinicio == 0) && (esp == 0))// verificando se o nome nao eh vazio ou se eh formado por letras
    {
        return 0;
    }
    else if(erro > 0 && espinicio == 0)// caso tenha algum caracter diferente de letras
    {
        return 1;
    }
    else if(nome == 1)// caso so tenha uma letra
    {
        return 2;
    }
    else if(espinicio > 0)// caso comece com espacos
    {
        return 3;
    }
    else
        return 1;// caso de algum erro diferente
}

//---------Verifica Data---------------------------------------------------------------------------------------
int verificadata(PESSOA habitante) // funcao para verificar se a data da pessoa cadastrada eh verdadeira
{

    int i, p, anoi, k, verificador = 0;
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

    if(data[2] == '/' && data[5] == '/')
    {
        verificador++;
    }
    // a partir daqui são verificacoes para saber se a data eh valida, assim como sua formatacao
    if(strlen(data) < 10)
    {
        return 1;// caso faltar algum caracter ou numero
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
                verificador++;
            }
        }

        if((data[3] == '0' && data[4] == '4') || (data[3] == '0' && data[4] == '6') ||
                (data[3] == '0' && data[4] == '9') || (data[3] == '1' && data[4] == '1'))
        {
            if((data[0] == '0' && data[1] > '1' && data[1] <= '9') || (data[0] == '1' &&
                    data[1] >= '0' && data[1] <= '9') || (data[0] == '2' && data[1] >= '0' &&
                            data[1] <= '9') || (data[0] == '3' && data[1] == '0'))
            {
                verificador++;
            }
        }

        if(data[3] == '0' && data[4] == '2')
        {
            if((data[0] == '0' && data[1] > '1' && data[1] <= '9') || (data[0] == '1' &&
                    data[1] >= '0' && data[1] <= '9') || (data[0] == '2' && data[1] >= '0' &&
                            data[1] <= '8'))
            {
                verificador++;
            }
            else if((data[0] == '0' && data[1] > '1' && data[1] <= '9') || (data[0] == '1' &&
                    data[1] >= '0' && data[1] <= '9') || (data[0] == '2' && data[1] >= '0' &&
                            data[1] <= '9'))
            {
                verificador++;
            }
        }

    }

    if(anoi > 2021 || anoi < 1890)
    {
        return 2;// caso o ano seja > 2021 ou muito antigo
    }

    if(verificador == 2)
    {
        return 0;
    }
    else
        return 1;// retorna erro caso tenha algum erro na data ou ela nao exista

}

//---------Verifica Cidade e UF--------------------------------------------------------------------------------
int verificacidade_UF(PESSOA habitante) // funcao que verifica se a cidade esta registrada
{
    /*  dessa funcao pra verificacidade, o unico fato que muda eh a questao desta ser utilizada
        para verificar se a cidade esta cadastrada na UF correta, enquanto a verificacidade
        averigua se a grafia da cidade eh correta e esta cadastrada em alguma UF */

    FILE *cidades_registradas_txt;
    int procura_cidade_registrada = 0, procuraUF_igual = 0, certo = 0, i = 0;
    char cidades_registradas[CIDADE_MAX];
    char cidade_formatada[CIDADE_MAX];
    char cidadetemp[CIDADE_MAX];
    char *token;



    cidades_registradas_txt = fopen("cidades registradas.txt", "rb");// abro so para ler
    strcpy(cidadetemp, habitante.cidade);
    strcat(habitante.cidade, "-");
    strcat(habitante.cidade, habitante.UF);
    strcpy(cidade_formatada, habitante.cidade);
    strcpy(habitante.cidade, cidadetemp);
    strcat(cidade_formatada, "\n");

    if(strlen(habitante.cidade)==0)
    {
        fclose(cidades_registradas_txt);
        return 4;
    }

    if(cidades_registradas_txt)
    {
        while(fgets(cidades_registradas, 1500, cidades_registradas_txt))
        {
            i = 0;
            strcpy(cidadetemp, cidades_registradas);
            token = strtok(cidades_registradas, "-");
            // dividindo a estrutura CIDADE-UF
            while(token != NULL)
            {
                i++;
                if(i == 1)
                {
                    strcat(token, "\n");
                    if(strstr(token, habitante.cidade)) // verifico se a cidade esta registrada pelo buffer
                    {
                        procura_cidade_registrada++;    // contador para verificar quantas vezes a cidade aparece
                    }
                }
                if(i == 2)
                {
                    if(strstr(token, habitante.UF))// também verifico se a uf eh igual da cidade, se nao for, aviso que a cidade eh de outra uf
                    {
                        procuraUF_igual++;         // contador para verificar quantas vezes a UF aparece
                    }
                }
                token = strtok(NULL, "-");
            }
            if(strcmp(cidade_formatada, cidadetemp) == 0)// se a cidade estiver registrada na UF, soma o int certo
            {
                certo++;
            }
        }
        if(certo == 1)// se a cidade aparece mais de uma vez e a UF apenas uma vez, a cidade eh valida
        {
            fclose(cidades_registradas_txt);
            return 0;// caso esteja correto
        }
        else if((procura_cidade_registrada > 0) && (procuraUF_igual == 0))// se a cidade aparece mais de uma vez mas a UF nao, a cidade eh invalida
        {
            fclose(cidades_registradas_txt);
            return 1;// caso a cidade nao esteja cadastrada na UF
        }
        else if((procura_cidade_registrada == 0) && (procuraUF_igual == 0))// se a cidade nao aparece nenhuma vez nem a UF, a cidade eh invalida
        {
            fclose(cidades_registradas_txt);
            return 3;// caso a cidade nao esteja cadastrada
        }
        else
        {
            fclose(cidades_registradas_txt);
            return 3;// algum outro erro
        }
    }
    else
    {
        fclose(cidades_registradas_txt);
        return 2;// caso o arquivo nao abra, provavelmente nenhuma cidade foi cadastrada
    }

    fclose(cidades_registradas_txt);

}

//---------Verifica UF-----------------------------------------------------------------------------------------
int verificaUF(PESSOA habitante)    // funcao que verifica se a UF esta registrada
{
    FILE *uf;   // arquivo pra abrir o txt das UFs
    char uftxt[UF_MAX];    // string para armazenar o conteudo do txt, numero 100
    int procurastring = 0;   //string criada pra verificar se a UF digitada esta dentro do .txt das UFs registradas

    uf = fopen("UFregistrada.txt", "rb");/* abro so pra ler para caso
                                            nao tenha sido nenhuma registrada*/
    if(uf)
    {
        if(strlen(habitante.UF) == 2)
        {
            do
            {
                fscanf(uf,"%s",uftxt);// transferindo o conteudo do txt para uma string
                if(strstr(uftxt, habitante.UF))
                {
                    procurastring++;// se a UF aparece, o contador eh somado
                }
            }
            while(!feof(uf));
            if(procurastring != 0)
            {
                fclose(uf);
                return 0;// caso seja valida
            }
            else
            {
                fclose(uf);
                return 1;// caso nao apareça no txt
            }
        }
        else
        {
            fclose(uf);
            return 1;// caso a escrita seja invalida
        }
    }
    else
    {
        fclose(uf);
        return 2;// caso o arquivo nao abra, provavelmente nenhuma UF foi cadastrada
    }

    fclose(uf);

}

//---------Verifica Cidade-------------------------------------------------------------------------------------
int verificacidade(PESSOA habitante)
{
    FILE *cidades_registradas_txt;
    int procura_cidade_registrada = 0, certo = 0, letras = 0, i = 0;
    char cidades_registradas[CIDADE_MAX];
    char cidade_formatada[CIDADE_MAX];
    char cidadetemp[CIDADE_MAX];
    char *token;

    cidades_registradas_txt = fopen("cidades registradas.txt", "rb");// abrindo o arquivo das cidades registradas

    int tamanho = strlen(habitante.cidade);

    if(tamanho == 0)
    {
        fclose(cidades_registradas_txt);
        return 4;// caso nada tenha sido digitado
    }

    for(int i = 0; i < tamanho; i++)
    {
        if((habitante.cidade[i] >= 'A' && habitante.cidade[i] <= 'Z') || isspace(habitante.cidade[i]))
        {
            letras++;// verificando se eh formado por letras e/ou espacos
        }
    }

    if(letras != tamanho)
    {
        fclose(cidades_registradas_txt);
        return 4;// caso tenha algo diferente de letras
    }

    if(cidades_registradas_txt)
    {
        while(fgets(cidades_registradas, 1500, cidades_registradas_txt))
        {
            i = 0;
            strcpy(cidadetemp, cidades_registradas);// armazenando a info das cidades para verificacao
            // dividindo a estrutura CIDADE-UF
            token = strtok(cidades_registradas, "-");
            while(token != NULL)
            {
                i++;
                if(i == 1)
                {
                    strcat(token, "\n");// boto um \n para seguir a estrutura de habitante.cidade
                    if(strstr(token, habitante.cidade)) // buffer para verificar se a cidade esta registrada
                    {
                        procura_cidade_registrada++;    // contador para verificar quantas vezes a cidade aparece
                    }
                }
                token = strtok(NULL, "-");
            }
            if(strcmp(cidade_formatada, cidadetemp) == 0)// se a cidade estiver registrada na UF, soma o int certo
            {
                certo++;
            }
        }
        if(certo == 1)// se a cidade aparece exatamente uma vez, volta
        {
            fclose(cidades_registradas_txt);
            return 0;
        }
        else if(procura_cidade_registrada > 0)// se a cidade aparece mais de uma vez mas a UF nao, a cidade eh invalida
        {
            fclose(cidades_registradas_txt);
            return 0;// caso a cidade nao esteja cadastrada na UF
        }
        else if((procura_cidade_registrada == 0))// se a cidade nao aparece nenhuma vez nem a UF, a cidade eh invalida
        {
            fclose(cidades_registradas_txt);
            return 3;// caso a cidade nao esteja cadastrada
        }
        else
        {
            fclose(cidades_registradas_txt);
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
    int verificador = 0;
    char opcao[2];

    system("cls");

    printf("Digite o nome da pessoa: ");
    fflush(stdin);
    scanf("%[^\n]s", habitante.nome);// lendo o nome
    strupr(habitante.nome);// faco varias vezes pelo codigo para facilitar verificacao
    verificador = verificanome(habitante);
    if(verificador == 0)// verificando se o nome nao eh vazio ou se eh formado por letras
    {
        printf("Digite o sexo da pessoa (M ou F): ");
        fflush(stdin);
        scanf("%[^\n]s", habitante.sexo);// lendo o sexo
        strupr(habitante.sexo);
        if(strcmp(habitante.sexo, "M") == 0 || strcmp(habitante.sexo, "F") == 0)// verificando se o sexo eh valido
        {
            printf("Digite a data de nascimento da pessoa (DD/MM/AAAA): ");
            fflush(stdin);
            scanf("%[^\n]s", habitante.data);// lendo a data
            verificador = verificadata(habitante);
            if(verificador == 0)
            {
                habitante.idade = calculaidade(habitante);// calculando a idade
                printf("Digite a UF de onde a pessoa foi vacinada: ");
                fflush(stdin);
                scanf("%[^\n]s", habitante.UF);
                strupr(habitante.UF);
                verificador = verificaUF(habitante);
                if(verificador == 0)
                {
                    printf("Digite agora a cidade: ");
                    fflush(stdin);
                    scanf("%[^\n]s", habitante.cidade);
                    strupr(habitante.cidade);
                    verificador = verificacidade_UF(habitante);
                    if(verificador == 0)
                    {
                        do
                        {
                            printf("\nVoce realmente deseja cadastrar os dados de %s?(S/N): ", habitante.nome);
                            fflush(stdin);
                            scanf("%[^\n]s", opcao);
                            strupr(opcao);
                        }while(strcmp(opcao, "N") != 0 && strcmp(opcao, "S") != 0);
                        if(strcmp(opcao, "S") == 0)
                        {
                        registrapessoa(habitante);// chama o procedimento que salva no arquivo apos verificacoes
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
                        printf("\nPor favor, digite algo para que possa ser feita a verificacao.\n\n");
                    }
                }
                else if(verificador == 1)// se a uf digitada for invalida (tamanho > 2 ou < 2) ou nao for registrada
                {
                    printf("\nEssa UF nao esta registrada ou eh invalida\nVerifique a escrita e tente novamente.\n\n");
                }
                else if(verificador == 2)
                {
                    printf("\nNao foi possivel abrir o arquivo :(\n");
                    printf("Voce ja cadastrou alguma UF?\n\n");
                }
            }
            else if(verificador == 2)
            {
                printf("\nEssa pessoa eh uma viajante do tempo :O\n\n");/*  se o ano eh depois de 2021 ou muito antigo
                                                                (mais antigo do que a pessoa mais velha que ja viveu) */
            }
            else if(verificador == 1)// se a data foi digitada incorretamente ou nao existe
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
void registraestado() // procedimento que registra os estados por suas siglas no arquivo
{
    system("cls");

    FILE *estados_registrados_txt;
    char UFs_registradas[100], UFnova[4];
    int procuraUF_registrada = 0;
    int contador = 0;
    char opcao[2];

    estados_registrados_txt = fopen("UFregistrada.txt", "a+b"); // abrindo o arquivo das UFs registradas

    if(estados_registrados_txt)     // verificando se o arquivo foi criado ou ja existe
    {
        printf("UFs ja registradas (ordem de cadastro): \n\n");
        fseek(estados_registrados_txt,0,SEEK_SET);
        do
        {
            // listando as UFs que ja foram registradas
            fscanf(estados_registrados_txt, "%s ", UFs_registradas);
            if(strlen(UFs_registradas) != 0)
            {
                printf("- ");
                printf("%s\n", UFs_registradas);
                contador++;
            }
        }while(!feof(estados_registrados_txt));
        if(contador == 0)
        {
            printf("Ainda nao foram cadastradas UFs.\n");
        }
        contador = 0;
        printf("\n");
        system("pause");
        printf("\nDigite a UF que deseja registrar: ");
        fflush(stdin);
        scanf("%[^\n]s", UFnova);   // armazenando a UF a ser cadastrada
        strupr(UFnova);             // transformando em maiusculo para facilitar a verificacao
        for(int j = 0; j < 3; j++)
        {
            if(UFnova[j] > 64 && UFnova[j] < 91)
            {
                contador++;// verificando a escrita da UF
            }
        }

        fseek(estados_registrados_txt,0, SEEK_SET);
        do
        {
            // verificando se ja esta registrada
            fscanf(estados_registrados_txt, "%s ", UFs_registradas);
            if(strcmp(UFs_registradas, UFnova) == 0)
            {
                procuraUF_registrada++;
            }
        }while(!feof(estados_registrados_txt));

        if(contador == 2)                      // verifica se a UF eh valida
        {
            if(procuraUF_registrada == 0)      // verifica se a UF ja esta registrada
            {
                do
                {
                    printf("Tem certeza que deseja registrar essa UF?(S/N): ");
                    fflush(stdin);
                    scanf("%[^\n]s", opcao);
                    strupr(opcao);
                }while(strcmp(opcao, "N") != 0 && strcmp(opcao, "S") != 0);
                if(strcmp(opcao, "S") == 0)
                {
                    fseek(estados_registrados_txt,0,SEEK_END);      // colocando o ponteiro no fim do .txt
                    fprintf(estados_registrados_txt,"%s ",UFnova); // escrevendo a UF inserida no arquivo
                    printf("\nUF armazenada com sucesso :D\n\n");
                }
                else if(strcmp(opcao, "N") == 0)
                {
                    printf("\nA UF nao foi registrada.\n\n");
                }
            }
            else
            {
                printf("\nEssa UF ja esta registrada :)\n\n");
            }
        }
        else
        {
            printf("\nEssa UF nao e valida, verifique a escrita e tente novamente...\n");
            printf("Lembre-se: as UFs sao formadas por duas letras.\n\n");
        }
    }
    else
    {
        printf("\nNao foi possivel abrir/criar o arquivo :(\n\n");
    }

    system("pause");
    system("cls");

    fclose(estados_registrados_txt);
}

//---------Registra Cidade-------------------------------------------------------------------------------------
void registracidade() // procedimento que registra as cidades no arquivo
{
    system("cls");

    FILE *cidades_registradas_txt, *UFs_registradas_txt;
    CIDADE cidadenova;
    int contadorcidade = 0, tamanho_cidade, contadorUF = 0, tamanho_UF, procura_cidade_registrada = 0;
    int procuraUF_registrada = 0, erro = 0;
    char UFs_registradas[100], cidades_registradas[500], nome_formatado[550];
    char opcao[2];

    cidades_registradas_txt = fopen("cidades registradas.txt", "a+b");  // abrindo o arquivo das cidades já registradas
    UFs_registradas_txt = fopen("UFregistrada.txt", "a+b");


    if(cidades_registradas_txt)
    {
        // listando as cidades ja registradas
        printf("Cidades ja registradas e suas respectivas UFs (ordem de cadastro): \n\n");
        while(fgets(cidades_registradas, 1500, cidades_registradas_txt))
        {
            printf("- ");
            printf(cidades_registradas);
            contadorcidade++;
        }
        if(contadorcidade == 0)
        {
            printf("Ainda nao foram cadastradas cidades.\n");
        }
        printf("\n");
        system("pause");
        printf("\nDigite o nome da cidade que deseja registrar: ");
        fflush(stdin);
        scanf("%[^\n]s", cidadenova.cidade);// armazenando a cidade a ser registrada
        printf("Digite a UF a qual essa cidade pertence: ");
        fflush(stdin);
        scanf("%[^\n]s", cidadenova.UF);    // armazenando a UF da cidade
    }
    else
    {
        printf("\nNao foi possivel abrir o arquivo das cidades\n\n");
    }

    strupr(cidadenova.cidade);
    strupr(cidadenova.UF);          // transformando as duas strings em maiusculo para melhor verificacao
    tamanho_cidade = strlen(cidadenova.cidade); // armazenando o tamanho da string para verificar se eh formada apenas por letras
    tamanho_UF = strlen(cidadenova.UF);         // armazenando o tamanho da string para verificar se esta escrita corretamente

    if(tamanho_cidade >= 1 && tamanho_cidade <= 50)
    {
        for(int i = 0; i < tamanho_cidade; i++)
        {
            if((cidadenova.cidade[i] > 64 && cidadenova.cidade[i] < 91) || isspace(cidadenova.cidade[i]))
            {
                contadorcidade++;// conta quantas letras ou espacos tem na string
            }
            else
            {
                erro++;
            }
        }
        for(int k = 0; k < 2; k++)
        {
            if(cidadenova.UF[k] > 64 && cidadenova.UF[k] < 91)
            {
                contadorUF++;// conta quantas letras tem na string
            }
        }
    }


    if((contadorcidade > 1) && (erro == 0) && (contadorcidade >= 3)
       && (tamanho_cidade >= 1 && tamanho_cidade <= 50))  // verifica se a cidade esta escrita corretamente ou nao eh mt grande (>50)
    {
        if(UFs_registradas_txt)
        {
            if(tamanho_UF == 2 && contadorUF == 2)  // verifica se a UF esta escrita corretamente
            {
                strcpy(nome_formatado, cidadenova.cidade);
                strcat(nome_formatado, "-");
                strcat(nome_formatado, cidadenova.UF);
                strcat(nome_formatado, "\n");
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
                        if(strstr(cidades_registradas, cidadenova.cidade)) // verificando se a cidade esta incluida na string
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
                        do
                        {
                            printf("Tem certeza que deseja registrar essa cidade?(S/N): ");
                            fflush(stdin);
                            scanf("%[^\n]s", opcao);
                            strupr(opcao);
                        }while(strcmp(opcao, "N") != 0 && strcmp(opcao, "S") != 0);
                        if(strcmp(opcao, "S") == 0)
                        {
                            fseek(cidades_registradas_txt,0,SEEK_END); // colocando o ponteiro no fim do .txt
                            fprintf(cidades_registradas_txt,"%s-%s\n",cidadenova.cidade,cidadenova.UF);
                            printf("\nCidade armazenada com sucesso :)\n\n");
                        }
                        else if(strcmp(opcao, "N") == 0)
                        {
                            printf("\nA cidade nao foi registrada.\n\n");
                        }
                    }
                    else
                    {
                        if(procuraUF_igual == 0)  // se a cidade tiver sido igual, porem com UF diferente, eh cadastrada
                        {
                            do
                            {
                                printf("Tem certeza que deseja registrar essa cidade?(S/N): ");
                                fflush(stdin);
                                scanf("%[^\n]s", opcao);
                                strupr(opcao);
                            }while(strcmp(opcao, "N") != 0 && strcmp(opcao, "S") != 0);
                            if(strcmp(opcao, "S") == 0)
                            {
                                fseek(cidades_registradas_txt,0,SEEK_END); // colocando o ponteiro no fim do .txt
                                fprintf(cidades_registradas_txt,"%s-%s\n",cidadenova.cidade,cidadenova.UF);
                                printf("\nCidade armazenada com sucesso :)\n\n");
                            }
                            else if(strcmp(opcao, "N") == 0)
                            {
                                printf("\nA cidade nao foi registrada.\n\n");
                            }
                        }
                        else
                        {
                            printf("\nA cidade ja esta registrada com essa UF.\n\n");
                        }
                    }
                }
                else
                {
                    printf("\nA UF nao esta registrada. Registre primeiramente o estado e tente novamente.\n\n");
                }
            }
            else
            {
                printf("\nA UF digitada eh invalida. Verifique a escrita e tente novamente.\n\n");
            }
        }
        else
        {
            printf("\nNao foi possivel abrir o arquivo :(\n\n");
        }
    }
    else if(erro != 0)
    {
        printf("\nA cidade deve conter apenas letras.\n");

    }
    else if(contadorcidade == 0)
    {
        printf("\nDigite pelo menos 1 letra para cadastrar uma cidade.\n\n");
    }
    else if(tamanho_cidade > 50)
    {
        printf("Tente nao escrever nada tao grande...\n");
    }

    system("pause");
    system("cls");

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
    }
    else
    {
        printf("Erro ao abrir arquivo :(\n\n");
    }

    fclose(txt_pessoas);
}

//---------Lista Pessoas por Estado----------------------------------------------------------------------------
void listaestado(PESSOA habitante)// procedimento que lista as pessoas de acordo com suas UFs
{
    system("cls");
    FILE *pessoas_txt, *UFs_registradas_txt;
    int i = 0, j = 0;       // sera necessario para guardar somente o estado
    char *token1, *token2;  // separar as categorias do struct da pessoa e separar cidade de estado
    char dados_pessoa[PESSOA_MAX];
    char pessoas_registradas[PESSOA_MAX];// string pra armazenar as linhas de cada pessoa
    int pessoas = 0;// caso nao tenha nenhuma pessoa, continuara zero
    int verificador;

    pessoas_txt = fopen("pessoas.txt", "rb");
    UFs_registradas_txt = fopen("UFregistrada.txt", "rb"); // abrindo os arquivos das pessoas e das UFs

    if(pessoas_txt)
    {
        if(UFs_registradas_txt)
        {
            printf("Digite a UF do estado que deseja listar: ");
            fflush(stdin);
            scanf("%[^\n]s", habitante.UF);
            strupr(habitante.UF);
            verificador = verificaUF(habitante);
            if(verificador == 0)// verifica se a estrutura da uf digitada eh valida e esta registrada
            {
                printf("Segue(m) a(s) pessoa(s) registradas neste estado:\n\n");
                printf("---------------------------------------------------------------------------\n");
                while(fgets(pessoas_registradas,PESSOA_MAX,pessoas_txt))
                {
                    // dividindo a struct para verificacao
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
                                        printf(dados_pessoa);
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
void listacidade(PESSOA habitante)// procedimento que lista as pessoas de acordo com suas cidades
{
    system("cls");
    FILE *pessoas_txt, *cidades_registradas_txt;
    int i, numero, k;
    char cidades_registradas[LOCAL_MAX];
    int procuracidade_registrada = 0;
    char pessoas_registradas[PESSOA_MAX];
    int contadorpessoas = 0;
    char *token, cidadetemp[CIDADE_MAX];
    char cidadeprocurada[CIDADE_MAX];
    int verificador = 0;
    char pessoatemp[PESSOA_MAX];
    char *token2;

    pessoas_txt = fopen("pessoas.txt", "rb");
    cidades_registradas_txt = fopen("cidades registradas.txt", "rb");// abrindo os arquivos de pessoas e cidades para leitura

    if(pessoas_txt)
    {
        if(cidades_registradas_txt)
        {
            printf("Digite a cidade que deseja listar: ");
            fflush(stdin);
            scanf("%[^\n]s", habitante.cidade);
            strupr(habitante.cidade);
            verificador = verificacidade(habitante);
            if(verificador == 0)// verifica se a cidade possui apenas letras e esta cadastrada
            {
                while(fgets(cidades_registradas, LOCAL_MAX, cidades_registradas_txt))
                {
                    // separando a struct CIDADE-UF
                    token = strtok(cidades_registradas, "-");
                    i = 0;
                    while(token != NULL)
                    {
                        i++;
                        if(strcmp(token, habitante.cidade) == 0 && i == 1)
                        {
                            procuracidade_registrada++;// caso a cidade apareca, somo para verificacao
                        }
                        token = strtok(NULL, "-");
                    }
                }
                if(procuracidade_registrada == 1) // verifica se a cidade digitada foi encontrada no txt de estados registrados
                {
                    printf("\nSegue(m) a(s) pessoa(s) desta cidade: \n\n");
                    printf("---------------------------------------------------------------------------\n");
                    while(fgets(pessoas_registradas, PESSOA_MAX, pessoas_txt))// transferindo o txt pra uma string)
                    {
                        strcpy(pessoatemp, pessoas_registradas);
                        // separando a struct PESSOA para verificacao
                        token = strtok(pessoas_registradas, ",");
                        i = 0;
                        k = 0;
                        while(token != NULL)
                        {
                            i++;
                            if(i == 2)// posicao de CIDADE-UF na struct
                            {
                                token2 = strtok(token, "-");// obtenho apenas CIDADE da string da pessoa
                                if(k == 0)
                                {
                                    if(strcmp(token2, habitante.cidade) == 0)// verifico se a cidade eh igual
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
                else if(procuracidade_registrada > 1)// caso haja mais de uma cidade com UFs diferentes
                {
                    printf("\nAs seguintes cidades foram encontradas: \n\n");
                    k = 1;
                    fseek(cidades_registradas_txt, 0, SEEK_SET);
                    while(fgets(cidades_registradas, LOCAL_MAX, cidades_registradas_txt))
                    {
                        strcpy(cidadetemp, cidades_registradas);
                        // dividindo a struct CIDADE
                        token = strtok(cidades_registradas, "-");
                        i = 0;
                        while(token != NULL)
                        {
                            i++;
                            if(strcmp(token, habitante.cidade) == 0 && i == 1)
                            {
                                printf("%d.", k);
                                printf("%s", cidadetemp);// printo toda a struct da cidade para escolha do usuario
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
                        // dividindo a struct CIDADE para poder obter apenas a cidade procurada pelo usuario
                        token = strtok(cidades_registradas, "-");
                        i = 0;
                        while(token != NULL)
                        {
                            i++;
                            if(strcmp(token, habitante.cidade) == 0 && i == 1)
                            {
                                if(k == numero)// se chegar no numero escolhido pelo usuario, eu armazeno a cidade
                                {
                                    strcpy(cidadeprocurada, token);
                                }
                                k++;// somo caso seja outra cidade que tenha entrado
                            }
                            if(strcmp(cidadeprocurada, habitante.cidade) == 0 && i == 2)// armazenando a UF caso seja a cidade correta
                            {
                                strcat(cidadeprocurada,"-");
                                token[2] = '\0';// para nao ocorrer erros na verificacao
                                strcat(cidadeprocurada, token);// junto a UF com a cidade
                            }
                            token = strtok(NULL, "-");
                        }
                    }
                    fseek(pessoas_txt, 0, SEEK_SET);
                    while(fgets(pessoas_registradas, PESSOA_MAX, pessoas_txt))
                    {
                        // printo somente os que realmente sao da cidade+uf
                        if((strstr(pessoas_registradas,cidadeprocurada)))
                        {
                            printf("%s", pessoas_registradas);
                            printf("---------------------------------------------------------------------------\n");
                            contadorpessoas++;// conto para retornar depois se alguem foi listado
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
                else if(procuracidade_registrada == 0)
                {
                    printf("\nEssa cidade nao esta registrada.\n\n");
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
void consultapessoa()// procedimento que mostra informacoes de uma pessoa em particular
{
    system("cls");
    FILE *pessoas_txt;
    char pessoa_desejada[NOME_MAX], lista_pessoas[PESSOA_MAX], infopessoa[PESSOA_MAX], dados_pessoa[PESSOA_MAX];
    int contador = 0, k = 0;
    char *token;

    pessoas_txt = fopen("pessoas.txt", "rb");// abrindo arquivo de pessoas para leitura

    if(pessoas_txt)
    {
        printf("Digite o nome ou sobrenome da pessoa que deseja consultar: ");
        fflush(stdin);
        scanf("%[^\n]s", pessoa_desejada);
        strupr(pessoa_desejada);
        while(fgets(lista_pessoas,NOME_MAX,pessoas_txt))
        {
            strcpy(dados_pessoa, lista_pessoas);
            // dividindo a struct PESSOA
            token = strtok(lista_pessoas, ",");
            k = 0;
            while(token != NULL)
            {
                k++;// para diferenciara as posicoes
                if(strstr(token, pessoa_desejada) && k == 1)// o nome fica na posicao 1 na struct que vai para o arquivo
                {
                    contador++; // contador para ver quantas vezes o nome aparece
                    strcpy(infopessoa, dados_pessoa); // copio para outra string para depois apresentar o nome se so entrar uma vez nessa condicao
                }
                token = strtok(NULL, ",");
            }
        }
        if(contador == 0)// caso nao entre nenhuma vez na condicao
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
                    if(strstr(token, pessoa_desejada) && k == 1)// verifico se o nome da pessoa eh igual ao digitado
                    {
                        printf(dados_pessoa);// printo todas as pessoas pois podem existir pessoas diferentes com nomes iguais
                        printf("---------------------------------------------------------------------------\n");
                    }
                    token = strtok(NULL, ",");
                }

            }

            printf("\n\n");
        }
        else if(contador == 1)// caso entre apenas uma vez, sera essa pessoa
        {
            printf("\nSeguem as informacoes da pessoa desejada: \n\n");
            printf("---------------------------------------------------------------------------\n");
            printf("%s", infopessoa);// struct armazenada mais cedo
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
void excluipessoa()// procedimento que pergunta sobre a exclusao
{
    system("cls");
    FILE *original;
    char lista_pessoas[PESSOA_MAX]; // string para armazenar os dados das pessoas para verificacao
    char opcao[2];
    int contador = 0;        // para a listagem de pessoas

    original = fopen("pessoas.txt", "rb");// abrindo o arquivo existente com as pessoas

    if(original)
    {
        do
        {
            //listando (ou nao) as pessoas cadastradas
            printf("Deseja ver todas as pessoas cadastradas antes de excluir alguem?(S/N): ");
            fflush(stdin);
            scanf("%[^\n]s", opcao);
            strupr(opcao);
        }while(strcmp(opcao, "N") != 0 && strcmp(opcao, "S") != 0);
        if(strcmp(opcao, "N") == 0)
        {
            fclose(original);
            confirmaexclusao(original);// chamando o procedimento de exclusao sem mostrar a lista
        }
        else if(strcmp(opcao, "S") == 0)
        {
            // listando as pessoas ja cadastradas com todos os seus dados
            printf("Essas sao todas as pessoas cadastradas ate o momento: \n");
            printf("\n");
            fseek(original, 0, SEEK_SET);
            while(fgets(lista_pessoas,PESSOA_MAX,original))
            {
                    printf("- ");
                    printf(lista_pessoas);
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
void confirmaexclusao()// procedimento que exclui a pessoa desejada
{
    FILE *alterado, *original;
    char pessoa_desejada[NOME_MAX];// nome da pessoa que deseja excluir
    char lista_pessoas[PESSOA_MAX];// string para armazenar os dados das pessoas para verificacao
    int  i = 1, contador = 0, numero, k;// contadores para verificacoes futuras
    char *nome_pessoa;//  para armazenar o nome de cada pessoa
    char infopessoa[PESSOA_MAX], dados_pessoa[PESSOA_MAX];// strings para armazenar as infos das pessoas
    char opcao[2];

    alterado = fopen("alterado.txt", "w+b");// criando um arquivo novo de saída
    original = fopen("pessoas.txt", "rb");// abrindo o arquivo existente com as pessoas

    system("pause");
    printf("\n");
    printf("Digite o nome ou sobrenome da pessoa que deseja excluir: ");
    fflush(stdin);
    scanf("%[^\n]s", pessoa_desejada);// obtendo o nome desejado para exclusao
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
                // dividindo a struct PESSOA
                nome_pessoa = strtok(lista_pessoas, ",");
                while(nome_pessoa)
                {
                    k++;
                    if(k == 1)
                    {
                        if(strstr(nome_pessoa, pessoa_desejada))
                        {
                            contador++; // contador para ver quantas vezes o nome aparece
                            strcpy(infopessoa, dados_pessoa); // copio para outra string para exclusao sem verificacao caso o nome so apareca uma vez
                        }
                    }
                    nome_pessoa = strtok(NULL, ",");
                }
            }
            if(contador == 0)// caso nao entre nenhuma vez na condicao
            {
                printf("\nNao foi possivel encontrar esta pessoa\nVerifique a escrita e tente novamente.\n\n");
            }
            else if(contador > 1)// caso entre mais de uma vez(nomes repetidos)
            {
                printf("Foram encontradas mais de uma pessoa:\n\n");
                fseek(original, 0, SEEK_SET);
                while(fgets(lista_pessoas,PESSOA_MAX,original))
                {
                    k = 0;
                    strcpy(dados_pessoa, lista_pessoas);
                    // dividindo a struct PESSOA
                    nome_pessoa = strtok(lista_pessoas, ",");
                    while(nome_pessoa)
                    {
                        k++;
                        if(k == 1)
                        {
                            if(strstr(nome_pessoa, pessoa_desejada))
                            {
                                printf("%d-", i);// listando as pessoas de maneira ordenada para futura escolha
                                printf(dados_pessoa);
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
                i = 1;                              // para listagem ordenada
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
                            if(strstr(nome_pessoa, pessoa_desejada))// verifico se o nome eh igual
                            {
                                if(i != numero)
                                {
                                    fseek(alterado,0,SEEK_END);
                                    fputs(dados_pessoa,alterado);// escrevo caso o nome seja igual porem nao o escolhido
                                }
                                else
                                {
                                    do
                                    {
                                        // verifico se deseja-se realmente excluir a pessoa
                                        printf("Tem certeza que deseja excluir os dados de %s?(S/N): ", nome_pessoa);
                                        fflush(stdin);
                                        scanf("%[^\n]s", opcao);
                                        strupr(opcao);
                                    }while(strcmp(opcao, "N") != 0 && strcmp(opcao, "S") != 0);
                                    if(strcmp(opcao, "S") == 0)
                                    {
                                        printf("\nDados de %s excluidos com sucesso :)\n\n", nome_pessoa);// nao escrevo o nome no novo arquivo
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
                                fputs(dados_pessoa,alterado);// escrevo o resto no arquivo novo caso nao seja o excluido
                            }
                        }
                        nome_pessoa = strtok(NULL, ",");
                    }
                }
                fclose(alterado);
                fclose(original);
                remove("pessoas.txt");// removo o arquivo original
                rename("alterado.txt","pessoas.txt");// renomeio o novo arquivo para o nome do arquivo antigo
            }
            else if(contador == 1)
            {
                fseek(original, 0, SEEK_SET);
                while(fgets(lista_pessoas,PESSOA_MAX,original))
                {
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
    remove("alterado.txt");// caso saia das condicoes sem excluir o arquivo novo, excluo aqui para nao ocorrer algum tipo de problema
}

//---------Relatorio Final-------------------------------------------------------------------------------------
void relatoriofinal()// procedimento para mostrar o relatorio das pessoas
{
    system("cls");

    FILE *pessoas_txt;
    char pessoa_dados[PESSOA_MAX], idade[4], sexo[1];// armazenar os dados das pessoas
    int i = 0, k = 0;                                       // para dividir as condicoes do token
    int idadeint;                               // para transformar a idade em inteiro para contar pro relatorio
    double homem = 0, mulher = 0, habitante = 0, zeroquinze = 0, dseisvnove = 0, trtqnove = 0, cinqsess = 0, acima60 = 0; // para somas
    char *token, *token2;                                // para dividir as informacoes no txt

    pessoas_txt = fopen("pessoas.txt", "rb");



    if(pessoas_txt)
    {
        // somando contadores de idade e de sexo
        while(fgets(pessoa_dados, PESSOA_MAX, pessoas_txt))
        {
            //  processo de separacao de dados
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
            // soma para porcentagem
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
            //contas para a porcentagem final
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
char menu() // funcao que retorna o menu para a funcao principal
{

    int i;
    int opcoes = 0;

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
    fflush(stdin);
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
    printf("- Seu sexo;                          ");            //  todos esses prints em for com 219 ou 254 são para estetica
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
