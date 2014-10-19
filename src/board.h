#ifndef BOARDOPS
#define BOARDOPS

#include <audio_ts.h>
#include <globals.h>
#include <swirl_types.h>
#include <vdp.h>
#include <vdp_spr.h>
#include <vdp_tile.h>
#include <vdp_bg.h>
#include <string.h>
#include <types.h>
#include <sound.h>
#include <custrand.h>

void recursiveFloodSelect(int x, int y, int ch, int selbit);
int recursiveDelete(int x, int y, int type);
void applyGravity();
void applyLeftShift();
void drawBoard();
void initBoard();
void unselectEverything();

#endif
