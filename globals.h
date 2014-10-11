#ifndef GLOBALS
#define GLOBALS

#include <types.h>
#include <vdp_spr.h>

#define FALSE 0
#define TRUE 1

#define BOARD_X 15
#define BOARD_Y 14
#define SWIRL_WIDTH 2
#define SWIRL_HEIGHT 2
#define PRIORITY_LOW 0
#define PRIORITY_HIGH 1
#define CURSOR_INCREMENT_SPEED 8
#define TITLE_SCREEN_SNOWFLAKES 20

#define BUILD_DATE "Built "__DATE__" "__TIME__

#define CUR(x) ((x) * 2)
#define SEL(x) ((x) / 16)

struct swirl {
	u8 id;
	u8 selected;
};

struct ls {
	u8 x;
	u8 y;
};

extern struct swirl board[BOARD_Y][BOARD_X];
extern struct ls lastselected;
extern int waitflag;
extern u16 randbase;
extern int selected;
extern int score;
extern SpriteDef cursor;

#endif
