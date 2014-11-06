#ifndef IMAGEASSET
#define IMAGEASSET

#define GENESIS_IMAGE_ASSET 	0xB16D1CC5

#include <types.h>
#include <vdp.h>
#include <memory.h>
#include <vdp_tile.h>

typedef struct {
	u32 magicNumber;
} ImageAssetHeader;

typedef struct {
	u8* tiles;
	u16 palette[16];
	u16 size; //shall be a multiple of 8 (8 is one 8x8 tile)
} ImageAsset;

ImageAsset getImage(u8 file[]);
u8 getNibble(u8* array, u16 index);
void setNibble(u8* array, u16 index, u8 value);

#endif
