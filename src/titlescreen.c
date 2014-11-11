#include <titlescreen.h>

void titleScreen() {
	snowflake snowflakes[TITLE_SCREEN_SNOWFLAKES];
	SpriteDef sfdefs[TITLE_SCREEN_SNOWFLAKES];
	
	VDP_resetScreen();
	VDP_resetSprites();

	// Load Swirls
	VDP_loadTileData(swirls, TILE_USERINDEX, 20, TRUE);
	VDP_loadTileData(title_screen, TILE_USERINDEX + 20, 15, TRUE);
	VDP_loadTileData(swirl_spr, TILE_USERINDEX + 35, 20, TRUE);
	
	VDP_setPalette(PAL1, swirl_pal);
	VDP_setPalette(PAL2, sel_pal);
	VDP_setPalette(PAL3, ts_pal);
	
	JOY_init();
	JOY_setEventHandler(titleHandler);
	
	ImageAsset* title = getImage(titlbg);
	VDP_setPalette(PAL0, title->palette);
	VDP_loadTileData(title->tiles, TILE_USERINDEX + 59, (title->xTiles * title->yTiles), TRUE);
	VDP_fillTileMapRectInc(VDP_PLAN_B, TILE_ATTR_FULL(PAL0, PRIORITY_LOW, FALSE, FALSE, TILE_USERINDEX + 59), 0, 0, title->xTiles, title->yTiles);
	MEM_free( title );
	
	VDP_fillTileMapRectInc(VDP_PLAN_A, TILE_ATTR_FULL(PAL3, PRIORITY_LOW, FALSE, FALSE, TILE_USERINDEX + 20), 18, 3, 5, 3);
	VDP_drawText("Mega Swirl",  1, 7);
	VDP_drawText("Testing Demo", 1, 8);
	VDP_drawText(VERSION_STRING, 1, 9);
	
	VDP_drawText("Music from Deflemask by", 1, 11);
	VDP_drawText("Delek", 1, 12);
	
	VDP_drawText("Featuring artwork by", 1, 14);
	VDP_drawText("Radioactivemantaray", 1, 15);
	
	VDP_drawText("- Press Start to Play -", 1, 21);
	VDP_drawText(BUILD_DATE, 1, 24);

	u8 selected_swirl;
	for(int i = 0; i != TITLE_SCREEN_SNOWFLAKES; i++) {
		snowflakes[i].startedAt = 
		snowflakes[i].startDelay =
		snowflakes[i].fallRate =
		snowflakes[i].swirltype =
		0;
		
		sfdefs[i].posx =
		sfdefs[i].posy =
		sfdefs[i].tile_attr =
		sfdefs[i].size =
		sfdefs[i].link =
		0;
		
		selected_swirl = (custrand() % 4);
		snowflakes[i].swirltype = selected_swirl; // Select one of four swirl types
		snowflakes[i].startDelay = ((custrand() % 3000) + 1) / 300; // Select between a 1-10 second delay (300 ticks per second)
		snowflakes[i].startedAt = getTick(); // Time when this snowflake was created 
		snowflakes[i].fallRate = (custrand() % 2) + 1; // Select how fast this snowflake should fall to the bottom of the screen
		sfdefs[i].posx = (custrand() % 320); // Select X position for this swirl
		sfdefs[i].posy = -16; // Start it off screen
		
		sfdefs[i].size = SPRITE_SIZE(2, 2);
		sfdefs[i].tile_attr = TILE_ATTR_FULL(PAL1, PRIORITY_HIGH, FALSE, FALSE, TILE_USERINDEX + 35 + (4 * selected_swirl)); // This will need to be changed as we need tiles arranged for sprites
		if(i != 0) {
			sfdefs[i - 1].link = i;
		}
	}
	VDP_setSpritesDirect(0, sfdefs, TITLE_SCREEN_SNOWFLAKES);

	Z80_loadDriver(Z80_DRIVER_VGM, 1);
	Z80_requestBus(1);
	YM2612_enableDAC();
	Z80_releaseBus();
	SND_startPlay_VGM(muz_title);

	while (waitflag == FALSE) {
		
		for(int i = 0; i != TITLE_SCREEN_SNOWFLAKES; i++) {
			
			if(getTick() - snowflakes[i].startedAt >= snowflakes[i].startDelay) {
				
				if(sfdefs[i].posy != 240) {
					sfdefs[i].posy = sfdefs[i].posy + snowflakes[i].fallRate;
				} else {
					selected_swirl = (custrand() % 4);
					snowflakes[i].startDelay = ((custrand() % 3000) + 1) / 300;
					snowflakes[i].startedAt = getTick();
					snowflakes[i].fallRate = (custrand() % 2) + 1;
					sfdefs[i].posx = (custrand() % 320);
					sfdefs[i].posy = -16;
				}
				
			}
			
			VDP_setSpritesDirect(0, sfdefs, TITLE_SCREEN_SNOWFLAKES);
		}
		
	}

	waitflag = FALSE;
	srand(GET_HVCOUNTER);
}
