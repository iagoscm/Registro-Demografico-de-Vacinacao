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

//funcoes excluirpessoa e consultapessoa estao encontrando muitos erros na hora de dividir o nome, tentar usar strtok para resolver
//verificar se consultaestado e consulta cidade nao estao possuindo os mesmos erros

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
void listaestado();
void listacidade();
void consultapessoa();
void excluipessoa();
void relatoriofinal();
int verificadata(PESSOA habitante);
int verificacidade(PESSOA habitante);
int verificaUF(PESSOA habitante);
char menu();
int calculaidade(int anoi, PESSOA habitante);

int main()
{
    int opcoes, i;
    PESSOA habitante;

    for(i = 0; i < 51; i++)
    {
        printf("%c", 254);                                //desta parte até o "system(pause)" são prints para decorar a tela inicial onde está
    }                                                     //escrito "Registro Demografico de Vacinacao"
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
    printf("- Seu sexo;                          ");            //todos esses prints em for com 219 ou 254 são para estética
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
            listaestado();
        }

        if(opcoes == 5)
        {
            listacidade();
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
            printf("Segue o relatorio geral de vacinacao: \n");
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
int calculaidade(int anoi, PESSOA habitante) // funcao que calcula a idade do habitante a partir do ano
{

    int i;
    int idade = 0;

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

//---------Verifica Cidade-------------------------------------------------------------------------------------
int verificacidade(PESSOA habitante) // funcao que verifica se a cidade esta registrada
{
    FILE *cidades_registradas_txt;
    int procura_cidade_registrada = 0, procuraUF_igual = 0;
    char cidades_registradas[CIDADE_MAX];

    cidades_registradas_txt = fopen("cidades registradas.txt", "a+b");

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
        }
        if((procura_cidade_registrada != 0) && (procuraUF_igual == 1))// se a cidade aparece mais de uma vez e a UF apenas uma vez, a cidade eh valida
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
    }
    else
        return 2;// caso o arquivo nao abra

    fclose(cidades_registradas_txt);

}

//---------Verifica UF-----------------------------------------------------------------------------------------
int verificaUF(PESSOA habitante)    // funcao que verifica se a UF esta registrada
{
    FILE *uf;   // arquivo pra abrir o txt das UFs
    char uftxt[UF_MAX];    // buffer para armazenar o conteudo do txt, numero 100
    int procurastring = 0;   //string criada pra verificar se a UF digitada esta dentro do .txt das UFs registradas

    uf = fopen("UFregistrada.txt", "a+");

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
        return 2;// caso o arquivo nao abra
    }

    fclose(uf);

}

