/* ScummVM - Scumm Interpreter
 * Copyright (C) 2006 The ScummVM project
 *
 * Copyright (C) 1999-2001 Sarien Team
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#ifndef AGI_GRAPHICS_H
#define AGI_GRAPHICS_H

#include "common/stdafx.h"

namespace Agi {

#define GFX_WIDTH	320
#define GFX_HEIGHT	200
#define CHAR_COLS	8
#define CHAR_LINES	8

class AgiEngine;

class GfxMgr {
private:
	AgiEngine *_vm;

	uint8 palette[32 * 3];
	uint8 *agi_screen;
	unsigned char *screen;

	uint8 *shake_h, *shake_v;

public:
	GfxMgr(AgiEngine *vm) {
		_vm = vm;
		shake_h = NULL;
		shake_v = NULL;
	}

	void gfxPutBlock(int x1, int y1, int x2, int y2);

	void putTextCharacter(int, int, int, unsigned int, int, int);
	void shakeScreen(int);
	void shakeStart();
	void shakeEnd();
	void saveScreen();
	void restoreScreen();

	int initVideo();
	int deinitVideo();
	void scheduleUpdate(int, int, int, int);
	void doUpdate();
	void putScreen();
	void flushBlock(int, int, int, int);
	void flushBlockA(int, int, int, int);
	void putPixelsA(int, int, int, uint8 *);
	void flushScreen();
	void clearScreen(int);
	void clearConsoleScreen(int);
	void drawBox(int, int, int, int, int, int, int);
	void drawButton(int, int, const char *, int, int, int fgcolor = 0, int bgcolor = 0);
	int testButton(int, int, const char *);
	void drawRectangle(int, int, int, int, int);
	void saveBlock(int, int, int, int, uint8 *);
	void restoreBlock(int, int, int, int, uint8 *);
	void initPalette(uint8 *);
	void drawFrame(int x1, int y1, int x2, int y2, int c1, int c2);

	void putPixel(int, int, int);
	void putBlock(int x1, int y1, int x2, int y2);
	void gfxSetPalette();
	void putPixelsHires(int x, int y, int n, uint8 *p);

	int keypress();
	int getKey();
	void printCharacter(int, int, char, int, int);
	void pollTimer();
	int initMachine();
	int deinitMachine();
};

} // End of namespace Agi

#endif				/* AGI_GRAPHICS_H */
