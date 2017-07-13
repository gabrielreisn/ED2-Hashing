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
    
    char strings[10][MAXP];

    if (argc < 2) {
        printf("Arquivo de entrada não fornecido");
        return 0;
    }
    fp = fopen(argv[2], "rt");
    if (fp == NULL) {
        printf("Erro na abertura do arquivo");
        return 0;
    }

    inicializaHash(fp, palavra, tabelaHash);

    //-------------------------------------------

    char* token;
    printf("digite as palavras da busca:");
    gets(palavra);
    token = strtok(palavra," ");
    
    int i=0;
    while( token != NULL ) 
   {
      strcpy(strings[i],token); 
      token = strtok(NULL," ");
      i++;
   }
    
    int qtd = i;
    
    for(i=0;i<qtd;i++){
        //printf("%s\n",);
        busca(fp, tabelaHash,strings[i]);
    }
    //



    //imprime_ordenado(tabelaHash); //imprime por ordem decrescente da ocorrencia das palavras, precisa imprimir por ordem alfabetica
    return 0;
}