#include <stdio.h>
#include <stdlib.h>
#include "arvoreBinaria.h"

// Inicializa um novo nó com o valor dado.
No* criarNo(int valor) {
    No* novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

// Insere um valor recursivamente, retornando a nova raiz.
No* inserir(No* raiz, int valor) {
    if (raiz == NULL){
        return criarNo(valor);
    }
    if (valor <= raiz->valor) {
        raiz->esq = inserir(raiz->esq, valor);
    }
    else {
        raiz->dir = inserir(raiz->dir, valor);
    }

    return raiz;
}

// Busca um valor, retornando o nó ou NULL se não encontrado.
No* buscar(No* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor)
        return raiz;

    if (valor < raiz->valor)
        return buscar(raiz->esq, valor);
    else
        return buscar(raiz->dir, valor);
}

// Realiza o caminhamento EM-ORDEM na árvore.
void emOrdem(No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("%d ", raiz->valor);
        emOrdem(raiz->dir);
    }
}

// Realiza o caminhamento em PRÉ-ORDEM na árvore.
void preOrdem(No* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}

// Realiza o caminhamento em PÓS-ORDEM na árvore.
void posOrdem(No* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d ", raiz->valor);
    }
}

// Calcula a altura da árvore (número de arestas no caminho mais longo até uma folha).
// Considerando a raiz como altura 1, folhas como altura 1, e árvore vazia como 0.
int altura(No* raiz) {
    if (raiz == NULL)
        return 0;
    int altEsq = altura(raiz->esq);
    int altDir = altura(raiz->dir);
    return 1 + (altEsq > altDir ? altEsq : altDir);
}

// Destrói a árvore, liberando a memória de todos os nós.
void destruirArvore(No* raiz) {
    if (raiz != NULL) {
        destruirArvore(raiz->esq);
        destruirArvore(raiz->dir);
        free(raiz);
    }
}