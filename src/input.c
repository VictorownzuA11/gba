#include "input.h"

unsigned short input_cur = 0x03FF;
unsigned short input_prev = 0x03FF;


UserInput_t getUserInput(void) {
    // output an int array of size four
    // {origin file, origin rank, target cell, target rank}
    const unsigned short keys[] = {KEY_A, KEY_B, KEY_RIGHT, KEY_LEFT,
                                KEY_UP, KEY_DOWN};
    unsigned short pressed;
    UserInput_t UserInput;
    int out[4];
    int ori_selected = 0;
    int file = 0;
    int rank = 0;

    // initialize highlighted cell (top right)
    initSquare(file, rank);
    KeyPoll();

    while(1){
        KeyPoll();
        pressed = 0x0000;
        //check for key press
        for (int i=0; i<6; i++){
            if (wasKeyPressed(keys[i])){
                while (!wasKeyReleased(keys[i])){
                    KeyPoll();
                }
                pressed = keys[i];
                break;
            }
        }
        
        if (pressed == KEY_A){
            // select cell
            out[ori_selected * 2] = file;
            out[ori_selected * 2 + 1] = rank;

            ori_selected++;
        }
        else if(pressed == KEY_B){
            // cancel previous selection
            if(ori_selected > 0){
                ori_selected--;
            }
        }
        else{
            //Move current highlighted square according to pressed
            MoveSquare(pressed, &file, &rank);
        }
        if (ori_selected == 2) break;
    }
    // restore last selected cell
    restoreSquare(file, rank);
    return UserInput;
}

int MoveSquare(unsigned short pressed, int *file, int *rank){
    int x,y;

    if (pressed == KEY_RIGHT){
        //Move highlighted square right
        for (x = 0; x < 20; x++) {
            for (y = 0; y < 20; y++) {
                vram[(*file)*20 + x + ((*rank)*20 + y)*240] -= 0x0500;
            }
        }
        if (*file < 7){
            *file += 1;
        }
        for (x = 0; x < 20; x++) {
            for (y = 0; y < 20; y++) {
                vram[(*file)*20 + x + ((*rank)*20 + y)*240] += 0x0500;
            }
        }
    }
    else if (pressed == KEY_LEFT){
        //Move highlighted square left
        for (x = 0; x < 20; x++) {
            for (y = 0; y < 20; y++) {
                vram[(*file)*20 + x + ((*rank)*20 + y)*240] -= 0x0500;
            }
        }
        if (*file > 0){
            *file -= 1;
        }
        for (x = 0; x < 20; x++) {
            for (y = 0; y < 20; y++) {
                vram[(*file)*20 + x + ((*rank)*20 + y)*240] += 0x0500;
            }
        }
    }
    else if (pressed == KEY_DOWN){
        //Move highlighted square up
        for (x = 0; x < 20; x++) {
            for (y = 0; y < 20; y++) {
                vram[(*file)*20 + x + ((*rank)*20 + y)*240] -= 0x0500;
            }
        }
        if (*rank < 7){
            *rank += 1;
        }
        for (x = 0; x < 20; x++) {
            for (y = 0; y < 20; y++) {
                vram[(*file)*20 + x + ((*rank)*20 + y)*240] += 0x0500;
            }
        }
    }
    else if (pressed == KEY_UP){
        //Move highlighted square down
        for (x = 0; x < 20; x++) {
            for (y = 0; y < 20; y++) {
                vram[(*file)*20 + x + ((*rank)*20 + y)*240] -= 0x0500;
            }
        }
        if (*rank > 0){
            *rank -= 1;
        }
        for (x = 0; x < 20; x++) {
            for (y = 0; y < 20; y++) {
                vram[(*file)*20 + x + ((*rank)*20 + y)*240] += 0x0500;
            }
        }
    }
    else{
        //Invalid input
        return 0;
    }
    return 1;
}

int restoreSquare(int file, int rank){
    int x,y;
    for (x = 0; x < 20; x++) {
        for (y = 0; y < 20; y++) {
            vram[(file)*20 + x + ((rank)*20 + y)*240] -= 0x0500;
        }
    }
    return 1;
}

int initSquare(int file, int rank){
    int x,y;
    for (x = 0; x < 20; x++) {
        for (y = 0; y < 20; y++) {
            vram[(file)*20 + x + ((rank)*20 + y)*240] += 0x0500;
        }
    }
    return 1;
}

void KeyPoll(void) {
    input_prev = input_cur;
    input_cur = REG_KEYINPUT | KEY_MASK;
}

unsigned short wasKeyPressed(unsigned short key_code) {
    return (key_code) & (~input_cur & input_prev);
}

unsigned short wasKeyReleased(unsigned short key_code) {
    return  (key_code) & (input_cur & ~input_prev);
}

unsigned short getKeyState(unsigned short key_code) {
    return !(key_code & (input_cur) );
}