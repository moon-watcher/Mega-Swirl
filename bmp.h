#ifndef BMP_H
#define BMP_H

#include <genesis.h>

void renderRLEtoRAM(u32 bmpFile[], u32 result[]);
void renderRLEtoVDP(u32 bmpFile[]);

#endif // BMP_H