//---------Cadastra Pessoa-------------------------------------------------------------------------------------
void cadastrapessoa(PESSOA habitante)
{
    /* funcao que ha de cadastrar a pessoa, primeiro verificando
    se os seus dados estão corretos, para ai sim registra-la no banco*/

    int nome = 0, erro = 0;// para contar se o nome eh feito apenas de letras

    printf("Digite o nome da pessoa: ");
    fflush(stdin);
    scanf("%[^\n]s", habitante.nome);// lendo o nome
    strupr(habitante.nome);
    for(int i = 0; i < strlen(habitante.nome); i++)
    {
        if((habitante.nome[i] >= 'A'  && habitante.nome[i] <= 'Z') || (isspace(habitante.nome[i])))
        {
            nome++;
        }
        else
        {
            erro++;// se tiver algo alem de letras, nao sera possivel entrar
        }
    }
    if((nome > 1) && (erro == 0))// verificando se o nome nao eh vazio ou se eh formado por letras
    {
        printf("Digite o sexo da pessoa (M ou F): ");
        fflush(stdin);
        scanf("%[^\n]s", habitante.sexo);// lendo o sexo
        strupr(habitante.sexo);// faco varias vezes pelo codigo para facilitar verificacao
        if(strcmp(habitante.sexo, "M") != 0 && strcmp(habitante.sexo, "F") != 0)// verificando se o sexo eh valido
        {
            printf("Sexo invalido\n\n");
            system("pause");
            system("cls");
        }
        else
        {
            printf("Digite a data de nascimento da pessoa (DD/MM/AAAA): ");
            fflush(stdin);
            scanf("%[^\n]s", habitante.data);// lendo a data
            int p = 0;
            char ano[5];
            for(int k = 6; k <= 9; k++)
            {
                ano[p] = habitante.data[k];
                p++;
            }
            int anoi = atoi(ano);// convertendo o ano obtido na string acima para int
            habitante.idade = calculaidade(anoi, habitante);// todo esse processo desde o for eh para conseguir infos para calcular a idade
            if(verificadata(habitante) == 2)
            {
                printf("Essa pessoa eh uma viajante do tempo :O\n\n");
                system("pause");
                system("cls");
            }
            else if(verificadata(habitante) == 1)
            {
                printf("Essa data eh invalida\n\n");
                system("pause");
                system("cls");
            }
            else if(verificadata(habitante) == 0)
            {
                printf("Digite a UF de onde a pessoa foi vacinada: ");
                fflush(stdin);
                scanf("%[^\n]s", habitante.UF);
                strupr(habitante.UF);
                if(verificaUF(habitante) == 1)
                {
                    printf("Essa UF nao esta registrada ou eh invalida\nVerifique a escrita e tente novamente.\n\n");
                    system("pause");
                    system("cls");
                }
                else if(verificaUF(habitante) == 2)
                {
                    printf("Nao foi possivel abrir o arquivo :(\n\n");
                    system("pause");
                    system("cls");
                }
                else if(verificaUF(habitante) == 0)
                {
                    printf("Digite agora uma cidade registrada nessa UF: ");
                    fflush(stdin);
                    scanf("%[^\n]s", habitante.cidade);
                    strupr(habitante.cidade);
                    if(verificacidade(habitante) == 1)
                    {
                        printf("Esta cidade esta registrada, porem nao nessa UF.\n\n");
                        system("pause");
                        system("cls");
                    }
                    else if(verificacidade(habitante) == 2)
                    {
                        printf("Nao foi possivel abrir o arquivo :(\n\n");
                        system("pause");
                        system("cls");
                    }
                    else if(verificacidade(habitante) == 3)
                    {
                        printf("Esta cidade nao esta registrada.\n\n");
                        system("pause");
                        system("cls");
                    }
                    else if(verificacidade(habitante) == 0)
                    {
                        registrapessoa(habitante);// chama o procedimento que salva no arquivo apos verificacoes
                    }
                }
            }
        }
    }
    else if(erro > 0)
    {
        printf("\nO nome deve ser formado apenas por letras\n\n");
        system("pause");
        system("cls");
    }
    else if(nome == 1)
    {
        printf("\nDigite pelo menos mais de uma letra para o nome\n\n");
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


    if(estados_registrados_txt)     // verificando se o arquivo existe
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
        printf("\nNao foi possivel abrir o arquivo :(\n\n");
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
                        char nome_cidade[500], nome_UF[4];  // buffers para verificar a cidade e a UF
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
void listaestado()// procedimento que lista as pessoas de acordo com suas UFs
{
    FILE *pessoas_txt, *UFs_registradas_txt;
    char pesquisa_estado[50];// estado desejado
    int contadorUF = 0;
    char lixo[PESSOA_MAX];// string grande o suficiente para guardar tudo aquilo que nao eh estado
    int i = 0;// sera necessario para guardar somente o estado
    char estado_linha[5];// buffer para guardar o estado da pessoa

    pessoas_txt = fopen("pessoas.txt", "a+b");
    UFs_registradas_txt = fopen("UFregistrada.txt", "a+b"); // abrindo os arquivos das pessoas e das UFs

    if(pessoas_txt)
    {
        printf("Digite a UF do estado que deseja listar: ");
        fflush(stdin);
        scanf("%[^\n]s", pesquisa_estado);
        strupr(pesquisa_estado);
        for(int k = 0; k < 2; k++)// repeticao para verificar se a UF esta digitada corretamente
        {
            if(pesquisa_estado[k] > 64 && pesquisa_estado[k] < 91)
            {
                contadorUF++;// conta quantas letras tem na string
            }
        }
        if(contadorUF == 2)// verifica se a estrutura da uf digitada eh valida
        {
            char UFs_registradas[100];
            int procuraUF_registrada = 0;
            do
            {
                fscanf(UFs_registradas_txt,"%s ", UFs_registradas);// transferindo o texto do txt para uma string
                if(strstr(UFs_registradas, pesquisa_estado))
                {
                    procuraUF_registrada++;// verifica se a UF digitada esta cadastrada
                }
            }
            while(!feof(UFs_registradas_txt));
            if(procuraUF_registrada != 0) // verifica se a UF digitada foi encontrada no txt de estados registrados
            {
                printf("Seguem as pessoas registradas neste estado:\n\n");
                char pessoas_registradas[PESSOA_MAX];// buffer pra armazenar as linhas de cada pessoa
                int pessoas = 0;// caso nao tenha nenhuma pessoa, continuara zero
                while(fgets(pessoas_registradas,NOME_MAX,pessoas_txt))
                {
                    i = 0;
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
                    i++;
                    if(strcmp(estado_linha, pesquisa_estado) == 0) // buffer para listar as pessoas pelo estado
                    {
                        printf(pessoas_registradas);
                        printf("\n");
                        pessoas++;
                    }
                }
                if(pessoas == 0)
                {
                    printf("\nAinda nao foram cadastradas pessoas neste estado.\n\n");
                    system("pause");
                    system("cls");
                }
                if(pessoas != 0)
                {
                    system("pause");
                    system("cls");
                }
            }
            else
            {
                printf("\nEssa UF nao foi registrada.\n\n");
                system("pause");
                system("cls");
            }
        }
        else
        {
            printf("Essa UF eh invalida, verifique a escrita e tente novamente.\n\n");
            system("pause");
            system("cls");
        }
    }
    else
    {
        printf("Nao foi possivel abrir o arquivo :(\n\n");
        system("pause");
        system("cls");
    }

    fclose(pessoas_txt);
    fclose(UFs_registradas_txt);
}

//---------Lista Pessoas por Cidade----------------------------------------------------------------------------
void listacidade()
{
    FILE *pessoas_txt, *cidades_registradas_txt;
    char pesquisa_cidade[LOCAL_MAX];
    int contadorcidade = 0;
    int pessoas = 0;// verificar quantas pessoas tem na cidade

    pessoas_txt = fopen("pessoas.txt", "a+b");
    cidades_registradas_txt = fopen("cidades registradas.txt", "a+b");

    if(pessoas_txt)
    {
        printf("Digite a cidade que deseja listar: ");
        fflush(stdin);
        scanf("%[^\n]s", pesquisa_cidade);
        strupr(pesquisa_cidade);
        for(int k = 0; k <= strlen(pesquisa_cidade); k++)// repeticao para verificar se a UF esta digitada corretamente
        {
            if(pesquisa_cidade[k] > 64 && pesquisa_cidade[k] < 91)
            {
                contadorcidade++;// conta quantas letras tem na string
            }
        }
        if((contadorcidade == strlen(pesquisa_cidade)) && (contadorcidade > 2))// verifica se a cidade possui apenas letras
        {
            char cidades_registradas[100];
            int procuracidade_registrada = 0;
            while(fgets(cidades_registradas, LOCAL_MAX, cidades_registradas_txt))
            {
                if(strstr(cidades_registradas, pesquisa_cidade))
                {
                    procuracidade_registrada++;
                }
            }
            if(procuracidade_registrada == 1) // verifica se a UF digitada foi encontrada no txt de estados registrados
            {
                char pessoas_registradas[100];
                printf("\nSeguem as pessoas desta cidade: \n\n");
                while(fgets(pessoas_registradas, PESSOA_MAX, pessoas_txt))// transferindo o txt pra uma string)
                {
                    if(strstr(pessoas_registradas, pesquisa_cidade))
                    {
                        printf("%s\n", pessoas_registradas);
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
                    printf("\n\nAinda nao foram cadastradas pessoas nesta cidade\n\n");
                    system("pause");
                    system("cls");
                }
            }
            else if(procuracidade_registrada > 1)
            {
                char UF_desejada[4];
                printf("\nDigite apenas a UF de qual das seguintes cidades deseja ver: \n");
                fseek(cidades_registradas_txt, 0, SEEK_SET);
                do
                {
                    fscanf(cidades_registradas_txt,"%s\n", cidades_registradas);// transferindo o texto do txt para uma string
                    if(strstr(cidades_registradas, pesquisa_cidade))
                    {
                        printf("%s\n", cidades_registradas);
                    }
                }
                while(!feof(cidades_registradas_txt));
                fflush(stdin);
                scanf("%[^\n]s", UF_desejada);
                strupr(UF_desejada);
                int contadorUF = 0;
                for(int j = 0; j < 4; j++)
                {
                    if(UF_desejada[j] > 64 && UF_desejada[j] < 91)
                    {
                        contadorUF++;
                    }
                }
                if(contadorUF == 2)
                {
                    char pessoas_registradas[100];
                    int contadorpessoas = 0;
                    printf("\nSeguem as pessoas registradas nessa localizacao:\n\n");
                    while(fgets(pessoas_registradas, 1500, pessoas_txt))
                    {

                        if((strstr(pessoas_registradas, UF_desejada)) && (strstr(pessoas_registradas,pesquisa_cidade)))
                        {
                            printf("%s\n", pessoas_registradas);
                            contadorpessoas++;
                        }
                    }
                    if(contadorpessoas == 0)
                    {
                        printf("Nao existem pessoas cadastradas nessa localizacao");
                        printf(" ou a UF eh invalida.\n\n");
                        system("pause");
                        system("cls");
                    }
                    else
                    {
                        printf("\n\n");
                        system("pause");
                        system("cls");
                    }
                }
                else
                {
                    printf("\nEssa UF eh invalida, verifique a escrita e tente novamente\n\n");
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
        else
        {
            printf("Essa cidade eh invalida, verifique a escrita e tente novamente.\n\n");
            system("pause");
            system("cls");
        }
    }
    else
    {
        printf("Nao foi possivel abrir o arquivo :(\n\n");
        system("pause");
        system("cls");
    }

    fclose(cidades_registradas_txt);
    fclose(pessoas_txt);

}

//---------Consulta Pessoa-------------------------------------------------------------------------------------
void consultapessoa()
{
    FILE *pessoas_txt;
    char pessoa_desejada[NOME_MAX], lista_pessoas[PESSOA_MAX], infopessoa[PESSOA_MAX], nome_pessoa[NOME_MAX];
    int contador = 0, i = 1, numero, k = 0, j = 0;

    pessoas_txt = fopen("pessoas.txt", "a+b");

    if(pessoas_txt)
    {
        printf("Digite o nome ou sobrenome da pessoa que deseja consultar: ");
        fflush(stdin);
        scanf("%[^\n]s", pessoa_desejada);
        strupr(pessoa_desejada);
        while(fgets(lista_pessoas,NOME_MAX,pessoas_txt))
        {
            j = 0;
            nome_pessoa[0] = '\0';
            do
            {
                nome_pessoa[j] = lista_pessoas[j];
                j++;
            }
            while(lista_pessoas[j]!=',');
            if(strstr(nome_pessoa, pessoa_desejada))
            {
                contador++; // contador para ver quantas vezes o nome aparece
                strcpy(infopessoa, lista_pessoas); // copio para outra string para depois apresentar o nome se so entrar uma vez nessa condicao
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
                if(strstr(lista_pessoas, pessoa_desejada))
                {
                    k = 0;
                    printf("%d-", i);// listando as pessoas de maneira ordenada para futura escolha
                    do
                    {
                        printf("%c", lista_pessoas[k]);
                        k++;
                    }
                    while(lista_pessoas[k]!=',');
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
            while(fgets(lista_pessoas,NOME_MAX,pessoas_txt))
            {
                if(strstr(lista_pessoas, pessoa_desejada))
                {
                    if(i == numero)
                    {
                        printf("Seguem os dados da pessoa desejada: \n\n");
                        printf("%s\n\n", lista_pessoas);
                        system("pause");
                        system("cls");
                    }
                    i++;
                }
            }
        }
        else if(contador == 1)// caso entre apenas uma vez, sera essa pessoa
        {
            printf("Seguem as informacoes da pessoa desejada: \n\n");
            printf("%s\n\n", infopessoa);
            system("pause");
            system("cls");
        }
    }
    else
    {
        printf("Nao foi possivel abrir o arquivo :(\n\n");
        system("pause");
        system("cls");
    }

    fclose(pessoas_txt);
}

//---------Exclui Pessoa---------------------------------------------------------------------------------------
void excluipessoa()
{
    FILE *original, *alterado;
    char pessoa_desejada[NOME_MAX];// nome da pessoa que deseja excluir
    char lista_pessoas[PESSOA_MAX];// buffer para armazenar os dados das pessoas para verificacao
    int j = 0, i = 1, contador = 0, k = 0, numero;// contadores para verificacoes futuras
    char nome_pessoa[NOME_MAX];// buffer para armazenar o nome de cada pessoa
    char infopessoa[PESSOA_MAX];// buffer para armazenar as infos da pessoa caso so exista uma com o nome digitado

    original = fopen("pessoas.txt", "r+b");// abrindo o arquivo existente com as pessoas
    alterado = fopen("alterado.txt", "w+b");// criando um arquivo novo de saída

    nome_pessoa[0] = '\0';

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
                j = 0;
                nome_pessoa[0] = '\0';
                do
                {
                    nome_pessoa[j] = lista_pessoas[j];
                    j++;
                }
                while(lista_pessoas[j]!=',');
                if(strstr(nome_pessoa, pessoa_desejada))
                {
                    contador++; // contador para ver quantas vezes o nome aparece
                    strcpy(infopessoa, lista_pessoas); // copio para outra string para depois apresentar o nome se so entrar uma vez nessa condicao
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
                    j = 0;
                    nome_pessoa[0] = '\0';
                    while(lista_pessoas[j]!=',')
                    {
                        nome_pessoa[j] = lista_pessoas[j];
                        j++;
                    }
                    if(strstr(nome_pessoa, pessoa_desejada))
                    {
                        k = 0;
                        printf("%d-", i);// listando as pessoas de maneira ordenada para futura escolha
                        do
                        {
                            printf("%c", lista_pessoas[k]);
                            k++;
                        }
                        while(lista_pessoas[k]!=',');
                        printf("\n");
                        i++;
                    }
                }
                do
                {
                    printf("\nDigite o numero da pessoa que deseja obter os dados: ");
                    fflush(stdin);
                    scanf("%d", &numero);
                }while(numero < 1 || numero > i-1);
                i = 1;
                fseek(original, 0, SEEK_SET);
                while(fgets(lista_pessoas,NOME_MAX,original))
                {
                    printf("%s", lista_pessoas);
                    k = 0;
                    nome_pessoa[0] = '\0';
                    do
                    {
                        nome_pessoa[k] = lista_pessoas[k];
                        k++;
                    }while(lista_pessoas[k]!=',');
                    printf("%s\n\n", nome_pessoa);
                    if(strstr(nome_pessoa, pessoa_desejada))
                    {
                        if(i != numero)
                        {
                            fseek(alterado,0,SEEK_END);
                            fprintf(alterado,"%s", lista_pessoas);
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
                        fprintf(alterado,"%s",lista_pessoas);
                    }
                }
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
//---------Menu------------------------------------------------------------------------------------------------
char menu() // funcao que retorna o menu para a funcao principal
{

    int i;
    int opcoes;

    printf("\n");
    for(i = 0; i < 50; i++)
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
    scanf("%d", &opcoes);

    return opcoes;

}
