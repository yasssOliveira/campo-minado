#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "matriz.h"

/*função que checa se a coordenada digitada pelo jogador é valida, ou seja, se ela existe dentro das
limitações de tamanho que a matriz implica
Recebe linha, coluna e tamanho como parâmentro e retorna 1 caso a coordenada seja válida e 0 caso 
seja inválida*/
int podeCoordenada(int linha, int coluna, int tamanho){
    if((linha >= 1 && linha <= tamanho) && (coluna >= 1 && coluna <= tamanho)){
        return 1; //válida
    }
    else{
        return 0; //inválida
    }   
}

/*função que sorteia a posição em que as bombas serão alocadas na matriz
Recebe o ponteiro de matriz, a quantidade de bombas, linha e coluna como parâmetros e não retorna nada
utiliza a função rand para gerar coordenadas aleatórias na matriz e aloca as bombas (-1) nelas*/
void sorteandoPosicao(int** matriz, int qtdBombas, int linha, int coluna){
    int bombas = 0; //contador de bombas
    srand(time(NULL));

    while(bombas < qtdBombas){ //roda até a quantidade de bombas setadas ser igual a quantidade de bombas pré definidas
        int pLinha = (rand() % linha)+1; //sorteia uma posição na linha
        int pColuna = (rand() % coluna)+1; //sorteia uma posição na coluna
        if (matriz[pLinha][pColuna] != -1) { //se a posição não abrigar uma bomba, ela se torna uma
            matriz[pLinha][pColuna] = -1;
            bombas++;
        }
    }
}


/*função que conta a quantidade de bombas que existem ao redor de uma coordenada
Recebe linha, coluna, tamanho e ponteiro de matriz como parâmetros e retorna a quantidade de bombas 
ao redor da posição determinada a partir de uma variável contadora*/
int quantidadeBombasRedor(int linha, int coluna, int tamanho, int** matriz){
    int qtd = 0;
    
    //diagonal superior esquerda
    if(podeCoordenada(linha - 1, coluna - 1, tamanho) && (matriz[linha-1][coluna-1] == -1)){
        qtd++;
    }
    //acima
    if(podeCoordenada(linha - 1, coluna, tamanho) && (matriz[linha - 1][coluna] == -1)){
        qtd++;
    }
    //diagonal superior direita
    if(podeCoordenada(linha - 1, coluna + 1, tamanho) && (matriz[linha-1][coluna+1] == -1)){
        qtd++;
    }
    //esquerda
    if(podeCoordenada(linha, coluna - 1, tamanho) && (matriz[linha][coluna-1] == -1)){
        qtd++;
    }
    //direita
    if(podeCoordenada(linha, coluna + 1, tamanho) && (matriz[linha][coluna+1] == -1)){
        qtd++;
    }
    //diagonal inferior esquerda
    if(podeCoordenada(linha + 1, coluna - 1, tamanho) && (matriz[linha+1][coluna-1] == -1)){
        qtd++;
    }
    //abaixo
    if(podeCoordenada(linha + 1, coluna, tamanho) && (matriz[linha+1][coluna] == -1)){
        qtd++;
    }
    //diagonal inferior direira
    if(podeCoordenada(linha + 1, coluna + 1, tamanho) && (matriz[linha+1][coluna+1] == -1)){
        qtd++;
    }

    return qtd;
}


/*função que seta a quantidade de bombas ao redor de uma determinada posição usando a função 
quantidadeBombasRedor
Recebe linha, coluna, tamanho e ponteiro de matriz como parâmetros e aloca o número de bombas em volta 
da coordenada na posição definida*/
void bombasRedor(int linha, int coluna, int tamanho, int** matriz){
    for(int i = 1; i <= linha; i++){
        for(int j = 1; j <= coluna; j++){
            if(matriz[i][j] != -1){
            matriz[i][j] = quantidadeBombasRedor(i, j, tamanho, matriz);
            }
        }
    }
}

/*função que checa de uma célula já foi aberta ou não
Recebe ponteiro de matriz, linha e coluna como parâmetros e caso a posição já tenha sido aberta, retorna
1, se estiver fechada, retorna 0*/
int coordenadaUsada(int** matriz, int linha, int coluna){
    int aberta = 0; //flag

    for(int i = 1; i <= linha; i++){
        for(int j = 1; j <= coluna; j++){
            if(matriz[i][j] == 'x'){
                aberta = 0; //fechada
            }
            else{
                aberta = 1; //aberta
            }
        }
    }

    return aberta;
}

/*função que abre células vazias (de valor "0") até que encontra uma célula com valor maior que 0
Recebe como parâmetros matriz de char, matriz de inteiros, linha, coluna e tamanho e abre as células de
forma recursiva usando flood fill*/
void abrindoVazio(char** matriz, int** mat, int linha, int coluna, int tamanho){
    if(podeCoordenada(linha, coluna, tamanho) == 0){ //checa de a coordenada é valida
        return;
    }

    if(matriz[linha][coluna] != 'x'){ //checa se a coordenada já foi aberta
        return;
    }

    if(mat[linha][coluna] == -1){ //se a coordenada for uma bomba, recebe -1
        matriz[linha][coluna] = -1;
        return;
    }

    if(mat[linha][coluna] == 0){ //se a coordenada for vaiza recebe 0
        matriz[linha][coluna] = '0';
    }
    else{
        matriz[linha][coluna] = '0' + mat[linha][coluna]; //se não for vazia recebe o valor de bombas ao redor
        return;
    }

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i != 0 || j != 0) {
                abrindoVazio(matriz, mat, linha+i, coluna+j, tamanho); //chamada recursiva da função
            }
        }
    }

}

