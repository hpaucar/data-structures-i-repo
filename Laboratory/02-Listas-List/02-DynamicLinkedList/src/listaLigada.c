//============================================================================
// Name        : listaLigadaEstatica.c
// Author      : Prof. Herminio Paucar
// Description : Este programa gerencia listas lineares ligadas (implementacao estatica).
// As listas gerenciadas podem ter MAX elementos (posicoes de 0 a MAX-1 no
//   arranjo A). Não usaremos sentinela nesta estrutura.
//============================================================================
#include "listaLigada.hpp"

/* Inicialização da lista sequencial (a lista jah esta criada e eh apontada 
 pelo endereco em l) */
void inicializarLista(LISTA *li) {
	int i;
	li->inicio = INVALIDO;
	li->dispo = 0;
	for (i = 0; i < MAX - 1; i++)
		li->A[i].prox = i + 1;
	li->A[MAX - 1].prox = INVALIDO;
} /* inicializarLista */

/* Exibição da lista seqüencial */
void exibirLista(LISTA *li) {
	int i = li->inicio;
	printf("Lista: \" ");
	while (i != INVALIDO) {
		printf("%d ", li->A[i].reg.chave); // soh lembrando TIPOCHAVE = int
		i = li->A[i].prox;
	}
	printf("\"\n");
} /* exibirLista */

/* Retornar o tamanho da lista (numero de elementos "validos") */
int tamanho(LISTA *li) {
	int i = li->inicio;
	int tam = 0;
	while (i != INVALIDO) {
		tam++;
		i = li->A[i].prox;
	}
	return tam;
} /* tamanho */

/* Retornar o tamanho em bytes da lista. Neste caso, isto nao depende do numero
 de elementos que estao sendo usados, pois a alocacao de memoria eh estatica.
 A priori, nao precisariamos do ponteiro para a lista, vamos utiliza-lo apenas
 porque teremos as mesmas funcoes para listas ligadas implementacao nao estatica.
 */
int tamanhoEmBytes(LISTA *li) {
	return sizeof(LISTA);
} /* tamanhoEmBytes */

/* Busca sequencial (lista ordenada ou nao) */
int buscaSeq(LISTA *li, TIPOCHAVE ch) {
	int i = li->inicio;
	while (i != INVALIDO) {
		if (li->A[i].reg.chave == ch)
			return i;
		i = li->A[i].prox;
	}
	return INVALIDO;
} /* buscaSeq */

/* Busca sequencial - funcao de exclusao (retorna no endereço *ant o indice do
 elemento anterior ao elemento que está sendo buscado [ant recebe o elemento
 anterior independente do elemento buscado ser ou não encontrado]) */
int buscaSeqExc(TIPOCHAVE ch, LISTA *li, int *ant) {
	*ant = INVALIDO;
	int i = li->inicio;
	while ((i != INVALIDO) && (li->A[i].reg.chave < ch)) {
		*ant = i;
		i = li->A[i].prox;
	}
	if ((i != INVALIDO) && (li->A[i].reg.chave == ch))
		return i;
	return INVALIDO;
} /* buscaSeqExc */

/* Obter nó disponível e marcá-lo como não disponível - esta operação será usada
 junto com inserções, por exemplo */
int obterNo(LISTA *li) {
	int resultado = li->dispo;
	if (li->dispo != INVALIDO)
		li->dispo = li->A[li->dispo].prox;
	return resultado;
} /* obterNo */

/* Devolver nó da posição j para a lista de nós disponíveis - coloca-se o nó j
 como primeiro na lista de disponíveis */
void devolverNo(LISTA *li, int j) {
	li->A[j].prox = li->dispo;
	li->dispo = j;
} /* devolverNo */

bool excluirElemLista(LISTA *li, TIPOCHAVE ch) {
	int ant = INVALIDO;
	int i = li->inicio;
	while ((i != INVALIDO) && (li->A[i].reg.chave < ch)) {
		ant = i;
		i = li->A[i].prox;
	}
	if (i == INVALIDO || li->A[i].reg.chave != ch)
		return false;
	if (ant == INVALIDO)
		li->inicio = li->A[i].prox;
	else
		li->A[ant].prox = li->A[i].prox;
	devolverNo(li, i);
	return true;
} /* excluirElemListaEnc */

/* Exclusão do elemento de chave indicada */
bool excluirElemLista2(LISTA *li, TIPOCHAVE ch) {
	int ant, i;
	i = buscaSeqExc(ch, li, &ant);
	if (i == INVALIDO)
		return false;
	if (ant == INVALIDO)
		li->inicio = li->A[i].prox;
	else
		li->A[ant].prox = li->A[i].prox;
	devolverNo(li, i);
	return true;
} /* excluirElemListaEnc */

/* Destruição da lista sequencial */
void reinicializarLista(LISTA *li) {
	inicializarLista(li);
} /* destruirLista */

/* Inserção em lista ordenada sem duplicação */
bool inserirElemListaOrd(LISTA *li, REGISTRO reg) {
	if (li->dispo == INVALIDO)
		return false; // se lista cheia, não é possível inserir
	int ant, i;
	i = buscaSeqExc(reg.chave, li, &ant);
	if (i != INVALIDO)
		return false;
	i = obterNo(li);
	li->A[i].reg = reg;
	if (ant == INVALIDO) { // o novo elemento será o 1o da lista (a lista podia estar vazia ou não)
		li->A[i].prox = li->inicio;
		li->inicio = i;
	} else {  // inserção após um elemento já existente
		li->A[i].prox = li->A[ant].prox;
		li->A[ant].prox = i;
	}
	return true;
} /* inserirElemListaOrd */

/* Inserção em lista ordenada sem duplicação - não utilize o método auxiliar */
bool inserirElemListaOrd2(LISTA *li, REGISTRO reg) {
	if (li->dispo == INVALIDO)
		return false; // se lista cheia, não é possível inserir
	int ant = INVALIDO;
	int i = li->inicio;
	while ((i != INVALIDO) && (li->A[i].reg.chave < reg.chave)) {
		ant = i;
		i = li->A[i].prox;
	}
	if (i != INVALIDO && li->A[i].reg.chave == reg.chave)
		return false;
	i = obterNo(li);
	li->A[i].reg = reg;
	if (ant == INVALIDO) { // o novo elemento será o 1o da lista (a lista podia estar vazia ou não)
		li->A[i].prox = li->inicio;
		li->inicio = i;
	} else {  // inserção após um elemento já existente
		li->A[i].prox = li->A[ant].prox;
		li->A[ant].prox = i;
	}
	return true;
} /* inserirElemListaOrd2 */
