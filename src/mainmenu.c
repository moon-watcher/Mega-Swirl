#include <mainmenu.h>

void mainMenu() {
	VDP_clearPlan(APLAN, FALSE);
	VDP_resetSprites();
	VDP_updateSprites();
	
	ImageAsset* optionTiles = getImage(dialog_tiles);
	VDP_setPalette(PAL2, optionTiles->palette);
	VDP_loadTileData(optionTiles->tiles, TILE_USERINDEX + 55, (optionTiles->xTiles * optionTiles->yTiles), TRUE);
	MEM_free( optionTiles );
	
	drawDialog( 2, 2, 20, 24 );
	
	VDP_drawText( "Main Menu", 7, 4 );
	VDP_drawText( "1P Game", 7, 7 );
	VDP_drawText( "Head 2 Head", 7, 9 );
	VDP_drawText( "Online Play", 7, 11 );
	VDP_drawText( "Options", 7, 13 );
	
	VDP_setTileMapXY(APLAN, TILE_ATTR_FULL(PAL2, PRIORITY_LOW, FALSE, FALSE, ARROW), 5, 7);
	
	while(TRUE);
	
	// Setup some things before main gameplay
	
	VDP_setPalette(PAL2, sel_pal);
	
	ImageAsset* test = getImage(swlspace);	
	VDP_setPalette(PAL0, test->palette);
	VDP_loadTileData(test->tiles, TILE_USERINDEX + 59, (test->xTiles * test->yTiles), TRUE);
	VDP_fillTileMapRectInc(VDP_PLAN_B, TILE_ATTR_FULL(PAL0, PRIORITY_LOW, FALSE, FALSE, TILE_USERINDEX + 59), 0, 0, test->xTiles, test->yTiles);
	MEM_free( test );
	
	JOY_setEventHandler(joyHandler);
	SND_stopPlay_VGM();
}
