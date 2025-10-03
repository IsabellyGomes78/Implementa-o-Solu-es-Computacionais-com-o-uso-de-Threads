/*
 ============================================================================
  Arquivo: CatalagoMusical.c
  Objetivo: Simular um catálogo musical utilizando structs em C.
            Funcionalidades:
              - Cadastrar músicas
              - Listar músicas cadastradas
              - Buscar música por título
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MUSICAS 50   // limite de músicas no catálogo
#define TAM_TITULO 50
#define TAM_ARTISTA 50

// Estrutura que representa uma música
typedef struct {
    char titulo[TAM_TITULO];
    char artista[TAM_ARTISTA];
    int ano;
} Musica;

// Catálogo
Musica catalogo[MAX_MUSICAS];
int qtdMusicas = 0; // contador de músicas cadastradas

// Função para cadastrar uma música
void cadastrarMusica() {
    if (qtdMusicas >= MAX_MUSICAS) {
        printf("\nCatálogo cheio! Não é possível adicionar mais músicas.\n");
        return;
    }

    Musica nova;
    printf("\n=== Cadastro de Música ===\n");
    printf("Título: ");
    fgets(nova.titulo, TAM_TITULO, stdin);
    nova.titulo[strcspn(nova.titulo, "\n")] = '\0'; // remove \n do final

    printf("Artista: ");
    fgets(nova.artista, TAM_ARTISTA, stdin);
    nova.artista[strcspn(nova.artista, "\n")] = '\0';

    printf("Ano de lançamento: ");
    scanf("%d", &nova.ano);
    getchar(); // consome o \n deixado pelo scanf

    catalogo[qtdMusicas] = nova;
    qtdMusicas++;

    printf("\nMúsica cadastrada com sucesso!\n");
}

// Função para listar todas as músicas
void listarMusicas() {
    if (qtdMusicas == 0) {
        printf("\nNenhuma música cadastrada ainda.\n");
        return;
    }

    printf("\n=== Catálogo Musical ===\n");
    for (int i = 0; i < qtdMusicas; i++) {
        printf("[%d] %s - %s (%d)\n",
               i + 1,
               catalogo[i].titulo,
               catalogo[i].artista,
               catalogo[i].ano);
    }
}

// Função para buscar música por título
void buscarMusica() {
    if (qtdMusicas == 0) {
        printf("\nNenhuma música cadastrada ainda.\n");
        return;
    }

    char busca[TAM_TITULO];
    printf("\nDigite o título da música para buscar: ");
    fgets(busca, TAM_TITULO, stdin);
    busca[strcspn(busca, "\n")] = '\0';

    int encontrada = 0;
    for (int i = 0; i < qtdMusicas; i++) {
        if (strcmp(catalogo[i].titulo, busca) == 0) {
            printf("\nMúsica encontrada:\n");
            printf("%s - %s (%d)\n",
                   catalogo[i].titulo,
                   catalogo[i].artista,
                   catalogo[i].ano);
            encontrada = 1;
            break;
        }
    }

    if (!encontrada) {
        printf("\nMúsica não encontrada no catálogo.\n");
    }
}

// Função principal
int main() {
    int opcao;

    do {
        printf("\n=== Catálogo Musical ===\n");
        printf("1. Cadastrar música\n");
        printf("2. Listar músicas\n");
        printf("3. Buscar música por título\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // consome o \n do scanf

        switch (opcao) {
            case 1:
                cadastrarMusica();
                break;
            case 2:
                listarMusicas();
                break;
            case 3:
                buscarMusica();
                break;
            case 0:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
