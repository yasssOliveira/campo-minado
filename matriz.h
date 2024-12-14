
#ifndef MATRIZ_H
#define MATRIZ_H

/*função que cria, aloca memória e preenche com 0 todas as posições de uma matriz de números inteiros,
que vai guardar as informações da quantidade de bombas ao redor de uma coordenada e a coordenada das 
bombas
Recebe os números de linha e coluna como parâmentro e retorna o ponteiro para a matriz criado com o 
tamanho de linhas e colunas desejadas*/
int** criandoMatriz(int linha, int coluna);

/*função que cria, aloca memória e preenche com 'x' todas as posições de uma matriz de char, que vai 
ser mostrada inicialmente para o usuário
Recebe os números de linha e coluna como parâmetro e retorna o ponteiro para a matriz criado com o
tamanho de linhas e colunas desejadas*/
char** matrizInicial(int linha, int coluna);

/*função que imprime a matriz de inteiros
Recebe tamanho e ponteiro de matriz como parâmetros e serve para imprimir de maneira organizada e bem 
definida a matriz de números inteiros, que é mostrada para o usuário ao final de cada jogo*/
void imprimindoMatrizValores(int tamanho, int** matriz);

/*função que imprime a matriz de char
Recebe tamanho e ponteiro de matriz como parâmetros e serve para imprimir de maneira organizada e bem 
definida a matriz de char, que é mostrada ao usuário durante cada jogo*/
void imprimindoMatrizInicial(int tamanho, char** matriz);

/*Funçao que libera memória alocada na matriz de inteiros*/
void liberarMatrizInt(int** matriz, int tamanho);

/*função que libera memória alocada na matriz de char*/
void liberarMatrizChar(char** matriz, int tamanho);

#endif
