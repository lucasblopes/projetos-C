#include<stdio.h>
#define N 5

void printSolution(int sol[N][N]){

    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++)
            printf(" %2d ", sol[x][y]);
        printf("\n");
    }
}

int isSafe(int x, int y, int sol[N][N]){

    return (x >= 0 && x < N && y >= 0 && y < N && sol[x][y] == -1);
}

int solveKTUtil(int x, int y, int movei, int sol[N][N], int xMove[N], int yMove[N]){

    if (movei == N * N) // caso base: cavalo visitou todas as casas
        return 1;
        
    for (int k = 0; k < 8; k++){ // pega os movimentos certos do cavalo
        int next_x = x + xMove[k];
        int next_y = y + yMove[k];

        if (isSafe(next_x, next_y, sol)){ // analisa se o movimento do cavalo é seguro
            sol[next_x][next_y] = movei;
            if (solveKTUtil(next_x, next_y, movei + 1, sol, xMove, yMove) == 1)
                return 1; // solução encontrada
            else // beco sem saída
                sol[next_x][next_y] = -1; // backtracking
        }
    }
    return 0;
}

void solveKT(){
    //inicializa a matriz com -1
    int sol[N][N];
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
            sol[x][y] = -1;

    //posicao inicial
    sol[0][0] = 0;
    //possibilidades de movimentacao para o cavalo
    int xMove[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int yMove[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    if (solveKTUtil(0, 0, 1, sol, xMove, yMove) == 1)
        printSolution(sol);
    else
        printf("Solucao nao existe");
}

int main(void){

    solveKT();

    return 0;
}