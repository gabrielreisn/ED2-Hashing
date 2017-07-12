/* Informar nomes dos arquivos teste.txt e alfabeto.txt na linha de
comando */
/* Exemplo: a.out teste.txt alfabeto.txt
*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"
//#include "hashLinear.c"

int main(int argc, char ** argv) {

    FILE *fp;
    hash tabelaHash;
    char palavra[MAXP];

    if (argc < 2) {
        printf("Arquivo de entrada não fornecido");
        return 0;
    }
    fp = fopen(argv[2], "rt");
    if (fp == NULL) {
        printf("Erro na abertura do arquivo");
        return 0;
    }

    inicializaHash(fp,palavra,tabelaHash);
    
    //--------------------------------------------
    int qtd;
    printf("buscar quantas palavras?:");
    scanf("%d",&qtd);
    
    int i;
    for (i = 0; i < qtd; i++) {
        printf("digite a palavra:");
        scanf("%s",&palavra);
        busca(fp,tabelaHash,palavra);
    }

    
    //imprime_ordenado(tabelaHash);  //imprime por ordem decrescente da ocorrencia das palavras, precisa imprimir por ordem alfabetica
    return 0;
}