#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int valor;
    int altura;
    struct Node* esquerda;
    struct Node* direita;
} Node;

// ---------------- Funções Auxiliares ----------------
int altura(Node* no) {
    return no ? no->altura : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int fatorBalanceamento(Node* no) {
    return no ? altura(no->esquerda) - altura(no->direita) : 0;
}

Node* novoNo(int valor) {
    Node* no = (Node*)malloc(sizeof(Node));
    no->valor = valor;
    no->esquerda = no->direita = NULL;
    no->altura = 1;
    return no;
}

// ---------------- Rotações ----------------
Node* rotacaoDireita(Node* y) {
    Node* x = y->esquerda;
    Node* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

Node* rotacaoEsquerda(Node* x) {
    Node* y = x->direita;
    Node* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}

Node* balancear(Node* no) {
    int balance = fatorBalanceamento(no);

    // LL
    if (balance > 1 && fatorBalanceamento(no->esquerda) >= 0)
        return rotacaoDireita(no);

    // RR
    if (balance < -1 && fatorBalanceamento(no->direita) <= 0)
        return rotacaoEsquerda(no);

    // LR
    if (balance > 1 && fatorBalanceamento(no->esquerda) < 0) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    // RL
    if (balance < -1 && fatorBalanceamento(no->direita) > 0) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

// ---------------- Inserção ----------------
Node* inserir(Node* raiz, int valor) {
    if (raiz == NULL)
        return novoNo(valor);

    if (valor < raiz->valor)
        raiz->esquerda = inserir(raiz->esquerda, valor);
    else if (valor > raiz->valor)
        raiz->direita = inserir(raiz->direita, valor);
    else
        return raiz;

    raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));

    return balancear(raiz);
}

// ---------------- Remoção ----------------
Node* menorValor(Node* no) {
    Node* atual = no;
    while (atual->esquerda)
        atual = atual->esquerda;
    return atual;
}

Node* remover(Node* raiz, int valor) {
    if (!raiz)
        return raiz;

    if (valor < raiz->valor)
        raiz->esquerda = remover(raiz->esquerda, valor);
    else if (valor > raiz->valor)
        raiz->direita = remover(raiz->direita, valor);
    else {
        // Nó com apenas 1 filho ou nenhum
        if (!raiz->esquerda || !raiz->direita) {
            Node* temp = raiz->esquerda ? raiz->esquerda : raiz->direita;

            if (!temp) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            free(temp);
        } else {
            Node* temp = menorValor(raiz->direita);
            raiz->valor = temp->valor;
            raiz->direita = remover(raiz->direita, temp->valor);
        }
    }

    if (!raiz)
        return raiz;

    raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));
    return balancear(raiz);
}

// ---------------- Percursos ----------------
void preOrdem(Node* raiz) {
    if (raiz) {
        printf("%d ", raiz->valor);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

void emOrdem(Node* raiz) {
    if (raiz) {
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->valor);
        emOrdem(raiz->direita);
    }
}

void posOrdem(Node* raiz) {
    if (raiz) {
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        printf("%d ", raiz->valor);
    }
}

// ---------------- Ordem por Nível ----------------
typedef struct Fila {
    Node* no;
    struct Fila* prox;
} Fila;

Fila* enfileirar(Fila* fila, Node* no) {
    Fila* novo = (Fila*)malloc(sizeof(Fila));
    novo->no = no;
    novo->prox = NULL;
    if (!fila) return novo;

    Fila* temp = fila;
    while (temp->prox) temp = temp->prox;
    temp->prox = novo;
    return fila;
}

Fila* desenfileirar(Fila* fila, Node** no) {
    if (!fila) {
        *no = NULL;
        return NULL;
    }
    *no = fila->no;
    Fila* prox = fila->prox;
    free(fila);
    return prox;
}

void ordemNivel(Node* raiz) {
    if (!raiz) return;
    Fila* fila = NULL;
    fila = enfileirar(fila, raiz);

    Node* atual;
    while (fila) {
        fila = desenfileirar(fila, &atual);
        printf("%d ", atual->valor);
        if (atual->esquerda)
            fila = enfileirar(fila, atual->esquerda);
        if (atual->direita)
            fila = enfileirar(fila, atual->direita);
    }
}

// ---------------- Main ----------------
int main() {
    Node* raiz = NULL;
    int valores[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++)
        raiz = inserir(raiz, valores[i]);

    printf("Pre-Ordem: ");
    preOrdem(raiz); printf("\n");

    printf("Em-Ordem: ");
    emOrdem(raiz); printf("\n");

    printf("Pos-Ordem: ");
    posOrdem(raiz); printf("\n");

    printf("Ordem de Nível: ");
    ordemNivel(raiz); printf("\n");

    // Remover um nó
    printf("\nRemovendo 40...\n");
    raiz = remover(raiz, 40);

    printf("Pre-Ordem após remoção: ");
    preOrdem(raiz); printf("\n");

    return 0;
}
