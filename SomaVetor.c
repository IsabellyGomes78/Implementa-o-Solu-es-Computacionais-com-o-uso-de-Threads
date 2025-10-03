/*
 ============================================================================
  Arquivo: SomaVetor.c
  Objetivo: Calcular a soma dos elementos de um vetor de inteiros
            utilizando múltiplas threads para dividir o trabalho.
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 8             // tamanho do vetor
#define NUM_THREADS 4   // número de threads que farão a soma

// Vetor de dados
int vetor[N] = {10, 20, 30, 40, 50, 60, 70, 80};

// Vetor auxiliar para armazenar resultados parciais
int soma_parcial[NUM_THREADS] = {0};

// Estrutura para passar parâmetros para as threads
typedef struct {
    int id;       // identificador da thread
    int inicio;   // índice inicial do intervalo
    int fim;      // índice final do intervalo
} ThreadArgs;

// Função executada por cada thread
void* soma_intervalo(void* arg) {
    ThreadArgs* dados = (ThreadArgs*) arg;
    int soma = 0;

    for (int i = dados->inicio; i < dados->fim; i++) {
        soma += vetor[i];
    }

    // Armazena o resultado parcial
    soma_parcial[dados->id] = soma;

    pthread_exit(NULL);
}

// Função principal
int main() {
    pthread_t threads[NUM_THREADS];
    ThreadArgs args[NUM_THREADS];
    int intervalo = N / NUM_THREADS;
    int soma_total = 0;

    // Cria as threads, cada uma responsável por uma parte do vetor
    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].id = i;
        args[i].inicio = i * intervalo;
        args[i].fim = (i == NUM_THREADS - 1) ? N : (i + 1) * intervalo;

        pthread_create(&threads[i], NULL, soma_intervalo, (void*) &args[i]);
    }

    // Aguarda as threads finalizarem
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Soma os resultados parciais
    for (int i = 0; i < NUM_THREADS; i++) {
        soma_total += soma_parcial[i];
    }

    // Exibe resultados
    printf("Vetor: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    printf("Soma total: %d\n", soma_total);

    return 0;
}
