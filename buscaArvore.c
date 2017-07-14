#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

int main(int argc, char** argv) {

    NoArv* arv;

    arv = abb_cria();

    FILE *fp;

    if (argc < 2) {
        printf("Arquivo de entrada não fornecido");
        return 0;
    }
    fp = fopen(argv[1], "rt"); //palavras chave
    if (fp == NULL) {
        printf("Erro na abertura do arquivo");
        return 0;
    }

    FILE* file2;
    file2 = fopen(argv[2], "rt"); //textao

    char palavra[640];




    while (le_palavra(file2, palavra)) {
        arv = abb_insere(arv, palavra);
    }
    linha2 = 1;
    flag2 = 0;
    rewind(file2);

    while (le_palavra(file2, palavra)) {

        NoArv* catch = abb_busca(arv, palavra);

        if (catch->ocorrencias[catch->qtd - 1] != linha2) {
            catch->ocorrencias[catch->qtd] = linha2;
            catch->qtd++;
        }
    }
    //palavra_t* strings[10];
    NoArv* strings[10];
    
    
    char* token;
    printf("digite as palavras da busca:");
    gets(palavra);
    token = strtok(palavra, " ");

    int i = 0;
    while (token != NULL) {

        strings[i] = abb_busca(arv,token);//acessa(tabelaHash, token);

        token = strtok(NULL, " ");
        i++;
    }

    int qtd = i;

    int k = 0;


    int tem = 1;

    for (i = 0; i < strings[0]->qtd; i++) {
        for (k = 1; k < qtd; k++) {
            if (contains(strings[k]->ocorrencias, strings[k]->qtd, strings[0]->ocorrencias[i])) {
                tem++;
            }

        }



        if (tem == qtd) {
            buscaLinha(file2, strings[0]->ocorrencias[i]);

        }
        tem = 1;
    }



    //abb_imprime(arv);

    return (EXIT_SUCCESS);
}

