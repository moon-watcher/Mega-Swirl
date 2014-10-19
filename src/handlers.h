#ifndef HANDLERS
#define HANDLERS

#include <types.h>
#include <joy.h>
#include <globals.h>
#include <swirl_types.h>
#include <board.h>
#include <vdp.h>
#include <vdp_tile.h>
#include <vdp_spr.h>

void titleHandler(u16 joy, u16 changed, u16 state);
void joyHandler(u16 joy, u16 changed, u16 state);

#endif
