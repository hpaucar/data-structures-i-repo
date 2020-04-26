//============================================================================
// Name        :listaSequencial.c
// Author      :Prof. Herminio Paucar
// Description :Este programa gerencia listas lineares sequenciais.
// As listas gerenciadas podem ter MAX elementos (posicoes de 0 a MAX-1 no
//   arranjo A). Alocamos MAX+1 posicoes no arranjo para possibilitar a
//   criacao de um elemento sentinela.
//============================================================================
#include <stdio.h>
#define MAX 50
#define ERRO -1
#define true 1
#define false 0

typedef int bool;

typedef int TIPOCLAVE;

typedef struct {
	TIPOCLAVE clave;
// outros campos...
} REGISTRO;

typedef struct {
	REGISTRO A[MAX + 1];
	int nroElem;
} LISTA;

/* Inicialización de la lista secuencial (la lista ya está creada y apuntada a
 por dirección en l) */
void inicializarLista(LISTA *li) {
	li->nroElem = 0;
} /* inicializarLista */

/* Visualización de lista secuencial */
void exibirLista(LISTA *li) {
	int i;
	printf("Lista: \" ");
	for (i = 0; i < li->nroElem; i++)
		printf("%i ", li->A[i].clave); // só lembrando TIPOCHAVE = int
	printf("\"\n");
} /* exibirLista */

/* Retornar o tamanho da lista (numero de elementos "validos") */
int tamano(LISTA *li) {
	return li->nroElem;
} /* tamanho */

/* Devuelve el tamaño en bytes de la lista. En este caso, no depende del número
 de elementos que se están utilizando, ya que la asignación de memoria es estática.
 A priori, no necesitaríamos el puntero a la lista, solo lo usaremos
 porque tendremos las mismas funciones para las listas vinculadas.
 */
int tamanoEnBytes(LISTA *li) {
	return sizeof(LISTA);
} /* tamanhoEmBytes */

/* Devuelve la clave del primer elemento de la lista secuencial (si existe) y ERROR
 si la lista está vacía */
TIPOCLAVE primeiroElem(LISTA *li) {
	if (li->nroElem > 0)
		return li->A[0].clave;
	else
		return ERRO; // lista vazia
} /* primeiroElem */

/* Devuelve la clave del último elemento de la lista secuencial (si existe) y ERROR
 si la lista está vacía */
TIPOCLAVE ultimoElem(LISTA *li) {
	if (li->nroElem > 0)
		return li->A[li->nroElem - 1].clave;
	else
		return ERRO; // lista vazia
} /* ultimoElem */

/* Devuelve la clave del elemento que está en la posición n de la LISTA. Recuerde que las posiciones de los
 disposición El rango de 0 a MAX-1 */
TIPOCLAVE enesimoElem(LISTA *li, int n) {
	if ((n >= 0) && (n < li->nroElem))
		return li->A[n].clave;
	else
		return ERRO;
} /* enesimoElem */

/* Reinicializar a estrutura */
void reinicializarLista(LISTA *li) {
	li->nroElem = 0;
} /* reinicializarLista */

/* Inserción "directa" en la i-ésima posición (posición i de la disposición A).
 Funciona de la misma manera que un insertionSort: debe mover todos los
 elementos de la misma posición y luego se inserta el nuevo elemento. */
bool insertarElemLista(LISTA *li, REGISTRO reg, int i) {
	int j;
	if ((li->nroElem >= MAX) || (i < 0) || (i > li->nroElem))
		return (false); // lista cheia ou índice inválido
	for (j = li->nroElem; j > i; j--)
		li->A[j] = li->A[j - 1];
	li->A[i] = reg;
	li->nroElem++;
	return true;
} /* inserirElemLista */

/* Búsqueda secuencial en la lista ordenada o no SIN WATCHTOWER */
int busquedaSecuencial(LISTA *li, TIPOCLAVE ch) {
	int i = 0;
	while (i < li->nroElem) {
		if (ch == li->A[i].clave)
			return i; // achou
		else
			i++;
	}
	return ERRO; // não achou
} /* buscaSequencial */

/* Exclusión del elemento cuya clave es igual a ch */

bool excluirElemLista(LISTA *li, TIPOCLAVE ch) {
	int pos, j;
	pos = busquedaSecuencial(li, ch);
	if (pos == ERRO)
		return false; // não existe
	for (j = pos; j < li->nroElem - 1; j++)
		li->A[j] = li->A[j + 1];
	li->nroElem--;
	return true;
} /* excluirElemLista */

/* Busca sequencial em lista COM SENTINELA (vetor criado com MAX+1 posições) */
int busquedaSentinela(LISTA *li, TIPOCLAVE ch) {
	int i = 0;
	li->A[li->nroElem].clave = ch; // sentinela
	while (li->A[i].clave != ch)
		i++;
	if (i > li->nroElem - 1)
		return ERRO; // não achou
	else
		return i;
} /* buscaSentinela */

int main() {
	LISTA lista;
	inicializarLista(&lista);
	exibirLista(&lista);
	printf("Numero de elementos en la lista: %i.\n", tamano(&lista));
	printf("Tamano de la lista (en bytes): %i.\n", tamanoEnBytes(&lista));
	// Create and Add Registro
	REGISTRO reg;
	reg.clave = 9;

	insertarElemLista(&lista, reg, 0);
	exibirLista(&lista);
	reg.clave = 3;
	insertarElemLista(&lista, reg, 1);
	reg.clave = 4;
	insertarElemLista(&lista, reg, 2);
	reg.clave = 1;
	insertarElemLista(&lista, reg, 3);
	reg.clave = 12;
	insertarElemLista(&lista, reg, 2);
	exibirLista(&lista);
	printf("Numero de elementos en la lista: %i.\n", tamano(&lista));
	printf("Tamanho de la lista (en bytes): %i.\n", tamanoEnBytes(&lista));
	printf("Clave 4 encontrada en la posicion: %i del array A.\n",
			busquedaSecuencial(&lista, 4));
	printf("Chave 4 encontrada na posicao: %i do arranjo A.\n",
			busquedaSentinela(&lista, 4));
	if (excluirElemLista(&lista, 4))
		printf("Exclusao bem sucedida: 4.\n");
	if (excluirElemLista(&lista, 8))
		printf("Exclusao bem sucedida: 8.\n");
	if (excluirElemLista(&lista, 9))
		printf("Exclusao bem sucedida: 9.\n");
	exibirLista(&lista);
	printf("Numero de elementos na lista: %i.\n", tamano(&lista));
	printf("Tamanho da lista (em bytes): %i.\n", tamanoEnBytes(&lista));
	reinicializarLista(&lista);
	exibirLista(&lista);
	printf("Numero de elementos na lista: %i.\n", tamano(&lista));
	printf("Tamanho da lista (em bytes): %i.\n", tamanoEnBytes(&lista));
	return 0;
}

/* SAIDA DO PROGRAMA:
 Lista: " "
 Numero de elementos na lista: 0.
 Tamanho da lista (em bytes): 208.
 Lista: " 9 "
 Lista: " 9 3 12 4 1 "
 Numero de elementos na lista: 5.
 Tamanho da lista (em bytes): 208.
 Chave 4 encontrada na posicao: 3 do arranjo A.
 Chave 4 encontrada na posicao: 3 do arranjo A.
 Exclusao bem sucedida: 4.
 Exclusao bem sucedida: 9.
 Lista: " 3 12 1 "
 Numero de elementos na lista: 3.
 Tamanho da lista (em bytes): 208.
 Lista: " "
 Numero de elementos na lista: 0.
 Tamanho da lista (em bytes): 208.
 */
