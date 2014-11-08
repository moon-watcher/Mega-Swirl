#ifndef IMAGEASSET
#define IMAGEASSET

#define GENESIS_IMAGE_ASSET 	0xB16D1CC5
#define	PALETTE_OFFSET		0xB		
#define	IMAGE_OFFSET		0x2B

#include <types.h>
#include <vdp.h>
#include <memory.h>
#include <vdp_tile.h>
#include <debug.h>

typedef struct {
	u32 magicNumber;
	u8 compressionOptions;
	u8 xSegments;
	u8 ySegments;
	u32 metadataLocation;
} ImageAssetHeader;

typedef struct {
	u8 xTiles;
	u8 yTiles;
	u8 spriteOrder;
	
	u32* tiles;
	u16* palette;
} ImageAsset;

ImageAsset* getImage(u8 file[]);

#endif
