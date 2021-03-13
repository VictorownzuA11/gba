#include "board.h"



int search(board board,int piece){
    int i;
    int cnt=0;
    for(i=0;i<64;i++){
        if(board.board[i]==piece){
            cnt++;
        }
    }
    return cnt;
}

int win(board board){
    if(search(board,7)==0){
        return 1;//can't find wKing, black win
    }
    if(searc(board,-7)==0){
        return -1;//can't find bKing, white win
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


int get_possible_moves(board board,int piece){
    
}