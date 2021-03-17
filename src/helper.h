#ifndef _HELPER_H_
#define _HELPER_H_


extern volatile unsigned char *ioram;
extern volatile unsigned short *reg_vcount;
extern volatile unsigned short *reg_keyinput;
extern volatile unsigned short *vram;
extern volatile unsigned short *oam;

void VidSync(void);

#endif