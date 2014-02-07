#include "bmp.h"

typedef struct {
	u16 header;
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
	u8 red;
	u8 green;
	u8 blue;
	u8 alpha;
} palEntry;

void renderRLEtoRAM(u32 bmpFile[], u32 result[]) {
	
}
