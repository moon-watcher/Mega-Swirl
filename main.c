/**************************************************************
 * Main                                                       *
 * Last Modified: 6/22/2013                                   *
 *                                                            *
 * Sega Swirl is (c) Sega Enterprises Ltd and does not        *
 * endorse or contribute to this game in any way.             *
 * This project may not be forked without attribution to the  *
 * original author(s).                                        *
 **************************************************************
 */
#include <genesis.h>
#include <swirl_assets.h>
#define BOARD_X 15
#define BOARD_Y 14
#define SWIRL_WIDTH 2
#define SWIRL_HEIGHT 2
#define FALSE 0
#define TRUE 1
#define PRIORITY_LOW 0
#define PRIORITY_HIGH 1
//#define USE_XORSHIFT

#define CUR(x) (x * 2)
#define SEL(x) (x / 16)

void joyHandler(u16 joy, u16 changed, u16 state);
void titleHandler(u16 joy, u16 changed, u16 state);
void initBoard();
void drawBoard();
void recursiveFloodSelect(int x, int y, int ch, int selbit);
int recursiveDelete(int x, int y, int type);
void applyGravity();
void applyLeftShift();
void titleScreen();
void srand(u16 seed);
u16 custrand();
void unselectEverything();

struct swirl {
	u8 id;
	u8 selected;
} board[BOARD_Y][BOARD_X];

struct ls {
	u8 x;
	u8 y;
} lastselected;

volatile int toggle = TRUE; //test var that will be killed
volatile int waitflag = FALSE;
volatile u16 randbase;
volatile int selected = FALSE;
volatile int trigger = FALSE;
int score = 0;
SpriteDef cursor;

int main(void) {
	titleScreen();
	initBoard();
	drawBoard();
	VDP_drawText("MEGA SWIRL", 30, 0);
	while(1) {
		VDP_waitVSync();
	}
	return 0;
}

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
}

void unselectEverything() {
	int x, y;
	for (y = 0; y != BOARD_Y; y++) {
		for (x = 0; x != BOARD_X; x++) {
			board[y][x].selected = FALSE;
		}
	}
}

void joyHandler(u16 joy, u16 changed, u16 state) {
	switch (joy) {
		case JOY_1:
        if (state & BUTTON_A) {
				if (board[SEL(cursor.posy)][SEL(cursor.posx)].selected == TRUE) {
					int deleted_amount = recursiveDelete(SEL(cursor.posx),SEL(cursor.posy), board[SEL(cursor.posy)][SEL(cursor.posx)].id);
					if (deleted_amount == 1)
						score-=10;
					else
						score+=deleted_amount * 10;
					applyGravity();
					applyLeftShift();
					drawBoard();
					selected = FALSE;
				}
				else if (board[SEL(cursor.posy)][SEL(cursor.posx)].id != 0) {
					if(selected) {
						unselectEverything();
					} 
					selected = TRUE;
					recursiveFloodSelect(SEL(cursor.posx), SEL(cursor.posy), board[SEL(cursor.posy)][SEL(cursor.posx)].id, TRUE);
					drawBoard();
				} else {
					if(selected) {
						unselectEverything();
						selected = FALSE;
						drawBoard();
					}
				}
		}
		if (state & BUTTON_UP) {
			if (SEL(cursor.posy) > 0) {
				int oldy = cursor.posy;
				while(cursor.posy != oldy - 16) {
					VDP_waitVSync();
					cursor.posy-=2;
					VDP_setSpriteDirectP(0, &cursor);
				}
			}
		}
		if (state & BUTTON_DOWN) {
			if (SEL(cursor.posy) < BOARD_Y - 1) {
				int oldy = cursor.posy;
				while(cursor.posy != oldy + 16) {
					VDP_waitVSync();
					cursor.posy+=2;
					VDP_setSpriteDirectP(0, &cursor);
				}
			}
		}
		if (state & BUTTON_LEFT) {
			if (SEL(cursor.posx) > 0) {
				int oldx = cursor.posx;
				while(cursor.posx != oldx - 16) {
					VDP_waitVSync();
					cursor.posx-=2;
					VDP_setSpriteDirectP(0, &cursor);
				}
			}
		}
		if (state & BUTTON_RIGHT) {
			if (SEL(cursor.posx) < BOARD_X - 1) {
				int oldx = cursor.posx;
				while(cursor.posx != oldx + 16) {
					VDP_waitVSync();
					cursor.posx+=2;
					VDP_setSpriteDirectP(0, &cursor);
				}
			}
		}
		break;
	}
}

void titleHandler(u16 joy, u16 changed, u16 state) {
	switch (joy) {
		case JOY_1:
         if (state & BUTTON_START) {
				waitflag = TRUE;
			}
			break;
	}

}

void titleScreen() {
	VDP_resetScreen();
	VDP_resetSprites();
	//palettes, tiles, and VDP registers get set here
	//TODO: Title Screen
	//TODO: Swirls
	//Load sprites
	VDP_loadTileData(swirls, TILE_USERINDEX, 20, TRUE);
	VDP_setPalette(PAL1, swirl_pal);
	VDP_setPalette(PAL2, sel_pal);
	VDP_setPalette(PAL3, std_pal);
	JOY_init();
	JOY_setEventHandler(titleHandler);
	
	VDP_drawText("- MEGA SWIRL GAME TEST -", 8, 0);
	VDP_drawText("Built June 22, 2013", 7, 2);
	VDP_drawText("Version v0.1.1b", 12, 3);
	VDP_drawText("Press start to play.", 10, 5); 
	while (waitflag == FALSE);

	srand(GET_HVCOUNTER);
	VDP_clearPlan(APLAN, FALSE);
	JOY_setEventHandler(joyHandler);
}

void srand(u16 seed) {
	randbase = 11073 * seed + 11;
}

u16 custrand() {
	 //this is the same random function but uses a different randbase
	 //custrand() + srand() provides slightly more enthropy than the function alone
	 #ifdef USE_XORSHIFT
	 static u32 x = 123456789;
	 static u32 y = 362436069;
	 static u32 z = 521288629;
	 static u32 w = 88675123;
	 u32 t;
	 
	t = x ^ (x << 11);
	x = y; y = z; z = w;
	w = w ^ (w >> 19) ^ (t ^ (t >> 8));
	return w;
	#else
	randbase ^= (randbase >> 1) ^ GET_HVCOUNTER;
    randbase ^= (randbase << 1);
    return randbase >> 3;
    #endif
}
