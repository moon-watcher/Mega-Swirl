#ifndef BMP_H
#define BMP_H

#define BMP_ACCEPTABLE_HEADER 0x424D
#define BMP_FILE_HEADER_SIZE 14

#include <genesis.h>

typedef struct {
	u16 magicNumber;
	u32 bmpSize;
	u16 reserved1;
	u16 reserved2;
	u32 bmpImageAddr;
	
	u32 dibHeaderSize;
	s32 width;
	s32 height;
	u16 colorPlanes; //must be 1
	u16 bpp;
	u32 compressionMethod;
	u32 imageSize;
	u32 hResPpm;
	u32 vResPpm;
	u32 colourCount;
	u32 importantColourCount;
} BMPHeader;

typedef struct {
	u32* tiles;
	u16 palette[16];
	u16 size; //shall be a multiple of 8 (8 is one 8x8 tile)
} vdpBitmap;

vdpBitmap renderRLEtoRAM(u8 bmpFile[]);

#endif // BMP_H
