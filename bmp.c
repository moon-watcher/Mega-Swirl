#include "bmp.h"

vdpBitmap renderRLEtoRAM(u8 bmpFile[]) {
	vdpBitmap* rv = MEM_alloc( sizeof(vdpBitmap) );
	rv->size = -1;
	
	BMPHeader* head = (BMPHeader*) bmpFile;
	//head.magicNumber = bmpFile[0] + (bmpFile[1] << 8);
	
	char arr[8]; //Arr!!!
	intToHex(head->bmpSize, arr, 8);
	
	VDP_drawText(arr, 0, 0);
	while(TRUE);
}
