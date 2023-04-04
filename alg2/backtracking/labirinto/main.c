#include <stdio.h>

#define N 4

void printSolution(int sol[N][N]){

    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++)
            printf(" %2d ", sol[x][y]);
        printf("\n");
    }
}

int isSafe(int maze[N][N], int x, int y){

    if(x>=0 && x<N && y>=0 && y<N && maze[x][y] == 1)
        return 1;
    else
        return 0;
}

int solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N]){

    if (x == N-1 && y == N-1 && maze[x][y] == 1){ // caso base
        sol[x][y] = 1;
        return 1;
    }
    if (isSafe(maze, x, y)){ // verifica se maze[x][y] é válido
        if(sol[x][y] == 1) // verifica se a posição (x, y) faz parte da solução
            return 0;
        sol[x][y] = 1; // coloca a posição (x, y) como parte da solução

        if (solveMazeUtil(maze, y+1 , y, sol) == 1) // mover para a direita
            return 1;
        if (solveMazeUtil(maze, x+1 , y, sol) == 1) // mover para baixo
            return 1;
        sol[x][y] = 0; // backtracking
        return 0;
    }
    return 0;
}

int solveMaze(int maze[N][N]){

    int sol[N][N];
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
            sol[x][y] = 0;

    if (solveMazeUtil(maze, 0, 0, sol) == 0){
        printf("Solucao nao existe\n");
        return 0; // false
    }
    printSolution(sol);
    return 1; // true
}

int main(void){

    //0: paredes
    int maze[N][N] = {{1, 0, 0, 0},
                      {1, 1, 0, 1},
                      {1, 1, 0, 1},
                      {1, 1, 0, 1}};
    solveMaze(maze);

    return 0;
}