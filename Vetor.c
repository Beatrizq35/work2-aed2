#include "vetor.h"

// Cria vetor de inteiros com capacidade para tamanho elementos.
Vetor *vetorCriar(int tamanho) {
    Vetor *v = (Vetor *) malloc(sizeof(Vetor));
    if (!v) { 
        perror("malloc Vetor"); /*imprime a mensagem de erro do sistema*/
        exit(EXIT_FAILURE); /*encerra o programa com código de erro*/
    }
    v->dados = (int *) malloc(sizeof(int) * tamanho);
    if (!v->dados) { 
        perror("malloc dados"); 
        exit(EXIT_FAILURE); 
    }
    v->tamanho = tamanho;
    return v;
}
// Libera memória alocada para o vetor.
void vetorDestruir(Vetor *v) {
    if (!v) return;
    free(v->dados);
    free(v);
}

// Insere valor no índice indicado.
void vetorInserir(Vetor *v, int indice, int valor) {
    if (indice < 0 || indice >= v->tamanho) return;
    v->dados[indice] = valor;
}

// Função de comparação para qsort (ordena inteiros em ordem crescente).
static int cmpInt(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Ordena o vetor usando qsort interno.
void vetorOrdenar(Vetor *v) {
    qsort(v->dados, v->tamanho, sizeof(int), cmpInt);
}

// Busca binária: retorna índice do valor ou -1 se não encontrado.
int vetorBuscaBinaria(Vetor *v, int valor) {
    int esq = 0, dir = v->tamanho - 1;
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        if (v->dados[meio] == valor) return meio;
        if (v->dados[meio] < valor)  esq = meio + 1;
        else                          dir = meio - 1;
    }
    return -1;
}