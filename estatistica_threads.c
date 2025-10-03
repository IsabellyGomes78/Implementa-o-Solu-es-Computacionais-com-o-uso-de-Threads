/*
 ============================================================================
  Arquivo: estatistica_threads.c
  Objetivo: Calcular estatísticas (média, mínimo e máximo) de um vetor de
            números inteiros utilizando threads para paralelismo.
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10  // tamanho do vetor

// Vetor de dados
int vetor[N] = {12, 45, 7, 89, 32, 56, 23, 91, 14, 67};

// Variáveis globais para armazenar resultados
double media = 0;
int minimo = 0;
int maximo = 0;

// Função que calcula a média
void* calcula_media(void* arg) {
    int soma = 0;
    for (int i = 0; i < N; i++) {
        soma += vetor[i];
    }
    media = (double) soma / N;
    pthread_exit(NULL);
}

// Função que encontra o mínimo
void* calcula_minimo(void* arg) {
    int menor = vetor[0];
    for (int i = 1; i < N; i++) {
        if (vetor[i] < menor) {
            menor = vetor[i];
        }
    }
    minimo = menor;
    pthread_exit(NULL);
}

// Função que encontra o máximo
void* calcula_maximo(void* arg) {
    int maior = vetor[0];
    for (int i = 1; i < N; i++) {
        if (vetor[i] > maior) {
            maior = vetor[i];
        }
    }
    maximo = maior;
    pthread_exit(NULL);
}

// Função principal
int main() {
    pthread_t t_media, t_min, t_max;

    // Cria threads para cada cálculo
    pthread_create(&t_media, NULL, calcula_media, NULL);
    pthread_create(&t_min, NULL, calcula_minimo, NULL);
    pthread_create(&t_max, NULL, calcula_maximo, NULL);

    // Aguarda as threads terminarem
    pthread_join(t_media, NULL);
    pthread_join(t_min, NULL);
    pthread_join(t_max, NULL);

    // Exibe resultados
    printf("Vetor de dados: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    printf("Média: %.2f\n", media);
    printf("Mínimo: %d\n", minimo);
    printf("Máximo: %d\n", maximo);

    return 0;
}
