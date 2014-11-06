#include <bitmap.h>

/**
 * Create an Image from the given file  
 */
ImageAsset getImage(u8 file[]) {
	ImageAsset* bitmap = MEM_alloc( sizeof(ImageAsset) );
	for(int i = 0; i != 16; i++) {
		bitmap->palette[i] = 0;
	}
	bitmap->size = -1;

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
