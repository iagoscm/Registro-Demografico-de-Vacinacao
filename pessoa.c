#include "main.h"
#include "pessoa.h"

#include <ctype.h>
#include <string.h>

int verificanome(PESSOA habitante) // Funcao que verifica se o nome digitado eh valido
{
    int len = strlen(habitante.nome);
    
    // Verifica se o nome está vazio
    if (len == 0) {
        return ERRONOME;
    }
    
    // Verifica se inicia ou termina com espaço
    if (isspace(habitante.nome[0]) || isspace(habitante.nome[len - 1])) {
        return ESPACO;
    }
    
    int conta_letras = 0;
    
    for (int i = 0; i < len; i++) {
        char c = habitante.nome[i];
        
        
        if (isalpha(c)) {
            conta_letras++; // Se o caractere for uma letra, incrementa o contador
        }
        
        else if (isspace(c)) {
            if (i > 0 && isspace(habitante.nome[i - 1])) { // Se for espaço, garante que não seja espaço duplo 
                return ERRONOME; // Espaço duplo encontrado
            }
        }
        
        else {
            return ERRONOME; // Se for qualquer outro caractere, retorna erro
        }
    }
    
    if (conta_letras < 2) {
        return PEQUENO; // Se o nome tiver menos de duas letras, retorna erro
    }
    
    return 0;
}