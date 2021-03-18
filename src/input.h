#ifndef _INPUT_H_
#define _INPUT_H_

#include "helper.h"


extern unsigned short input_cur;
extern unsigned short input_prev;

typedef struct UserInput_t {
	int prevRank;
	int prevFile;
	int rank;
	int file;
	int select;
} UserInput_t;


#define REG_KEYINPUT  (* (volatile unsigned short*) 0x4000130)

#define KEY_A        0x0001
#define KEY_B        0x0002
#define KEY_SELECT   0x0004
#define KEY_START    0x0008
#define KEY_RIGHT    0x0010
#define KEY_LEFT     0x0020
#define KEY_UP       0x0040
#define KEY_DOWN     0x0080
#define KEY_R        0x0100
#define KEY_L        0x0200

#define KEY_MASK     0xFC00

void KeyPoll(void);
unsigned short wasKeyPressed(unsigned short key_code);
unsigned short wasKeyReleased(unsigned short key_code);
unsigned short getKeyState(unsigned short key_code);
UserInput_t getUserInput(void);
int MoveSquare(unsigned short pressed, int *file, int *rank);
int initSquare(int file, int rank);
int restoreSquare(int file, int rank);

#endif