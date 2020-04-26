//============================================================================
// Name        : listaLigadaEstatica.c
// Author      : Prof. Herminio Paucar
// Description : Este programa gerencia listas lineares ligadas (implementacao estatica).
// As listas gerenciadas podem ter MAX elementos (posicoes de 0 a MAX-1 no
//   arranjo A). N�o usaremos sentinela nesta estrutura.
//============================================================================
#ifndef LISTA_ENLAZADA_H_INCLUDED
#define LISTA_ENLAZADA_H_INCLUDED

#include <stdio.h>
#define MAX 50
#define INVALIDO -1
#define true 1
#define false 0
typedef int bool;

typedef int TIPOCHAVE;

typedef struct {
	TIPOCHAVE chave;
	// outros campos...
} REGISTRO;

typedef struct {
	REGISTRO reg;
	int prox;
} ELEMENTO;

typedef struct {
	ELEMENTO A[MAX];
	int inicio;
	int dispo;
} LISTA;

/* Inicializa��o da lista sequencial (a lista jah esta criada e eh apontada 
 pelo endereco em l) */
void inicializarLista(LISTA *li); /* inicializarLista */

/* Exibi��o da lista seq�encial */
void exibirLista(LISTA *l); /* exibirLista */

/* Retornar o tamanho da lista (numero de elementos "validos") */
int tamanho(LISTA *l); /* tamanho */

/* Retornar o tamanho em bytes da lista. Neste caso, isto nao depende do numero
 de elementos que estao sendo usados, pois a alocacao de memoria eh estatica.
 A priori, nao precisariamos do ponteiro para a lista, vamos utiliza-lo apenas
 porque teremos as mesmas funcoes para listas ligadas implementacao nao estatica.
 */
int tamanhoEmBytes(LISTA *l);

/* Busca sequencial (lista ordenada ou nao) */
int buscaSeq(LISTA *l, TIPOCHAVE ch); /* buscaSeq */

/* Busca sequencial - funcao de exclusao (retorna no endere�o *ant o indice do
 elemento anterior ao elemento que est� sendo buscado [ant recebe o elemento
 anterior independente do elemento buscado ser ou n�o encontrado]) */
int buscaSeqExc(TIPOCHAVE ch, LISTA *l, int *ant); /* buscaSeqExc */

/* Obter n� dispon�vel e marc�-lo como n�o dispon�vel - esta opera��o ser� usada
 junto com inser��es, por exemplo */
int obterNo(LISTA *l); /* obterNo */

/* Devolver n� da posi��o j para a lista de n�s dispon�veis - coloca-se o n� j
 como primeiro na lista de dispon�veis */
void devolverNo(LISTA *l, int j); /* devolverNo */

bool excluirElemLista(LISTA *l, TIPOCHAVE ch); /* excluirElemListaEnc */

/* Exclus�o do elemento de chave indicada */
bool excluirElemLista2(LISTA *l, TIPOCHAVE ch); /* excluirElemListaEnc */

/* Destrui��o da lista sequencial */
void reinicializarLista(LISTA *l); /* destruirLista */

/* Inser��o em lista ordenada sem duplica��o */
bool inserirElemListaOrd(LISTA *l, REGISTRO reg); /* inserirElemListaOrd */

/* Inser��o em lista ordenada sem duplica��o - n�o utilize o m�todo auxiliar */
bool inserirElemListaOrd2(LISTA *l, REGISTRO reg); /* inserirElemListaOrd2 */

#endif
