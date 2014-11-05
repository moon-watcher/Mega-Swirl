#include <bitmap.h>

#define C_ALPHA 0
#define C_RED 1
#define C_GREEN 2
#define C_BLUE 3

#define END_SCANLINE 0x0000
#define END_FILE	 0x0001

#define SWAP_UINT16(x) (((x) >> 8) | ((x) << 8))
#define SWAP_UINT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))

/**
 * Create a vdpBitmap from the given bmpFile  
 */
vdpBitmap renderRLEtoRAM(u8 bmpFile[]) {
	vdpBitmap* rv = MEM_alloc( sizeof(vdpBitmap) );
	for(int i = 0; i != 16; i++) {
		rv->palette[i] = 0;
	}
	rv->size = -1;
	
	BMPHeader* head = (BMPHeader*) bmpFile;
	
	// rv->size will be -1 when error condition is met
	// This is here for Mega Everdrive BMP-from-SD Loader implementation (to indicate error)
	if(head->magicNumber != BMP_ACCEPTABLE_HEADER)
		// deallocate and return null
		return *rv;
	
	// Perform pointer arithmetic at the byte level
	// Then at the longword level
	u32* bmpPalette = (u32*)((u8 *)bmpFile + BMP_FILE_HEADER_SIZE + SWAP_UINT32(head->dibHeaderSize));
	for(int colour = 0; colour != SWAP_UINT32(head->colourCount); colour++) {
		u32 paletteQuadruplet = SWAP_UINT32(bmpPalette[colour]);
		u8* components = (u8*)&paletteQuadruplet;
		// Convert bmpPalette colours to SEGA colours by taking the upper nibble of each component
		//componentMask[C_RED] = components[C_RED] >> 4;
		//componentMask[C_BLUE] = components[C_BLUE] >> 4;
		//componentMask[C_GREEN] = components[C_GREEN] >> 4;
		rv->palette[colour] = ( components[C_RED] >> 4 ) | ( components[C_BLUE] >> 4 ) << 8 | ( components[C_GREEN] >> 4 ) << 4;
	}
	
	//VDP_setPalette(PAL2, rv->palette);

	// Reference the bmpImage
	u16* bmpImage = (u16*)((u8*)bmpFile + SWAP_UINT32(head->bmpImageAddr));
	// careless
	u16 scanline = SWAP_UINT32(head->height) - 1;
	// careless
	rv->tiles = (u8*)MEM_alloc(sizeof(u8) * ((SWAP_UINT32(head->width) / 2) * (SWAP_UINT32(head->height) / 2)));
	
	u16* bmpPos = bmpImage;
	u8* tilesPos = rv->tiles;
	u16 doublet;
	while(TRUE) {
		doublet = bmpImage[bmpOffset];
		if(doublet == END_SCANLINE) {
			scanline--;
			bmpOffset++;
		} else if(doublet == END_FILE) {
			break;
		} else if(((doublet & 0xFF00) == 0x00) && ((doublet & 0x00FF) >= 0x03)) {
			// unencoded run
			//for(u16 i = 0; i != (doublet & 0x00FF); i++) {
				
			//}
			
		} else {
			// Standard encoded run (00 04+)
		}
		while(TRUE);
	}
}

// all u8 nibbles will be stored in the lower nibble of the byte (0x)
u8 getNibble(u8* array, u16 index) {
	// TODO: maybe optimise
	// number & 1 - odd
	if(index & 1) {
		// index needs to be subtracted by 1, then take the lower nibble
		return (array[index / 2] & 0x0F);
	} else {
		// use index as given. take the higher nibble
		return (array[index] & 0xF0) >> 4;
	}
}

// set a u8 nibble (lower nibble will be used)
void setNibble(u8* array, u16 index, u8 value) {
	if(index & 1) {
		array[index / 2] = ((array[index / 2] & 0xF0) | (value & 0x0F));
	} else {
		array[index] = ((array[index] & 0x0F) | (value << 4));
	}
}
