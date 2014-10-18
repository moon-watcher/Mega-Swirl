#include <board.h>

void recursiveFloodSelect(int x, int y, int ch, int selbit) {
	if (x == -1 || y == -1 || x == BOARD_X || y == BOARD_Y || board[y][x].id != ch || board[y][x].selected == selbit)
		return;

	board[y][x].selected = selbit;

	recursiveFloodSelect(x-1, y, ch, selbit);
	recursiveFloodSelect(x+1, y, ch, selbit);
	recursiveFloodSelect(x, y-1, ch, selbit);
	recursiveFloodSelect(x, y+1, ch, selbit);
}

int recursiveDelete(int x, int y, int type) {
	int toret = 0;
	if (x == -1 || y == -1 || x == BOARD_X || y == BOARD_Y || board[y][x].id != type || board[y][x].selected == FALSE)
		return 0;

	board[y][x].id = 0;
	board[y][x].selected = FALSE;
	toret = 1;

	toret+=recursiveDelete(x-1, y, type);
	toret+=recursiveDelete(x+1, y, type);
	toret+=recursiveDelete(x, y-1, type);
	toret+=recursiveDelete(x, y+1, type);
	return toret;
}

void applyGravity() {
	int x, y, ch, i;
	for(y = BOARD_Y-2; y >= 0; y--) {
		for (x = BOARD_X-1; x >= 0; x--) { //-2 because nothing needs to be brought down on the last row!
			i = y + 1;
			if (board[y][x].id != 0 && board[i][x].id == 0) {
				ch = board[y][x].id;
				while(i != BOARD_Y && board[i][x].id == 0) {
					board[i-1][x].id = 0;
					board[i-1][x].selected = 0;
					board[i][x].id = ch;
					i++;
				}
			}
		}
	}
}

void applyLeftShift() {
	int x, y, x2, y2, ch;
	int blanks = 0;
	y = BOARD_Y - 1;
	for (x = 0; x <= BOARD_X-2; x++) {
		if (board[y][x].id == 0) {
			blanks++;
			x2 = x + 1;
			if (board[y][x2].id != 0) {
				for (y2 = y; y2 >= 0; y2--) {
					ch = board[y2][x2].id;
					if (ch != 0) {
						board[y2][x2].id = 0;
						board[y2][x2].selected = 0;
						board[y2][x2 - blanks].id = ch;
					}
				}
			blanks = 0;
			x = 0;
			}
		}
	}
}

void drawBoard() {
	int x, y;
	char score_string[11];
	for (y = 0; y != BOARD_Y; y++) {
		for (x = 0; x != BOARD_X; x++) {
			if (board[y][x].id) {
				if (board[y][x].selected)
					VDP_fillTileMapRectInc(VDP_PLAN_A, TILE_ATTR_FULL(PAL2, PRIORITY_LOW, FALSE, FALSE, TILE_USERINDEX + (4 * board[y][x].id)), CUR(x), CUR(y), SWIRL_WIDTH, SWIRL_HEIGHT);
				else
					VDP_fillTileMapRectInc(VDP_PLAN_A, TILE_ATTR_FULL(PAL1, PRIORITY_LOW, FALSE, FALSE, TILE_USERINDEX + (4 * board[y][x].id)), CUR(x), CUR(y), SWIRL_WIDTH, SWIRL_HEIGHT);
			} else {
				VDP_clearTileMapRect(VDP_PLAN_A, CUR(x), CUR(y), SWIRL_WIDTH, SWIRL_HEIGHT);
			}
		}
	}
	VDP_drawText("Level 1", 31, 3);
	//VDP_drawText("Goals:", 32, 5);
	//VDP_drawText("0 / 0", 32, 6);
	VDP_drawText("Score:", 30, 26);
	intToStr((s32)score, score_string, 1);
	VDP_clearTileMapRect(VDP_PLAN_A, 30, 27, 10, 1);
	VDP_drawText(score_string, 30, 27);
	VDP_updateSprites();
}

void initBoard() {
	int x,y,c;
	for (y = 0; y != BOARD_Y; y++) {
		for (x = 0; x != BOARD_X; x++) {
			c = (custrand() % 4) + 1;
			board[y][x].id = c;
			board[y][x].selected = 0;
		}
	}
	VDP_resetSprites();
	cursor.posx = 0;
	cursor.posy = 0;
	cursor.size = SPRITE_SIZE(2, 2);
	cursor.tile_attr = TILE_ATTR_FULL(PAL1, PRIORITY_HIGH, FALSE, FALSE, TILE_USERINDEX);
	cursor.link = 0;
	VDP_setSpriteP(0, &cursor);
	VDP_updateSprites();
	
	SND_startPlay_VGM(muz_gameplay1);
}

void unselectEverything() {
	int x, y;
	for (y = 0; y != BOARD_Y; y++) {
		for (x = 0; x != BOARD_X; x++) {
			board[y][x].selected = FALSE;
		}
	}
}
