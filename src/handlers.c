#include <handlers.h>

void titleHandler(u16 joy, u16 changed, u16 state) {
	switch (joy) {
		case JOY_1:
         if (state & BUTTON_START) {
				waitflag = TRUE;
			}
			break;
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
					cursor.posy-=CURSOR_INCREMENT_SPEED;
					VDP_setSpriteDirectP(0, &cursor);
				}
			}
		}
		if (state & BUTTON_DOWN) {
			if (SEL(cursor.posy) < BOARD_Y - 1) {
				int oldy = cursor.posy;
				while(cursor.posy != oldy + 16) {
					VDP_waitVSync();
					cursor.posy+=CURSOR_INCREMENT_SPEED;
					VDP_setSpriteDirectP(0, &cursor);
				}
			}
		}
		if (state & BUTTON_LEFT) {
			if (SEL(cursor.posx) > 0) {
				int oldx = cursor.posx;
				while(cursor.posx != oldx - 16) {
					VDP_waitVSync();
					cursor.posx-=CURSOR_INCREMENT_SPEED;
					VDP_setSpriteDirectP(0, &cursor);
				}
			}
		}
		if (state & BUTTON_RIGHT) {
			if (SEL(cursor.posx) < BOARD_X - 1) {
				int oldx = cursor.posx;
				while(cursor.posx != oldx + 16) {
					VDP_waitVSync();
					cursor.posx+=CURSOR_INCREMENT_SPEED;
					VDP_setSpriteDirectP(0, &cursor);
				}
			}
		}
		break;
	}
}
