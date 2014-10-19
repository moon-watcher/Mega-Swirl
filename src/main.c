/**************************************************************
 * Main                                                       *
 *                                                            *
 * Sega Swirl is (c) Sega Enterprises Ltd and does not        *
 * endorse or contribute to this game in any way.             *
 * This project may not be forked without attribution to the  *
 * original author(s).                                        *
 **************************************************************
 */
#include <genesis.h>
#include <audio_ts.h>
#include <swirl_assets.h>
#include <globals.h>
#include <custrand.h>
#include <swirl_types.h>
#include <handlers.h>
#include <board.h>
#include <titlescreen.h>

void joyHandler(u16 joy, u16 changed, u16 state);
void titleHandler(u16 joy, u16 changed, u16 state);
void initBoard();
void drawBoard();
void recursiveFloodSelect(int x, int y, int ch, int selbit);
int recursiveDelete(int x, int y, int type);
void applyGravity();
void applyLeftShift();
void titleScreen();
void unselectEverything();

struct swirl board[BOARD_Y][BOARD_X];
struct ls lastselected;
int waitflag = FALSE;
u16 randbase;
int selected = FALSE;
int score = 0;
SpriteDef cursor;

int main(void) {
	titleScreen();
	initBoard();
	drawBoard();
	VDP_fillTileMapRectInc(VDP_PLAN_A, TILE_ATTR_FULL(PAL3, PRIORITY_LOW, FALSE, FALSE, TILE_USERINDEX + 20), 32, 0, 5, 3);
	while(1) {
		VDP_waitVSync();
	}
	return 0;
}
