#include <debug.h>

/**
 * Draw debug text in hex to the screen 
 */
void printHex(u32 hex, u8 length) {
	char str[length];
	intToHex(hex, str, length);
	VDP_drawText(str, 0, 0);
}
