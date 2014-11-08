#include <bitmap.h>

/**
 * Create an Image from the given file  
 */
ImageAsset* getImage(u8 file[]) {
	ImageAsset* bitmap = MEM_alloc( sizeof(ImageAsset) );
	ImageAssetHeader* header = (ImageAssetHeader*) file;
	
	if( header->magicNumber != GENESIS_IMAGE_ASSET ) {
		MEM_free( bitmap );
		return bitmap;
	}
	
	// TODO: Compression Options (nibble methods)
	
	bitmap->xTiles = header->xSegments;
	bitmap->yTiles = header->ySegments;
	
	bitmap->palette = (u16*)(file + PALETTE_OFFSET);

	printHex(*(u32*)(file + 1), 4);
	
	while(TRUE);
	
	return bitmap;
}
