#ifndef GLOBALS
#define GLOBALS

#include <types.h>
#include <vdp_spr.h>

struct swirl {
	u8 id;
	u8 selected;
};

struct ls {
	u8 x;
	u8 y;
} ;

extern int waitflag;
extern u16 randbase;
extern int selected;
extern int score;
extern SpriteDef cursor;

#endif
