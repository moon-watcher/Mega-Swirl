#include <dialogs.h>

void drawDialog(u8 x, u8 y, u8 width, u8 height) {
	
	// PRIORITY_LOW is not visible in this file for some reason I can't figure out, 
	// so i just replaced it with its constant value.
	
	// Blank using palette for controls
	VDP_fillTileMapRect(APLAN, TILE_ATTR_FULL(PAL2, 0, FALSE, FALSE, 15), x, y, width, height);
	
	// Four corners
	VDP_setTileMapXY(APLAN, TILE_ATTR_FULL(PAL2, 0, FALSE, FALSE, CORNER), x, y);
	VDP_setTileMapXY(APLAN, TILE_ATTR_FULL(PAL2, 0, FALSE, FALSE, CORNER), x + width - 1, y);
	VDP_setTileMapXY(APLAN, TILE_ATTR_FULL(PAL2, 0, FALSE, FALSE, CORNER), x, y + height - 1);
	VDP_setTileMapXY(APLAN, TILE_ATTR_FULL(PAL2, 0, FALSE, FALSE, CORNER), x + width - 1, y + height - 1);
	
	// Bars across
	VDP_fillTileMapRect(APLAN, TILE_ATTR_FULL(PAL2, 0, FALSE, FALSE, HORIZ), x + 1, y, width - 2, 1);
	VDP_fillTileMapRect(APLAN, TILE_ATTR_FULL(PAL2, 0, FALSE, FALSE, HORIZ), x + 1, y + height - 1, width - 2, 1);
	
	// Bars down
	VDP_fillTileMapRect(APLAN, TILE_ATTR_FULL(PAL2, 0, FALSE, TRUE, VERT), x, y + 1, 1, height - 2);
	VDP_fillTileMapRect(APLAN, TILE_ATTR_FULL(PAL2, 0, FALSE, TRUE, VERT), x + width - 1, y + 1, 1, height - 2);
}
