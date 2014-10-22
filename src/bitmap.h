#ifndef BMPSWIRL
#define BMPSWIRL

#define BMP_ACCEPTABLE_HEADER 0x424D
#define BMP_FILE_HEADER_SIZE 14

#define ROL(x, y, bitwidth) ((x) << (y))|((x) >> ((bitwidth) - (y)))
#define ROR(x, y, bitwidth) ((x) >> (y))|((x) << ((bitwidth) - (y)))

#include <types.h>
#include <vdp.h>
#include <memory.h>
#include <vdp_tile.h>

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
u8* decompressScanline(u16* compressedScanline, u16 size, s32 horizRes);
s32 roundUp(s32 numToRound, s32 multiple);

#endif // BMP_H