/*função que checa se a coordenada do jogador é ou não uma bomba
Recebe ponteiro de matriz de inteiros, ponteiro de matriz de char, linha e coluna como parâmetros e
retorna uma flag, que, caso a coordenada seja uma bomba, recebe 1, se não for bomba, recebe 0*/
int vitoriaOuDerrota(int** mat, char** matriz, int linha, int coluna, int tamanho){
    int ser = 0; //flag
    if(mat[linha][coluna] == -1){
        ser = 1; //posição é uma bomba
    }
    else if(mat[linha][coluna] == 0){
        abrindoVazio(matriz, mat, linha, coluna, tamanho);
    }
    else{
        matriz[linha][coluna] = '0' + mat[linha][coluna]; //posição não é uma bomba e mostra a quantidade de bombas em volta
    }
    return ser;
}

/*função que recebe as coordenadas do jogador
Recebe ponteiro de matriz de char, ponteiro de matriz de inteiros, linha, coluna, quantidade de bombas
e tamanho como parâmetros
essa função recebe as coordenadas do jogador, checa se elas são válidas, checa se ela jão foi aberta, e 
checa se ela é uma bomba. Caso não seja bomba, o jogo continua, caso seja, o jogo acaba.
quando o jogo acaba, se o usuário venceu é impressa a mensagem "parabens voce eh fera", caso ele tenha perdido,
a mensagem é "game over!". Ambas seguidas da matriz de inteiros*/
void receberCoordenadasJogador(char** matriz, int** mat, int linha, int coluna, int qtdBombas, int tamanho){
    int coodL, coodC, perdeu = 0;
    int celulasPossiveis = (linha * coluna) - qtdBombas;
    int celulasAbertas = 0;

    do{
        do{
            printf("\ndigite as coordenadas que deseja checar:\n");
            scanf("%d, %d", &coodL, &coodC);

            if (podeCoordenada(coodL, coodC, tamanho) == 0) {
                printf("coordenada invalida!\n");
                continue;
            }
            if(matriz[coodL][coodC] != 'x'){
                printf("coordenada ja aberta!\n");
                continue;
            }
            if (vitoriaOuDerrota(mat, matriz, coodL, coodC, tamanho) == 1) {
                perdeu = 1;
                break;
            }
            else{
                celulasAbertas++;
            }
            imprimindoMatrizInicial(tamanho, matriz); // imprime o campo minado atualizado
        }while(celulasAbertas != celulasPossiveis); //enquanto o usuário não tiver aberto todas as células
        bombasRedor(coodL, coodC, tamanho, mat); // imprime o campo minado atualizado
    }while(celulasAbertas != celulasPossiveis && perdeu == 0); //enquanto o usuario nao tiver perdido

    if(perdeu == 1){
        printf("\n");
        printf("game over!\n");
        printf("\n");
        imprimindoMatrizValores(tamanho, mat);
    }
    else{
        printf("\n");
        printf("parabens, voce eh fera\n");
        printf("\n");
        imprimindoMatrizValores(tamanho, mat);
    }
}
int main(void){
    char dificuldade[20];
    int linha, coluna, tamanho, qtdBombas, **matriz;
    char** campo;

    //pede a entrada da dificuldade que o usuario deseja
    printf("escolha a dificuldade: (facil, medio ou dificil)\n");
    scanf("%s", dificuldade);

    //relaciona a entrada incial do usuario com a dificuldade pre determinada do jogo
    if(strcmp(dificuldade, "facil") == 0){
     linha = 10;
     coluna = 10;
     tamanho = 10;
     qtdBombas = 15;
    }
    else if(strcmp(dificuldade, "medio") == 0){
     linha = 20;
     coluna = 20;
     tamanho = 20;
     qtdBombas = 60;
    }
    else if(strcmp(dificuldade, "dificil") == 0){
     linha = 30;
     coluna = 30;
     tamanho = 30;
     qtdBombas = 135;
    }

    matriz = criandoMatriz(linha, coluna); //cria a matriz de inteiros
    campo = matrizInicial(linha, coluna); //cria a matriz de char

    sorteandoPosicao(matriz, qtdBombas, linha, coluna); //sortea a posição das bombas
    bombasRedor(linha, coluna, tamanho, matriz); //seta quantas bombas tem ao redor da coordenada
    imprimindoMatrizInicial(tamanho, campo); //imprime a matriz que aparece para o usuário
    receberCoordenadasJogador(campo, matriz, linha, coluna, qtdBombas, tamanho); //recebe as coordenadas do jogador


    liberarMatrizInt(matriz, tamanho); //libera memoria da matriz de inteiros
    liberarMatrizChar(campo, tamanho); //libera memoria da matriz de char

    return 0;
}
