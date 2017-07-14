/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   arvore.h
 * Author: gabrielreisn
 *
 * Created on 14 de Julho de 2017, 00:16
 */

#ifndef ARVORE_H
#define ARVORE_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXP 640
#define MAXT 12700

struct noArv {
    int info;
    char key[640];
    int qtd;
    int ocorrencias[MAXP];
    struct noArv* esq;
    struct noArv* dir;
};
typedef struct noArv NoArv;

NoArv* abb_cria(void) {
    NoArv* a;

    a = (NoArv*) malloc(sizeof (NoArv));

    return a;
}

void abb_imprime(NoArv* a) {
    int j;

    if (a != NULL) {
        abb_imprime(a->dir);
        //abb_imprime(a->esq);
        printf("%15s    ", a->key);

        for (j = 0; j < (a->qtd); j++) {
            printf("%d ", a->ocorrencias[j]);
        }
        printf("\n");
        //abb_imprime(a->dir);
        abb_imprime(a->esq);
    }
}

NoArv* abb_busca(NoArv* r, char* str) {
    if (r == NULL) {
        //printf("sem resultados\n");
        return;
    }
    else if (strcmp(r->key, str) < 0) //(r->info > str)
        return abb_busca(r->esq, str);
    else if (strcmp(r->key, str) > 0) //(r->info < str)
        return abb_busca(r->dir, str);
    else return r;
}

NoArv* abb_insere(NoArv* a, char* str) {
    if (a == NULL) {
        a = (NoArv*) malloc(sizeof (NoArv));
        a->qtd = 0;
        strcpy(a->key, str);
        a->esq = a->dir = NULL;
    } else if (strcmp(a->key, str) < 0) //(v < a->info)
        a->esq = abb_insere(a->esq, str);
    else if (strcmp(a->key, str) > 0) //(v > a->info)
        a->dir = abb_insere(a->dir, str);
    return a;
}

int linha2 = 1;
int flag2 = 0;

static int le_palavra(FILE *fp, char *s) {
    char c;
    int i = 0;

    if (flag2 == 1) {
        linha2++;
        flag2 = 0;
    }


    while ((c = fgetc(fp)) != EOF) {

        if (isalpha(c))
            break;
        if (c == '\n') {
            linha2++;
        }
    }

    if (c == EOF) {
        return 0;
    } else {
        s[i++] = c;
    }

    while (i < MAXT - 1 && (c = fgetc(fp)) != EOF && (isalpha(c))) {
        s[i++] = c;
    }

    s[i] = '\0';

    if (c != '\n')
        return 1;


    if (c == '\n') {
        flag2 = 1;
    }

    return 1;
}



#ifdef __cplusplus
}
#endif

#endif /* ARVORE_H */

