//============================================================================
// Name        : listaLigadaEstatica.c
// Author      : Prof. Herminio Paucar
// Description : Este programa gerencia listas lineares ligadas (implementacao estatica).
// As listas gerenciadas podem ter MAX elementos (posicoes de 0 a MAX-1 no
//   arranjo A). Não usaremos sentinela nesta estrutura.
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

/* Inicialização da lista sequencial (a lista jah esta criada e eh apontada 
 pelo endereco em l) */
void inicializarLista(LISTA *li); /* inicializarLista */

/* Exibição da lista seqüencial */
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

/* Busca sequencial - funcao de exclusao (retorna no endereço *ant o indice do
 elemento anterior ao elemento que está sendo buscado [ant recebe o elemento
 anterior independente do elemento buscado ser ou não encontrado]) */
int buscaSeqExc(TIPOCHAVE ch, LISTA *l, int *ant); /* buscaSeqExc */

/* Obter nó disponível e marcá-lo como não disponível - esta operação será usada
 junto com inserções, por exemplo */
int obterNo(LISTA *l); /* obterNo */

/* Devolver nó da posição j para a lista de nós disponíveis - coloca-se o nó j
 como primeiro na lista de disponíveis */
void devolverNo(LISTA *l, int j); /* devolverNo */

bool excluirElemLista(LISTA *l, TIPOCHAVE ch); /* excluirElemListaEnc */

/* Exclusão do elemento de chave indicada */
bool excluirElemLista2(LISTA *l, TIPOCHAVE ch); /* excluirElemListaEnc */

/* Destruição da lista sequencial */
void reinicializarLista(LISTA *l); /* destruirLista */

/* Inserção em lista ordenada sem duplicação */
bool inserirElemListaOrd(LISTA *l, REGISTRO reg); /* inserirElemListaOrd */

/* Inserção em lista ordenada sem duplicação - não utilize o método auxiliar */
bool inserirElemListaOrd2(LISTA *l, REGISTRO reg); /* inserirElemListaOrd2 */

#endif
