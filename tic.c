/* Copyright (C) 2019, Hrafnkell Sigurðarson <hrs70@hi.is> */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define BOARDSIZE 3
#define ARRAYBOUND BOARDSIZE-1
#define SPACING "        "
void parsenum(int input);

bool board[BOARDSIZE][BOARDSIZE];
bool occupied[BOARDSIZE][BOARDSIZE];
bool turn = true;
// TODO: Remove printf, replace with game functions

void print_state() {
    for(int i = 0; i < BOARDSIZE; i++) {
        printf(SPACING);
        for(int j = 0; j < BOARDSIZE; j++) {
            occupied[i][j] == false 
                ? printf("_ ") 
                : printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

bool full(){
    for (int i = 0; i < BOARDSIZE; i++) {
        for (int j = 0; j < BOARDSIZE; j++) {
            if(!occupied[i][j]){ return false; }
        }    
    }
    return true;
}

void gameover(int player){
    printf("Game over \n");
    if(player == -1) {
        printf("Stalemate!\n");
    }else{
        printf("Player %d wins! \n", player);
    }
    print_state();
    exit(EXIT_SUCCESS);
}

void checkwin(){
    bool brdV, brdH;
    bool brdLR = board[0][0];
    bool brdRL = board[ARRAYBOUND][0];    
    int RL = 0;
    int LR = 0;

    for(int i = 0; i < BOARDSIZE; i++) {
        brdV = board[i][0];
        brdH = board[0][i];

        // Horizontal 
        for(int h = 0; h < BOARDSIZE; h++) {
            if(!occupied[i][h] || brdV != board[i][h]){
                break;
            }else{
                brdV = board[i][h];
            }

            if(h == ARRAYBOUND){
                printf("HORIZONTAL: %d\n", i);
                gameover(turn);
            }
        }
        // Vertical 
        for(int v = 0; v < BOARDSIZE; v++) {
            if(!occupied[v][i] || brdH != board[v][i]){
                break;
            }else{
                brdH = board[v][i];
            }

            if(v == ARRAYBOUND){
                printf("VERTICAL: %d\n", i);
                gameover(turn);
            }
        }

        //Diagonal
        if(occupied[i][i] && (brdLR == board[i][i])){
            brdLR = board[i][i];
            LR++;
        }

        if(occupied[i][ARRAYBOUND-i] && (brdRL == board[i][ARRAYBOUND-i])){
            brdRL = board[i][ARRAYBOUND-i];
            RL++;
        }

        if(LR == BOARDSIZE || RL == BOARDSIZE){
            printf("DIAGONAL \n");
            gameover(turn);
        }
    }
}


void apply(int x,int y) {
    if(occupied[y][x]) return;
    board[y][x] = turn;
    occupied[y][x] = true;
    checkwin();
    if(full()) gameover(-1);
    turn = !turn;
}

void readnum(){
    char line[10];
    int num = 0;
    while(fgets(line, sizeof(line), stdin) != NULL){
        if(sscanf(line, "%1d", &num) != 1){
            printf("Invalid input, please try again! \n");
            continue;
        }
        parsenum(num-1);
        printf("Player %d 's turn:", turn);
    }
}

void intro(){
    printf("Tic Tac Toe - in binary  with boolean arrays.\n"
           "The game is to be played using the numpad\n"
           "which represents positions on the game board,\n"
           "    press enter after each move... \n"
            );
}

void parsenum(int input){
    if(input < 0 || input > BOARDSIZE*BOARDSIZE) return;
    int y = ARRAYBOUND-(input/BOARDSIZE);
    int x = (input%BOARDSIZE);
    apply(x,y);
    print_state();
}

int main(int argc, const char *argv[]) {
    intro();
    print_state();
    readnum();
    return 0;
}
