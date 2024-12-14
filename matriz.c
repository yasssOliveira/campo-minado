#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>

//função de criação da matriz inicial
int** criandoMatriz(int linha, int coluna){
    int **matriz = (int**) malloc((linha+1) * sizeof(int*));

    for (int contL = 1; contL <= linha; contL++) {
        matriz[contL] = (int*) malloc((coluna+1) * sizeof(int));
        for(int contC = 1; contC <= coluna; contC++){
            matriz[contL][contC] = 0;
        }
    }
    
    return matriz;
}

//função que cria a matriz fechada que vai aparecer pro usuário
char** matrizInicial(int linha, int coluna){
    char **matriz = (char**) malloc((linha+1) * sizeof(char*));

    for (int contL = 1; contL <= linha; contL++) {
        matriz[contL] = (char*) malloc((coluna+1) * sizeof(char));
        for(int contC = 1; contC <= coluna; contC++){
            matriz[contL][contC] = 'x';
        }
    }
    
    return matriz;
}


//função que imprime a matriz de números inteiros
void imprimindoMatrizValores(int tamanho, int** matriz){
    printf("     ");
    for(int num = 1; num <= tamanho; num++){
        printf(" -----");
    }
    printf("\n");
    printf("     ");
    for(int num = 1; num <= tamanho; num++){
        printf("| %03d ", num); //imprime os indices das colunas
    }
    printf("|\n");
    printf(" ----");
    for(int num = 1; num <= tamanho; num++){
        printf(" -----");
    }
    printf("\n");
    for(int i = 1; i <= tamanho; i++){
        printf("| %02d |", i); //imprime os índices das linhas
        for(int j = 1; j <= tamanho; j++){
            printf(" %03d |", matriz[i][j]);
        }

        printf("\n");
        printf(" ----");
        for(int num = 1; num <= tamanho; num++){
            printf(" -----");
        }
        printf("\n");
    }
    printf("\n");
}

//função que imprime a matriz de char
void imprimindoMatrizInicial(int tamanho, char** matriz){
    printf("     ");
    for(int num = 1; num <= tamanho; num++){
        printf(" -----");
    }
    printf("\n");
    printf("     ");
    for(int num = 1; num <= tamanho; num++){
        printf("| %03d ", num); //imprime os indices das colunas
    }
    printf("|\n");
    printf(" ----");
    for(int num = 1; num <= tamanho; num++){
        printf(" -----");
    }
    printf("\n");
    for(int i = 1; i <= tamanho; i++){
        printf("| %02d |", i); //imprime os índices das linhas
        for(int j = 1; j <= tamanho; j++){
            printf("  %c  |", matriz[i][j]);
        }
        printf("\n");
        printf(" ----");
        for(int num = 1; num <= tamanho; num++){
            printf(" -----");
        }
        printf("\n");
    }
    printf("\n");
}

//função que libera memória alocada na matriz de inteiros
void liberarMatrizInt(int** matriz, int tamanho){
    for (int i = 1; i <= tamanho; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

//função que libera memória alocada na matriz char
void liberarMatrizChar(char** matriz, int tamanho){
    for (int i = 1; i <= tamanho; i++) {
        free(matriz[i]);
    }
    free(matriz);
}
