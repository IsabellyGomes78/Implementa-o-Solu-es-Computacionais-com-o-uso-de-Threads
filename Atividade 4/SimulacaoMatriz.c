/*
 ============================================================================
  Arquivo: SimulacaoMatriz.c
  Objetivo: Exemplo de operações com matrizes:
            - Preenchimento com números aleatórios
            - Exibição formatada
            - Cálculo da soma das linhas e colunas
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LINHAS 4
#define COLUNAS 5

// Função para preencher a matriz com valores aleatórios
void preencherMatriz(int matriz[LINHAS][COLUNAS]) {
    srand(time(NULL)); // inicializa a semente para números aleatórios

    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            matriz[i][j] = rand() % 100; // valores entre 0 e 99
        }
    }
}

// Função para exibir a matriz
void exibirMatriz(int matriz[LINHAS][COLUNAS]) {
    printf("\nMatriz gerada:\n");
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            printf("%4d ", matriz[i][j]);
        }
        printf("\n");
    }
}

// Função para calcular a soma das linhas
void somaLinhas(int matriz[LINHAS][COLUNAS]) {
    printf("\nSoma das linhas:\n");
    for (int i = 0; i < LINHAS; i++) {
        int soma = 0;
        for (int j = 0; j < COLUNAS; j++) {
            soma += matriz[i][j];
        }
        printf("Linha %d: %d\n", i, soma);
    }
}

// Função para calcular a soma das colunas
void somaColunas(int matriz[LINHAS][COLUNAS]) {
    printf("\nSoma das colunas:\n");
    for (int j = 0; j < COLUNAS; j++) {
        int soma = 0;
        for (int i = 0; i < LINHAS; i++) {
            soma += matriz[i][j];
        }
        printf("Coluna %d: %d\n", j, soma);
    }
}

// Função principal
int main() {
    int matriz[LINHAS][COLUNAS];

    preencherMatriz(matriz);
    exibirMatriz(matriz);
    somaLinhas(matriz);
    somaColunas(matriz);

    return 0;
}
