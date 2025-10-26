/*
 ============================================================================
  Arquivo: hello_threads.c
  Objetivo: Exemplo básico de criação de threads em C.
            Cada thread imprime uma mensagem identificando seu ID.
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5   // quantidade de threads

// Função executada por cada thread
void* imprimeMensagem(void* arg) {
    int id = *((int*) arg); // recupera o ID passado como argumento
    printf("Olá! Eu sou a thread %d\n", id);
    pthread_exit(NULL);
}

// Função principal
int main() {
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];

    // Criação das threads
    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i + 1; // define o ID da thread (1,2,3,...)
        pthread_create(&threads[i], NULL, imprimeMensagem, (void*) &ids[i]);
    }

    // Espera todas as threads terminarem
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Todas as threads terminaram.\n");

    return 0;
}
