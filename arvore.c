#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXP 640
#define MAXT 12700

typedef struct arv Arv;

struct arv {
    char info[MAXP];
    int qtd;
    int ocorrencias[MAXP];
    Arv* esq;
    Arv* dir;
};

Arv* arv_criavazia(void) {
    return NULL;
}

Arv* arv_cria(char* str, Arv* e, Arv* d) {
    Arv* arv;

    arv = (Arv*) malloc(sizeof (Arv));

    arv->dir = d;
    arv->esq = e;
    strcpy(arv->info, str);

    return arv;
}

Arv* criaArv() {
    Arv* arv;

    arv = (Arv*) malloc(sizeof (Arv));
    return arv;
    /*
    arv->dir = d;
    arv->esq = e;
    strcpy(arv->info,str);
    
    rturn arv;*/
}

Arv* arv_libera(Arv* a) {

    if (!arv_vazia(a)) {
        arv_libera(a->esq);
        arv_libera(a->dir);
        free(a);
    }

    a == NULL;

    return a;
}

/*
void insere (Arv *r,Arv novo) {  

    if (strcmp((r)->info,(novo)->info) < 0 ) 
       r->esq = insere (r->esq, novo);
    else 
       r->dir = insere (r->dir, novo);
    //return r;
}*/

int arv_vazia(Arv* a) {
    if (a == NULL)
        return 1;
    else
        return 0;
}

int arv_pertence(Arv* a, char c) {
    if (arv_vazia(a))
        return 0;
    //return (a->info == c || arv_pertence(a->dir, c) || arv_pertence(a->esq, c));
}

void arv_imprime(Arv* a) {

    if (!arv_vazia(a)) {
        printf("%s\n", a->info);
        arv_imprime(a->dir);
        arv_imprime(a->esq);
    }

}
/*
Arv* arv_pai(Arv* a, char c) {
    Arv* b;

    if (a == NULL)
        return NULL;

    else if //((a->dir != NULL && a->dir->info == c) || (a->esq != NULL && a->esq->info == c))
        return a;
    else {
        b = arv_pai(a->dir, c);
        if (b != NULL)
            return b;
        b = arv_pai(a->esq, c);
        if (b != NULL)
            return b;
    }

    return NULL;
}*/

//conta quqantas folhas
//acho que é inutil @SEE www.nemo.inf.ufes.br/jbutlr.domain.package && NEMO UTILSSSSS

int folhas(Arv* a) {
    static count = 0;

    if (!arv_vazia(a)) {
        if (a->dir == NULL && a->esq == NULL)
            count++;
        else {
            folhas(a->dir);
            folhas(a->esq);
        }
    }

    return count;

}

//conta quqantas folhas
//acho que é inutil @SEE www.nemo.inf.ufes.br/jbutlr.domain.package && NEMO UTILSSSSS

int ocorrencias(Arv* a, char c) {
    static count = 0;

    if (!arv_vazia(a)) {
        // if (c == a->info)
        count++;

        ocorrencias(a->esq, c);
        ocorrencias(a->dir, c);
    }

    return count;
}

//conta quqantas folhas
//acho que é inutil @SEE www.nemo.inf.ufes.br/jbutlr.domain.package && NEMO UTILSSSSS

char info(Arv* a) {
    //return a->info;
}


////////////TAD ABB

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
        abb_imprime(a->esq);
        printf("%15s    %d\n", a->key,a->qtd);
        
        //for (j = 0; j < (a->qtd); j++) {
          //  printf("%d ", a->ocorrencias[j]);
        //}
        abb_imprime(a->dir);
    }
}

NoArv* abb_busca(NoArv* r,char* str) {
    if (r == NULL){
        printf("sem resultados\n");
        return ;
    }
        
    else if(strcmp(r->key,str)<0) //(r->info > str)
        return abb_busca(r->esq, str);
    else if(strcmp(r->key,str)>0) //(r->info < str)
        return abb_busca(r->dir, str);
    else return r;
}

NoArv* abb_insere(NoArv* a, char* str) {
    if (a == NULL) {
        a = (NoArv*) malloc(sizeof (NoArv));
        a->qtd=0;
        strcpy(a->key, str);
        a->esq = a->dir = NULL;
    } else if (strcmp(a->key, str) < 0) //(v < a->info)
        a->esq = abb_insere(a->esq, str);
    else if (strcmp(a->key, str) > 0) //(v > a->info)
        a->dir = abb_insere(a->dir, str);
    return a;
}
//reoslver para retornar, sem free!

NoArv* abb_retira(NoArv* r, int v) {
    if (r == NULL)
        return NULL;
    else if (r->info > v)
        r->esq = abb_retira(r->esq, v);
    else if (r->info < v)
        r->dir = abb_retira(r->dir, v);
    else { /* achou o nó a remover */
        /* nó sem filhos */
        if (r->esq == NULL && r->dir == NULL) {
            free(r);
            r = NULL;
        }/* nó só tem filho à direita */
        else if (r->esq == NULL) {
            NoArv* t = r;
            r = r->dir;
            free(t);
        }            /* só tem filho à esquerda */
        else if (r->dir == NULL) {
            NoArv* t = r;
            r = r->esq;
            free(t);
        }/* nó tem os dois filhos */
        else {
            NoArv* f = r->esq;
            while (f->dir != NULL) {
                f = f->dir;
            }
            r->info = f->info; /* troca as informações */
            f->info = v;
            r->esq = abb_retira(r->esq, v);
        }
    }
    return r;
}

void insereKeys(FILE* fp, NoArv* arv) {


}

int linha = 1;
int flag = 0;


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

    while (i < MAXT - 1 && (c = fgetc(fp)) != EOF && (isalpha(c))) {
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

int main(int argc, char** argv) {

    NoArv* arv;

    arv = abb_cria();

    FILE *fp;

    if (argc < 2) {
        printf("Arquivo de entrada não fornecido");
        return 0;
    }
    fp = fopen(argv[1], "rt");  //palavras chave
    if (fp == NULL) {
        printf("Erro na abertura do arquivo");
        return 0;
    }

    //******************************************
    char palavra[640];

    while (!feof(fp)) {
        //printf("aa");
        //fgets (palavra, 640, fp);
        fscanf(fp, "%s\n", &palavra);
        //printf("**%s",palavra);
        arv = abb_insere(arv, palavra);
    }//insere todo mundo do arquivo de chaves na arvore
    //******************************************
    //fclose(fp);
    
    //printf("passou 1");
    
    FILE* file2;
    file2 = fopen(argv[2], "rt"); //textao
    
    //printf("passou 2");
    
    
    while (le_palavra(file2, palavra)) {
        //printf("passou 3");
        //printf("%s",palavra);
        NoArv* catch = abb_busca(arv,palavra);
        
        if (catch!=NULL) {
            //break;
        }
        
        //catch->qtd++;
        
        if(catch->ocorrencias[catch->qtd-1]!=linha){
            catch->ocorrencias[catch->qtd] = linha;
            catch->qtd++;
        }
    }
    
    
    
    
    //buscando corretamente na arv e podendo alterar depois!
    
    //printf("aeeee - %s",catch->key);
    
    //strcpy(catch->key,"FOOOOOR");
    
    
    
    
    
    
    
    //abb_imprime(arv);

    return (EXIT_SUCCESS);
}

