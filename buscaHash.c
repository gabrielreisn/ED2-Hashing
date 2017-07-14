/* Informar nomes dos arquivos teste.txt e alfabeto.txt na linha de
comando */
/* Exemplo: a.out teste.txt alfabeto.txt
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

int main(int argc, char ** argv) {

    FILE *fp;
    hash tabelaHash;
    char palavra[MAXP];
    
    
    
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


    int tem =1;
    
    for(i=0;i<strings[0]->qtd;i++){
        for(k=1;k<qtd;k++){
            if (contains(strings[k]->ocorrencias,strings[k]->qtd,strings[0]->ocorrencias[i])) {
                tem++;
            }
            
        }
        
        
        
        if (tem==qtd) {
            buscaLinha(fp,strings[0]->ocorrencias[i]);
            
        }
        tem=1;
    }
    
    


    return 0;
}