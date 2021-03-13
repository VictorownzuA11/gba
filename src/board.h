typedef struct board{
    int board[64];
    int gamestate;
}gameboard;
enum pieces_num {
	WHITE=1,	// 0
	BLACK=-1,	// 1
	wPAWN=2,	// 2
	wBISHOP=3,	// 3
	wKNIGHT=4,	// 4
	wROOK=5,	// 5
	wQUEEN=6,	// 6
	wKING=7,	// 7
	bPAWN=-2,	// 2
	bBISHOP=-3,	// 3
	bKNIGHT=-4,	// 4
	bROOK=-5,	// 5
	bQUEEN=-6,	// 6
	bKING=-7	// 7
};
int front(int step,int pos);
int back(int step,int pos);

int left(int step,int pos);
int right(int step,int pos);


int search(board board,int piece);

int win(board board);