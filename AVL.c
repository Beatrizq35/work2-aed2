#include "avl.h"

 // Fator de balanceamento (FB):
 // FB = altura(subárvore direita) - altura(subárvore esquerda)


// Pega altura maior entre dois filhos (usado para atualizar altura do nó).
static int max2(int a, int b) { return a > b ? a : b; }

// Retorna a altura de um nó (NULL tem altura 0, folha tem altura 1).
static int alturaNo(NoAVL *n) {
    return (n == NULL) ? 0 : n->altura;
}

// Recalcula a altura armazenada no nó a partir dos filhos.
static void atualizarAltura(NoAVL *n) {
    if (n)
        n->altura = 1 + max2(alturaNo(n->esq), alturaNo(n->dir));
}

// Fator de balanceamento real: altura(dir) - altura(esq).
static int fb(NoAVL *n) {
    if (!n) return 0;
    return alturaNo(n->dir) - alturaNo(n->esq);
}

// Alocacao de novo nó AVL (inserção de valor novo). 
static NoAVL *criarNoAVL(int valor) {
    NoAVL *novo = (NoAVL *) malloc(sizeof(NoAVL));
    if (!novo) { perror("malloc criarNoAVL"); exit(EXIT_FAILURE); }
    novo->valor  = valor;
    novo->altura = 1;    /* folha tem altura 1 */
    novo->esq    = NULL;
    novo->dir    = NULL;
    return novo;
}

/* ---------- ROTAÇÕES ---------- */

// Rotação SIMPLES à direita (caso esquerda-esquerda)
static NoAVL *rotacaoDireita(NoAVL *raiz) {
    NoAVL *novoRaiz = raiz->esq;
    NoAVL *filhoOrfao = novoRaiz->dir;

    novoRaiz->dir = raiz;
    raiz->esq = filhoOrfao;

    atualizarAltura(raiz);
    atualizarAltura(novoRaiz);
    return novoRaiz;
}

// Rotação SIMPLES à esquerda (caso direita-direita)
static NoAVL *rotacaoEsquerda(NoAVL *raiz) {
    NoAVL *novoRaiz = raiz->dir;
    NoAVL *filhoOrfao = novoRaiz->esq;

    novoRaiz->esq = raiz;
    raiz->dir = filhoOrfao;

    atualizarAltura(raiz);
    atualizarAltura(novoRaiz);
    return novoRaiz;
}

// Rotação DUPLA esquerda-direita (caso esquerda-direita).
static NoAVL *rotacaoEsquerdaDireita(NoAVL *raiz) {
    raiz->esq = rotacaoEsquerda(raiz->esq);
    return rotacaoDireita(raiz);
}

// Rotação DUPLA direita-esquerda (caso direita-esquerda).
static NoAVL *rotacaoDireitaEsquerda(NoAVL *raiz) {
    raiz->dir = rotacaoDireita(raiz->dir);
    return rotacaoEsquerda(raiz);
}

/* ---------- REBALANCEAMENTO ---------- */

static NoAVL *rebalancear(NoAVL *raiz) {
    atualizarAltura(raiz);
    int fatorRaiz = fb(raiz);

    // Caso Esquerda-Esquerda
    if (fatorRaiz < -1 && fb(raiz->esq) <= 0)
        return rotacaoDireita(raiz);

    // Caso Esquerda-Direita
    if (fatorRaiz < -1 && fb(raiz->esq) > 0)
        return rotacaoEsquerdaDireita(raiz);

    // Caso Direita-Direita
    if (fatorRaiz > 1 && fb(raiz->dir) >= 0)
        return rotacaoEsquerda(raiz);

    // Caso Direita-Esquerda
    if (fatorRaiz > 1 && fb(raiz->dir) < 0)
        return rotacaoDireitaEsquerda(raiz);

    return raiz;
}

/* ---------- INSERÇÃO ---------- */

// Insere valor na árvore AVL, retornando a nova raiz (ignora se já existir).
NoAVL *avlInserir(NoAVL *raiz, int valor) {
    if (raiz == NULL)
        return criarNoAVL(valor);

    if (valor < raiz->valor)
        raiz->esq = avlInserir(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = avlInserir(raiz->dir, valor);
    else
        return raiz;

    return rebalancear(raiz);
}

/* ---------- BUSCA ---------- */

NoAVL *avlBuscar(NoAVL *raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor)
        return raiz;
    if (valor < raiz->valor)
        return avlBuscar(raiz->esq, valor);
    return avlBuscar(raiz->dir, valor);
}

/* ---------- ALTURA ---------- */

int avlAltura(NoAVL *raiz) {
    return alturaNo(raiz);
}

/* ---------- DESTRUÇÃO ---------- */

void avlDestruir(NoAVL *raiz) {
    if (raiz == NULL) return;
    avlDestruir(raiz->esq);
    avlDestruir(raiz->dir);
    free(raiz);
}