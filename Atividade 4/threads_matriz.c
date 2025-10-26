/*
 ============================================================================
  Arquivo: threads_matriz.c
  Objetivo: Exemplo de operações com matrizes usando threads em C.
            Operações implementadas:
              - Soma de duas matrizes
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define LINHAS 4
#define COLUNAS 4
#define NUM_THREADS 4   // uma thread por linha (exemplo)

// Matrizes de entrada
int matrizA[LINHAS][COLUNAS] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
};

int matrizB[LINHAS][COLUNAS] = {
    {16, 15, 14, 13},
    {12, 11, 10, 9},
    {8, 7, 6, 5},
    {4, 3, 2, 1}
};

// Matriz resultado
int matrizSoma[LINHAS][COLUNAS];

// Estrutura para passar parâmetros às threads
typedef struct {
    int linha; // linha que a thread vai calcular
} ThreadArgs;

// Função executada por cada thread
void* somaLinha(void* arg) {
    ThreadArgs* dados = (ThreadArgs*) arg;
    int l = dados->linha;

    for (int j = 0; j < COLUNAS; j++) {
        matrizSoma[l][j] = matrizA[l][j] + matrizB[l][j];
    }

    pthread_exit(NULL);
}

// Função principal
int main() {
    pthread_t threads[NUM_THREADS];
    ThreadArgs args[NUM_THREADS];

    // Cria uma thread para cada linha da matriz
    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].linha = i;
        pthread_create(&threads[i], NULL, somaLinha, (void*) &args[i]);
    }

    // Aguarda todas as threads finalizarem
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Exibe o resultado
    printf("\nResultado da soma das matrizes:\n");
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            printf("%4d ", matrizSoma[i][j]);
        }
        printf("\n");
    }

    return 0;
}
