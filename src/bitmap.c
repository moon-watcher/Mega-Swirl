#include <bitmap.h>

#define C_ALPHA 0
#define C_RED 1
#define C_GREEN 2
#define C_BLUE 3

#define SWAP_UINT16(x) (((x) >> 8) | ((x) << 8))
#define SWAP_UINT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))

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

	// Reference the bmpImage
	u16* bmpImage = (u16*)((u8*)bmpFile + SWAP_UINT32(head->bmpImageAddr));

	VDP_setPalette(PAL2, rv->palette);
}
