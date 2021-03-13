typedef struct board{
    int board[64];
    int gamestate;
}board;

int front(int step,int pos);
int back(int step,int pos);

int left(int step,int pos);
int right(int step,int pos);


int search(board board,int piece);

int win(board board);