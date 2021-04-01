#ifndef _HELPER_H_
#define _HELPER_H_

#define WHITE 0x7FFF
#define BLACK 0x0

extern volatile unsigned char *ioram;
extern volatile unsigned short *reg_vcount;
extern volatile unsigned short *reg_keyinput;
extern volatile unsigned short *vram;
extern volatile unsigned short *oam;

extern const int bpawnp[];
extern const int brookp[];
extern const int bknightp[];
extern const int bbishopp[];
extern const int bqueenp[];
extern const int bkingp[];

void VidSync(void);

#endif