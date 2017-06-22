#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

#define N 10
#define TAMALFABETO 256




#define TAMALFABETO 256

typedef char TipoChave[N] ;
typedef unsigned TipoPesos[N] [ TAMALFABETO ] ;
typedef struct TipoItem {
/*
∗ outros componentes
∗
*/
TipoChave Chave;
} TipoItem;
typedef unsigned int TipoIndice;
typedef struct TipoCelula ∗ TipoApontador;
typedef struct TipoCelula {
TipoItem Item;
TipoApontador Prox;
} TipoCelula;
typedef struct TipoLista {
TipoCelula
∗Primeiro ,
∗Ultimo;
} TipoLista;
typedef TipoLista TipoDicionario[M] ;


TipoIndice h(TipoChave Chave, TipoPesos p)
{ int i ; unsigned int Soma = 0;
int comp = strlen (Chave);
for ( i = 0; i < comp; i ++) Soma += p[ i ] [ (unsigned int)Chave[ i ] ] ;
return (Soma %M);
}

void Inicializa (TipoDicionario T)
{ int i ;
for ( i = 0; i < M; i ++) FLVazia(&T[ i ] ) ;
}
TipoApontador Pesquisa(TipoChave Ch, TipoPesos p, TipoDicionario T)
{
/
∗ TipoApontador de retorno aponta para o item anterior da list
a
∗
/
TipoIndice i ; TipoApontador Ap;
i = h(Ch, p);
if (Vazia(T[ i ] ) ) return NULL ;
/
∗ Pesquisa sem sucesso
∗
/
else
{ Ap = T[ i ] . Primeiro;
while (Ap−>Prox−>Prox != NULL &&
strncmp(Ch, Ap−>Prox−>Item.Chave, sizeof(TipoChave)))
Ap = Ap−>Prox;
if ( !strncmp(Ch, Ap−>Prox−>Item.Chave, sizeof(TipoChave))) return Ap;
else return NULL ;
/
∗ Pesquisa sem sucesso
∗
/
}
}

void Insere(TipoItem x, TipoPesos p, TipoDicionario T)
{
if (Pesquisa(x.Chave, p, T) == NULL)
Ins(x, &T[h(x.Chave, p) ] ) ;
else printf ( " Registro ja esta presente\n" );
}
void Retira(TipoItem x, TipoPesos p, TipoDicionario T)
{
TipoApontador Ap;
Ap = Pesquisa(x.Chave, p, T);
if (Ap == NULL)
printf ( " Registro nao esta presente\n" );
else Ret(Ap, &T[h(x.Chave, p)] , &x);
}
