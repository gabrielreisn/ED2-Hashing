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
    
    //char strings[10][MAXP];
    
    palavra_t* strings[10];
    
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
    //imprime_ordenado(tabelaHash);
    //-------------------------------------------

    char* token;
    printf("digite as palavras da busca:");
    gets(palavra);
    token = strtok(palavra," ");
    
    int i=0;
    while( token != NULL ) 
   {
      
      strings[i] = acessa(tabelaHash,token);
      
      token = strtok(NULL," ");
      i++;
   }
    
    int qtd = i;
    
    int k=0;
    /*
    for(i=0;i<qtd;i++){
        printf("%s - ",strings[i]->palavra,strings[i]->ocorrencias);
        
        for (k = 0; k < strings[i]->qtd; k++) {
            printf("%d ",strings[i]->ocorrencias[k]);

        }
        printf("\n");

    }*/
    //

    int tem =1;
    //printf("qtd: %d\n\n",qtd);
    for(i=0;i<strings[0]->qtd;i++){
        for(k=1;k<qtd;k++){
            if (contains(strings[k]->ocorrencias,strings[k]->qtd,strings[0]->ocorrencias[i])) {
                //printf("str 1 (%d) - str %d (%d)\n",strings[0]->ocorrencias[i],k+1,strings[k]->ocorrencias[k]);
                tem++;
            }
            
        }
        
        //printf("tem: %d\n",tem);
        
        if (tem==qtd) {
            buscaLinha(fp,strings[0]->ocorrencias[i]);
            //tem=1;
        }
        tem=1;
        //tem=0;
        //printf("tem depois do print: %d\n",tem);
    }
    
    

    //imprime_ordenado(tabelaHash); //imprime por ordem decrescente da ocorrencia das palavras, precisa imprimir por ordem alfabetica
    return 0;
}