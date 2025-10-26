/*
 ============================================================================
  Arquivo: Produtor-Consumidor-Buffer.c
  Objetivo: Implementar o problema do produtor-consumidor usando threads
            e semáforos para sincronização de acesso ao buffer compartilhado.
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>   // para sleep()

// Definição do tamanho do buffer
#define BUFFER_SIZE 5

// Buffer compartilhado
int buffer[BUFFER_SIZE];
int in = 0;   // índice de inserção (produtor)
int out = 0;  // índice de remoção (consumidor)

// Semáforos e mutex
sem_t empty;   // conta quantos espaços livres existem no buffer
sem_t full;    // conta quantos itens existem no buffer
pthread_mutex_t mutex; // garante exclusão mútua no acesso ao buffer

// Função do produtor
void* produtor(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        item = rand() % 100; // gera item aleatório

        sem_wait(&empty);               // espera espaço livre
        pthread_mutex_lock(&mutex);     // entra na seção crítica

        buffer[in] = item;
        printf("Produtor produziu: %d (posição %d)\n", item, in);
        in = (in + 1) % BUFFER_SIZE;    // avança posição circular

        pthread_mutex_unlock(&mutex);   // sai da seção crítica
        sem_post(&full);                // sinaliza que há um item a mais

        sleep(1); // simula tempo de produção
    }
    pthread_exit(NULL);
}

// Função do consumidor
void* consumidor(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        sem_wait(&full);                // espera um item disponível
        pthread_mutex_lock(&mutex);     // entra na seção crítica

        item = buffer[out];
        printf("Consumidor consumiu: %d (posição %d)\n", item, out);
        out = (out + 1) % BUFFER_SIZE;  // avança posição circular

        pthread_mutex_unlock(&mutex);   // sai da seção crítica
        sem_post(&empty);               // sinaliza que há um espaço livre

        sleep(2); // simula tempo de consumo
    }
    pthread_exit(NULL);
}

// Função principal
int main() {
    pthread_t t_produtor, t_consumidor;

    // Inicializa os semáforos
    sem_init(&empty, 0, BUFFER_SIZE); // começa com buffer vazio
    sem_init(&full, 0, 0);            // nenhum item no buffer
    pthread_mutex_init(&mutex, NULL);

    // Cria threads
    pthread_create(&t_produtor, NULL, produtor, NULL);
    pthread_create(&t_consumidor, NULL, consumidor, NULL);

    // Aguarda finalização das threads
    pthread_join(t_produtor, NULL);
    pthread_join(t_consumidor, NULL);

    // Libera recursos
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
