#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "hash.h"

#define MAXP 64
#define MAXT 127

typedef struct palavra palavra_t;

struct palavra {
	char palavra[MAXP];
	int qtd;
	palavra_t *prox;
};

typedef palavra_t * hash[MAXT];

static int le_palavra (FILE *fp, char *s){
	char c;
	int i = 0;
	
	while((c = fgetc(fp)) != EOF){
		if (isalpha(c))
			break;
	}
	
	if (c == EOF)
		return 0;
	else 
		s[i++] = c;
	
	while( i < MAXT - 1 && (c = fgetc(fp)) != EOF && isalpha(c))
		s[i++] = c;
	s[i] = '\0';
	
	return 1;
}

static void inicializa (hash tab){
	int i;
	for(i = 0; i < MAXT; i++)
		tab[i] = NULL;
}

static int f_hash (char *s){
	int i;
	int total = 0;

	for(i = 0; s[i] != '\0'; i++)
		total += s[i];

	return total % MAXT;
}

static palavra_t *acessa (hash tab, char *s){
	palavra_t *p;
	int h = f_hash (s);
	
	if(tab[h] == NULL) {
		p = (palavra_t *) malloc (sizeof(palavra_t));
	
		strcpy(p->palavra, s);
		p->qtd = 0;
		p->prox = NULL;
		tab[h] = p;
		return p;
	}
	
	for(p = tab[h]; p != NULL; p = p->prox){
		if(strcmp(p->palavra,s) == 0)
			return p;
	}
	p = (palavra_t *) malloc (sizeof(palavra_t));
	strcpy(p->palavra, s);
	p->qtd = 0;
	p->prox = tab[h];	
	tab[h] = p;
	
	
	return p;
	
	
}

static int cont_elems (hash tab){
	int i;
	int total = 0;
	palavra_t *p;
	
	for(i = 0; i < MAXT; i++){
		for(p = tab[i]; p != NULL; p = p->prox)
			total++;
	}
	
	return total;
}

static palavra_t  ** cria_vet (int n, hash tab){
	int i, j = 0;
	palavra_t *p;
	
	palavra_t **vet = (palavra_t **) malloc(sizeof(palavra_t *)*n);
	
	for(i = 0; i < MAXT; i++){
		for (p = tab[i]; p != NULL ; p = p->prox)
			vet[j++] = p;
	}
	
	return vet;
}

static int compara (const void *v1, const void *v2){
	palavra_t ** p1 = (palavra_t **) v1;
	palavra_t ** p2 = (palavra_t **) v2;
	
	if ((*p1)->qtd > (*p2)->qtd) return -1;
	else if ((*p1)->qtd < (*p2)->qtd) return 1;
	else return strcmp ((*p2)->palavra, (*p2)->palavra);
	
}

static void imprime_ordenado(hash tab){
	int i;
	int qtd;
	palavra_t **vet;
	
	qtd = cont_elems(tab);
	vet = cria_vet(qtd,tab);
	
 	qsort(vet,qtd,sizeof(palavra_t **), compara);
	
	for(i = 0; i < qtd; i++){
			printf("%s %d\n", vet[i]->palavra, vet[i]->qtd);
// 			printf("%s %d ", vet[i]->palavra, vet[i]->qtd);
	}
}

int main (int argc, char ** argv){	
	
	FILE *fp;
	hash tab;
	char s[MAXP];
	
	if(argc < 2) {
		printf("Arquivo de entrada não fornecido");
		return 0;
	}
	fp = fopen(argv[1], "rt");
	if(fp == NULL){
		printf("Erro na abertura do arquivo");
		return 0;
	}
	
	inicializa(tab);
	
	while(le_palavra(fp,s)){
		palavra_t *p = acessa(tab, s);
		p->qtd++;
	}
		imprime_ordenado(tab);
	return 0;
}

