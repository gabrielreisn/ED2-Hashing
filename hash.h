/* 
 * File:   hash.h
 * Author: gferreira
 *
 * Created on June 22, 2017, 2:57 PM
 */

#ifndef HASH_H
#define	HASH_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
    
#define MAXP 640
#define MAXT 12700


int linha = 1;
int flag = 0;

typedef struct palavra palavra_t;

struct palavra {
    char palavra[MAXP];
    int qtd;
    int ocorrencias[MAXP];
    palavra_t *prox;
};

typedef palavra_t * hash[MAXT];

static int le_palavra(FILE *fp, char *s) {
    char c;
    int i = 0;
    
        if(flag==1){
            linha++;
            flag=0;
        }


    while ((c = fgetc(fp)) != EOF) {
        
        if (isalpha(c))
            break;
        if (c == '\n') {
            linha++;
        }
    }
    
    if (c == EOF) {   
        return 0;
    } else {
        s[i++] = c;
    }

    while (i < MAXT - 1 && (c = fgetc(fp) || c=='-') != EOF && (isalpha(c) || c=='-')) {
        s[i++] = c;
    }
    
    s[i] = '\0';
    
    if(c != '\n')
        return 1;
    
    
    if (c == '\n') {
        flag=1;
    }

    return 1;
}

static void inicializa(hash tab) {
    int i;
    for (i = 0; i < MAXT; i++)
        tab[i] = NULL;
}

static int f_hash(char *s) {
    int i;
    int total = 0;

    for (i = 0; s[i] != '\0'; i++)
        total += s[i];

    return total % MAXT;
}

static palavra_t *acessa(hash tab, char *s) {
    palavra_t *p;
    int h = f_hash(s);

    if (tab[h] == NULL) {
        p = (palavra_t *) malloc(sizeof (palavra_t));

        strcpy(p->palavra, s);
        p->qtd = 0;
        p->prox = NULL;
        tab[h] = p;
        return p;
    }

    for (p = tab[h]; p != NULL; p = p->prox) {
        if (strcmp(p->palavra, s) == 0)
            return p;
    }
    p = (palavra_t *) malloc(sizeof (palavra_t));
    strcpy(p->palavra, s);
    p->qtd = 0;
    p->prox = tab[h];
    tab[h] = p;


    return p;


}

static int cont_elems(hash tab) {
    int i;
    int total = 0;
    palavra_t *p;

    for (i = 0; i < MAXT; i++) {
        for (p = tab[i]; p != NULL; p = p->prox)
            total++;
    }

    return total;
}

static palavra_t ** cria_vet(int n, hash tab) {
    int i, j = 0;
    palavra_t *p;

    palavra_t **vet = (palavra_t **) malloc(sizeof (palavra_t *) * n);

    for (i = 0; i < MAXT; i++) {
        for (p = tab[i]; p != NULL; p = p->prox)
            vet[j++] = p;
    }

    return vet;
}

static int compara(const void *v1, const void *v2) {
    palavra_t ** p1 = (palavra_t **) v1;
    palavra_t ** p2 = (palavra_t **) v2;

    //if ((*p1)->qtd > (*p2)->qtd) return -1;
    if (strcmp((*p1)->palavra, (*p2)->palavra) < 0) return -1;
        //else if ((*p1)->qtd < (*p2)->qtd) return 1;
    else if (strcmp((*p1)->palavra, (*p2)->palavra) > 0) return 1;
    else if (strcmp((*p2)->palavra, (*p2)->palavra) == 0) return 0;

}

static void imprime_ordenado(hash tab) {
    int i, j;
    int qtd;
    palavra_t **vet;

    qtd = cont_elems(tab);
    vet = cria_vet(qtd, tab);

    qsort(vet, qtd, sizeof (palavra_t **), compara);

    for (i = 0; i < qtd; i++) {
        printf("%15s      ", vet[i]->palavra);
        for (j = 0; j < (vet[i]->qtd); j++) {
            printf("%d ", vet[i]->ocorrencias[j]);
        }

        printf("\n");
    }
}

static void inicializaHash(FILE*fp,char*palavra,hash tabela){
    inicializa(tabela);

    while (le_palavra(fp, palavra)) {
        palavra_t *p = acessa(tabela, palavra);
        if(p->ocorrencias[p->qtd-1]!=linha){
            p->ocorrencias[p->qtd] = linha;
            p->qtd++;
        }
    } 
}

static void busca(FILE*fp,hash tabela,char* palavra){
    
    rewind(fp);
    char buffer[20480];   //linha inteira

    palavra_t *p = acessa(tabela, palavra);  
    
    
    
    int j=0;
    for (int i = 0; i < p->qtd; i++) {
        for (j = 0; j < (p->ocorrencias[i]); j++) {
                fgets (buffer, 20480, fp);
                
            }
        printf("%d - ",j);
        puts(buffer);
        
        rewind(fp);
        }
}


    
    
    
    

#ifdef	__cplusplus
}
#endif

#endif	/* HASH_H */

