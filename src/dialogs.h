#ifndef SWIRLDIALOGS
#define SWIRLDIALOGS

#define		CORNER		TILE_USERINDEX + 55
#define		HORIZ		TILE_USERINDEX + 56
#define		VERT		TILE_USERINDEX + 57
#define		ARROW		TILE_USERINDEX + 58

#include <types.h>
#include <vdp.h>
#include <vdp_bg.h>
#include <vdp_tile.h>

void drawDialog(u8 x, u8 y, u8 width, u8 height);

#endif
