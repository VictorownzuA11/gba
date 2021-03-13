#include "board.h"
gameboard board;
int board_init(){
    int i;
    for(i=0;i<64;i++){
        board.board[i]=0;
    }
    board.gamestate=0;
}

int search(gameboard board,int piece){
    int i;
    int cnt=0;
    for(i=0;i<64;i++){
        if(board.board[i]==piece){
            cnt++;
        }
    }
    return cnt;
}

int win(gameboard board){
    if(search(board,wKING)==0){
        return BLACK;//can't find wKing, black win
    }
    if(searc(board,bKING)==0){
        return WHITE;//can't find bKing, white win
    }
    return 0;//game not over
}

int front(int step,int pos){
    if (step>8){
        return -1;
    }
    int ret=pos+8*step;
    if(ret>63){
        return -1;
    }
    return ret;

}
int back(int step,int pos){
    if (step>8){
        return -1;
    }
    int ret=pos-8*step;
    if(ret>63){
        return -1;
    }
    return ret;
}

int left(int step,int pos){
    if (step>8){
        return -1;
    }
    int ret=pos-step;
    if(ret%8>pos%8){
        return -1;
    }
    return ret;
}
int right(int step,int pos){
    if (step>8){
        return -1;
    }
    int ret=pos+step;
    if(ret%8>pos%8){
        return -1;
    }
    return ret;
}
int occup(gameboard board,int pos){
    if(board.board[pos]>0){
        return WHITE;//white occupy
    }
    if(board.board[pos]<0){
        return BLACK;//black occupy
    }
    return 0;//empty
}
int *get_possible_moves(gameboard board,int piece,int pos,int color){
    int possible_move[64];
    switch(piece){

        case 2:
        case-2:
            
    }
}