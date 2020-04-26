//============================================================================
// Name        : listaSequencialOrdenada.c
// Author      : Prof. Herminio Paucar
// Description : 
//============================================================================
#include <stdio.h>
#define MAX 50
#define ERRO -1
#define true 1
#define false 0

typedef int bool;

typedef int TIPOCHAVE;

typedef struct {
	TIPOCHAVE chave;
// outros campos...
} REGISTRO;

typedef struct {
	REGISTRO A[MAX + 1];
	int nroElem;
} LISTA;

/* Inicialização da lista sequencial (a lista já está criada e é apontada pelo endereço em l) */
void inicializarLista(LISTA *li) {
	li->nroElem = 0;
} /* inicializarLista */

/* Exibição da lista sequencial */
void exibirLista(LISTA *li) {
	int i;
	printf("Lista: \" ");
	for (i = 0; i < li->nroElem; i++)
		printf("%i ", li->A[i].chave);
	printf("\"\n");
} /* exibirLista */

/* Retornar o tamanho da lista (numero de elementos "validos") */
int tamanho(LISTA *li) {
	return li->nroElem;
} /* tamanho */

/* Retornar o tamanho em bytes da lista. Neste caso, isto nao depende do numero
 de elementos que estao sendo usados, pois a alocacao de memoria eh estatica.
 A priori, nao precisariamos do ponteiro para a lista, vamos utiliza-lo apenas
 porque teremos as mesmas funcoes para listas ligadas.
 */
int tamanhoEmBytes(LISTA *li) {
	return sizeof(LISTA);
} /* tamanhoEmBytes */

/* Retornar a chave do primeiro elemento da lista sequencial (caso haja) e ERRO
 caso a lista esteja vazia */
TIPOCHAVE primeiroElem(LISTA *li) {
	if (li->nroElem > 0)
		return li->A[0].chave;
	else
		return ERRO; // lista vazia
} /* primeiroElem */

/* Retornar a chave do ultimo elemento da lista sequencial (caso haja) e ERRO
 caso a lista esteja vazia */
TIPOCHAVE ultimoElem(LISTA *li) {
	if (li->nroElem > 0)
		return li->A[li->nroElem - 1].chave;
	else
		return ERRO; // lista vazia
} /* ultimoElem */

/* Retornar a chave do elemento que está na posição n da LISTA. Lembre-se que as posicoes do
 arranjo A vao de 0 a MAX-1  */
TIPOCHAVE enesimoElem(LISTA *li, int n) {
	if ((n >= 0) && (n < li->nroElem))
		return li->A[n].chave;
	else
		return ERRO;
} /* enesimoElem */

/* Reinicializar a estrutura */
void reinicializarLista(LISTA *li) {
	li->nroElem = 0;
} /* reinicializarLista */

/* Busca sequencial em lista ordenada ou não SEM SENTINELA */
int buscaSequencial(LISTA *li, TIPOCHAVE ch) {
	int i = 0;
	while (i < li->nroElem) {
		if (ch == li->A[i].chave)
			return i; // achou
		else
			i++;
	}
	return ERRO; // não achou
} /* buscaSequencial */

/* Busca sequencial em lista COM SENTINELA (vetor criado com MAX+1 posições) */
int buscaSentinela(LISTA *li, TIPOCHAVE ch) {
	int i = 0;
	li->A[li->nroElem].chave = ch; // sentinela
	while (li->A[i].chave != ch)
		i++;
	if (i > li->nroElem - 1)
		return ERRO; // não achou
	else
		return i;
} /* buscaSentinela */

/* Busca sequencial em lista COM SENTINELA (vetor criado com MAX+1 posições) 
 considerando o arranjo ordenado */
int buscaSentinelaOrdenada(LISTA *li, TIPOCHAVE ch) {
	int i = 0;
	li->A[li->nroElem].chave = ch; // sentinela
	while (li->A[i].chave < ch)
		i++;
	if (i == li->nroElem || li->A[i].chave != ch)
		return ERRO; // não achou
	else
		return i;
} /* buscaSentinela */

/* Busca binaria em lista ordenada */
int buscaBinaria(LISTA *li, TIPOCHAVE ch) {
	int esq, dir, meio;
	esq = 0;
	dir = li->nroElem - 1;
	while (esq <= dir) {
		meio = ((esq + dir) / 2);
		if (li->A[meio].chave == ch)
			return meio; // achou
		else {
			if (li->A[meio].chave < ch)
				esq = meio + 1;
			else
				dir = meio - 1;
		}
	}
	return ERRO;
} /* buscaBinaria */

