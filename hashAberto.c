#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"


#define VAZIO " ! ! ! ! ! ! ! ! ! ! "
#define RETIRADO "∗∗∗∗∗∗∗∗∗∗"
#define M 7
#define N 11
/*
∗ Tamanho da chave
∗
*/
typedef unsigned int TipoApontador;
typedef char TipoChave[N] ;
typedef unsigned TipoPesos[N] ;
typedef struct TipoItem {
/*
∗ outros componentes
∗
*/
TipoChave Chave;
} TipoItem;
typedef unsigned int TipoIndice;
typedef TipoItem TipoDicionario[M] ;

typedef char TipoChave[N] ;

TipoIndice h(TipoChave Chave, TipoPesos p){
    int i ; unsigned int Soma = 0;
    int comp = strlen (Chave);
    
    for ( i = 0; i < comp; i ++)
        Soma += p[ i ] [ (unsigned int)Chave[ i ] ] ;
    
    return (Soma %M);
}


void Inicializa (TipoDicionario T)
{ int i ;
for ( i = 0; i < M; i ++) memcpy(T[ i ] .Chave, VAZIO , N);
}
TipoApontador Pesquisa(TipoChave Ch, TipoPesos p, TipoDicionario T)
{ unsigned int i = 0; unsigned int Inicial ;
Inicial = h(Ch, p);
while (strcmp(T[( Inicial + i ) % M] .Chave,VAZIO) != 0 &&
strcmp (T[( Inicial + i ) % M] .Chave, Ch) != 0 && i < M)
i ++;
if (strcmp( T[( Inicial + i ) % M] .Chave, Ch) == 0)
return (( Inicial + i ) % M);
else return M;
/*
∗ Pesquisa sem sucesso
∗
*/
}


void Insere(TipoItem x, TipoPesos p, TipoDicionario T)
{ unsigned int i = 0; unsigned int Inicial ;
if (Pesquisa(x.Chave,p,T) < M) { printf ( "Elemento ja esta presente\n" ) ; return; }
Inicial = h(x.Chave, p);
while (strcmp(T[( Inicial + i ) % M] .Chave,VAZIO) != 0 &&
strcmp(T[( Inicial + i ) % M] .Chave, RETIRADO) != 0 && i < M) i ++;
if ( i < M)
{ strcpy(T[( Inicial + i ) % M] .Chave, x.Chave);
/*
∗ Copiar os demais campos de x, se existirem
∗
*/
}
else printf ( " Tabela cheia\n" );
}
void Retira(TipoChave Ch, TipoPesos p, TipoDicionario T)
{ TipoIndice i ;
i = Pesquisa(Ch, p, T);
if ( i < M)
memcpy(T[ i ] .Chave, RETIRADO , N);
else printf ( "Registro nao esta presente\n" );
}
