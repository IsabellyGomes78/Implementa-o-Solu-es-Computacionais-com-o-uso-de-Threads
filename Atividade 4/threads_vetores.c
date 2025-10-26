/*
 ============================================================================
  Arquivo: threads_vetores.c
  Objetivo: Exemplo de operações com vetores usando threads em C.
            Operações implementadas:
              - Soma de dois vetores
              - Produto escalar (dot product)
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 8             // tamanho dos vetores
#define NUM_THREADS 4   // número de threads

// Vetores de entrada
int vetorA[N] = {1, 2, 3, 4, 5, 6, 7, 8};
int vetorB[N] = {8, 7, 6, 5, 4, 3, 2, 1};

// Vetor resultado da soma
int vetorSoma[N];

// Variável para armazenar resultado parcial do produto escalar
int produto_parcial[NUM_THREADS] = {0};

// Estrutura para passagem de parâmetros às threads
typedef struct {
    int id;
    int inicio;
    int fim;
} ThreadArgs;

// Função que soma partes dos vetores
void* somaVetores(void* arg) {
    ThreadArgs* dados = (ThreadArgs*) arg;

    for (int i = dados->inicio; i < dados->fim; i++) {
        vetorSoma[i] = vetorA[i] + vetorB[i];
    }

    pthread_exit(NULL);
}

// Função que calcula o produto escalar parcial
void* produtoEscalar(void* arg) {
    ThreadArgs* dados = (ThreadArgs*) arg;
    int soma = 0;

    for (int i = dados->inicio; i < dados->fim; i++) {
        soma += vetorA[i] * vetorB[i];
    }

    produto_parcial[dados->id] = soma;

    pthread_exit(NULL);
}

// Função principal
int main() {
    pthread_t threads[NUM_THREADS];
    ThreadArgs args[NUM_THREADS];
    int intervalo = N / NUM_THREADS;
    int produto_total = 0;

    // --- Soma dos vetores ---
    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].id = i;
        args[i].inicio = i * intervalo;
        args[i].fim = (i == NUM_THREADS - 1) ? N : (i + 1) * intervalo;

        pthread_create(&threads[i], NULL, somaVetores, (void*) &args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nResultado da soma dos vetores:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", vetorSoma[i]);
    }
    printf("\n");

    // --- Produto escalar ---
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, produtoEscalar, (void*) &args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Soma dos resultados parciais
    for (int i = 0; i < NUM_THREADS; i++) {
        produto_total += produto_parcial[i];
    }

    printf("\nProduto escalar (A · B): %d\n", produto_total);

    return 0;
}