/* Exclusão do elemento cuja chave seja igual a ch */
bool excluirElemLista(LISTA *li, TIPOCHAVE ch) {
	int pos, j;
	pos = buscaSequencial(li, ch);
	if (pos == ERRO)
		return false; // não existe
	for (j = pos; j < li->nroElem - 1; j++)
		li->A[j] = li->A[j + 1];
	li->nroElem--;
	return true;
} /* excluirElemLista */

/* Exclusão do elemento cuja chave seja igual a ch em lista ordenada*/
bool excluirElemListaOrd(LISTA *li, TIPOCHAVE ch) {
	int pos, j;
	pos = buscaBinaria(li, ch);
	if (pos == ERRO)
		return false; // não existe
	for (j = pos; j < li->nroElem - 1; j++)
		li->A[j] = li->A[j + 1];
	li->nroElem--;
	return true;
} /* excluirElemListaOrd */

/* Inserção em lista ordenada usando busca binária permitindo duplicação */
bool inserirElemListaOrd(LISTA *li, REGISTRO reg) {
	if (li->nroElem >= MAX)
		return false; // lista cheia
	int pos = li->nroElem;
	while (pos > 0 && li->A[pos - 1].chave > reg.chave) {
		li->A[pos] = li->A[pos - 1];
		pos--;
	}
	li->A[pos] = reg;
	li->nroElem++;
	return true;
} /* inserirElemListaOrd */

/* Inserção em lista ordenada usando busca binária sem duplicação */
bool inserirElemListaOrdSemDup(LISTA *li, REGISTRO reg) {
	if (li->nroElem >= MAX)
		return false; // lista cheia
	int pos;
	pos = buscaBinaria(li, reg.chave);
	if (pos != ERRO)
		return false; // elemento já existe
	pos = li->nroElem - 1;
	while (pos > 0 && li->A[pos].chave > reg.chave) {
		li->A[pos + 1] = li->A[pos];
		pos--;
	}
	li->A[pos + 1] = reg;
	li->nroElem++;
	return true;
} /* inserirElemListaOrd */

int main() {
	LISTA lista;
	inicializarLista(&lista);
	exibirLista(&lista);
	printf("Numero de elementos na lista: %i.\n", tamanho(&lista));
	printf("Tamanho da lista (em bytes): %i.\n", tamanhoEmBytes(&lista));
	REGISTRO reg;
	reg.chave = 9;
	inserirElemListaOrd(&lista, reg);
	exibirLista(&lista);
	reg.chave = 3;
	inserirElemListaOrd(&lista, reg);
	reg.chave = 4;
	inserirElemListaOrd(&lista, reg);
	reg.chave = 1;
	inserirElemListaOrd(&lista, reg);
	reg.chave = 12;
	inserirElemListaOrd(&lista, reg);
	exibirLista(&lista);
	printf("Numero de elementos na lista: %i.\n", tamanho(&lista));
	printf("Tamanho da lista (em bytes): %i.\n", tamanhoEmBytes(&lista));
	printf("Chave 4 encontrada na posicao: %i do arranjo A.\n",
			buscaSequencial(&lista, 4));
	printf("Chave 4 encontrada na posicao: %i do arranjo A.\n",
			buscaBinaria(&lista, 4));
	printf("Chave 4 encontrada na posicao: %i do arranjo A.\n",
			buscaSentinela(&lista, 4));
	if (excluirElemLista(&lista, 4))
		printf("Exclusao bem sucedida: 4.\n");
	if (excluirElemLista(&lista, 8))
		printf("Exclusao bem sucedida: 8.\n");
	if (excluirElemLista(&lista, 9))
		printf("Exclusao bem sucedida: 9.\n");
	exibirLista(&lista);
	printf("Numero de elementos na lista: %i.\n", tamanho(&lista));
	printf("Tamanho da lista (em bytes): %i.\n", tamanhoEmBytes(&lista));
	reinicializarLista(&lista);
	exibirLista(&lista);
	printf("Numero de elementos na lista: %i.\n", tamanho(&lista));
	printf("Tamanho da lista (em bytes): %i.\n", tamanhoEmBytes(&lista));
	return 0;
}

/* SAIDA DO PROGRAMA:
 Lista: " "
 Numero de elementos na lista: 0.
 Tamanho da lista (em bytes): 208.
 Lista: " 9 "
 Lista: " 1 3 4 9 12 "
 Numero de elementos na lista: 5.
 Tamanho da lista (em bytes): 208.
 Chave 4 encontrada na posicao: 2 do arranjo A.
 Chave 4 encontrada na posicao: 2 do arranjo A.
 Chave 4 encontrada na posicao: 2 do arranjo A.
 Exclusao bem sucedida: 4.
 Exclusao bem sucedida: 9.
 Lista: " 1 3 12 "
 Numero de elementos na lista: 3.
 Tamanho da lista (em bytes): 208.
 Lista: " "
 Numero de elementos na lista: 0.
 Tamanho da lista (em bytes): 208.
 */
