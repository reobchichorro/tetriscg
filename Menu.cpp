
#include <iostream>
#include <string.h>
#include <stdio.h>


//estrutura de dados que repsenta o menu
struct Menu{
    int botao[9]; //opções do menu
    int foco; //opção que 
};

//funções de tratamento das opções do menu deverão estar aqui
void opcao_menu(int opcao)
{
    switch(opcao)
    {
        case 8 : //sair
            exit(0);
        break;
    }
}