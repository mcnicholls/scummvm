/* ScummVM - Scumm Interpreter
 * Copyright (C) 2001-2005 The ScummVM project
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header$
 *
 */

#include "stdafx.h"

#include "simon/simon.h"
#include "simon/intern.h"

namespace Simon {

#ifdef __PALM_OS__
static const byte *_simon1_cursor;
#else
static const byte _simon1_cursor[256] = {
	0xe1,0xe0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xe1,0xe1,0xe0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xe1,0xe1,0xe1,0xe0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xe1,0xe1,0xe1,0xe1,0xe0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xe1,0xe1,0xe1,0xe1,0xe1,0xe0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xe1,0xe1,0xe1,0xe1,0xe1,0xe1,0xe0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xe1,0xe1,0xe1,0xe1,0xe0,0xe0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xe1,0xff,0xff,0xe1,0xe0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xe1,0xe0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xe1,0xe0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xe1,0xe0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
};
#endif
static const byte _simon2_cursors[10][256] = {
	// cross hair
	{ 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xec,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xec,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xec,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xec,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xec,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xef,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xec,0xec,0xec,0xec,0xec,0xef,0xff,0xea,0xff,0xef,0xec,0xec,0xec,0xec,0xec,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xef,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xec,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xec,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xec,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xec,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xec,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff },
	// examine
	{ 0xff,0xff,0xef,0xef,0xef,0xef,0xef,0xef,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xef,0xee,0xeb,0xe4,0xe4,0xe4,0xee,0xef,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xef,0xee,0xeb,0xee,0xef,0xef,0xee,0xec,0xee,0xef,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xef,0xeb,0xee,0xef,0xee,0xee,0xef,0xee,0xe4,0xef,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xef,0xeb,0xef,0xef,0xef,0xec,0xee,0xef,0xe4,0xef,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xef,0xeb,0xef,0xef,0xee,0xef,0xef,0xef,0xe4,0xef,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xef,0xeb,0xee,0xef,0xef,0xef,0xef,0xee,0xe4,0xef,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xef,0xee,0xeb,0xee,0xef,0xef,0xee,0xe4,0xee,0xef,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xef,0xee,0xeb,0xeb,0xeb,0xeb,0xee,0xe4,0xec,0xef,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xef,0xef,0xef,0xef,0xef,0xef,0xeb,0xe4,0xee,0xef,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xef,0xee,0xe4,0xeb,0xef,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xef,0xeb,0xe4,0xeb,0xef,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xef,0xeb,0xec,0xeb,0xef,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xef,0xeb,0xe4,0xef,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xef,0xef,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff },
	// pick up  
	{ 0xff,0xff,0xff,0xff,0xff,0xe5,0xe5,0xe5,0xe5,0xe5,0xe5,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xe5,0xe6,0xe6,0xe7,0xe7,0xe6,0xe6,0xe5,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xe5,0xe7,0xe7,0xe7,0xe7,0xe8,0xe8,0xe8,0xe8,0xe5,0xff,0xff,0xff,
	  0xff,0xff,0xe5,0xe6,0xe7,0xe7,0xe7,0xe7,0xe7,0xe7,0xe8,0xe9,0xe7,0xe5,0xff,0xff,
	  0xff,0xe5,0xe6,0xe7,0xe6,0xe5,0xff,0xff,0xff,0xff,0xe5,0xe6,0xe8,0xe6,0xe5,0xff,
	  0xff,0xe5,0xe7,0xe7,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,0xe5,0xe8,0xe7,0xe5,0xff,
	  0xff,0xe5,0xe7,0xe7,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,0xe5,0xe7,0xe7,0xe5,0xff,
	  0xff,0xef,0xeb,0xeb,0xef,0xff,0xff,0xff,0xff,0xff,0xff,0xef,0xeb,0xeb,0xef,0xff,
	  0xff,0xef,0xee,0xeb,0xee,0xef,0xff,0xff,0xff,0xff,0xef,0xee,0xeb,0xee,0xef,0xff,
	  0xff,0xff,0xef,0xeb,0xeb,0xef,0xff,0xff,0xff,0xff,0xef,0xeb,0xeb,0xef,0xff,0xff,
	  0xff,0xff,0xef,0xee,0xe4,0xee,0xef,0xff,0xff,0xef,0xee,0xe4,0xee,0xef,0xff,0xff,
	  0xff,0xff,0xff,0xef,0xe4,0xeb,0xef,0xff,0xff,0xef,0xeb,0xe4,0xef,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xeb,0xeb,0xeb,0xef,0xef,0xeb,0xeb,0xeb,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xef,0xee,0xee,0xee,0xee,0xe1,0xe1,0xef,0xff,0xff,0xff,0xe4,
	  0xef,0xee,0xeb,0xeb,0xeb,0xeb,0xeb,0xe4,0xe4,0xe4,0xe4,0xe4,0xe4,0xe4,0xeb,0xec,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe4 },
	// give
	{ 0xff,0xff,0xff,0xff,0xff,0xe5,0xe7,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xe5,0xe7,0xe8,0xe7,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xe9,0xe7,0xe8,0xe8,0xe8,0xe7,0xe9,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xe5,0xe7,0xea,0xe8,0xe8,0xe8,0xea,0xe7,0xe5,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xe5,0xe7,0xe8,0xe8,0xea,0xe9,0xea,0xe8,0xe8,0xe7,0xe5,0xff,0xff,0xff,0xff,
	  0xe5,0xe7,0xe9,0xe8,0xe8,0xe9,0xec,0xe9,0xe8,0xe8,0xe8,0xe7,0xe5,0xff,0xff,0xff,
	  0xe5,0xe7,0xe7,0xe9,0xe8,0xec,0xe9,0xec,0xe8,0xe9,0xe7,0xe6,0xe5,0xff,0xff,0xff,
	  0xe5,0xe7,0xe7,0xe8,0xec,0xe9,0xe9,0xe9,0xec,0xe7,0xe6,0xe6,0xe5,0xff,0xff,0xff,
	  0xe5,0xe7,0xe7,0xea,0xe8,0xe9,0xe9,0xe9,0xe7,0xec,0xec,0xe4,0xe5,0xff,0xff,0xff,
	  0xe5,0xe7,0xe7,0xe9,0xe7,0xe8,0xe9,0xe7,0xe6,0xec,0xe4,0xec,0xe4,0xef,0xff,0xff,
	  0xe5,0xe6,0xe7,0xe9,0xe7,0xe7,0xe8,0xe6,0xe6,0xe4,0xec,0xe4,0xec,0xe4,0xef,0xff,
	  0xff,0xe5,0xe6,0xe9,0xe7,0xe7,0xe8,0xe6,0xe6,0xe8,0xe4,0xec,0xe4,0xec,0xeb,0xff,
	  0xff,0xff,0xe5,0xe9,0xe7,0xe7,0xe8,0xe6,0xe6,0xe8,0xe6,0xe4,0xec,0xeb,0xef,0xff,
	  0xff,0xff,0xff,0xe8,0xe7,0xe7,0xe8,0xe6,0xe6,0xe7,0xff,0xef,0xeb,0xef,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xe5,0xe7,0xe8,0xe6,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xe5,0xe6,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff },
	// talk
	{ 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xe5,0xe5,0xe5,0xe5,0xe5,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xe5,0xe7,0xe8,0xe8,0xe8,0xe7,0xe6,0xe5,0xe5,0xe5,0xff,0xff,0xff,0xff,
	  0xff,0xe5,0xe6,0xe9,0xea,0xe6,0xea,0xe9,0xe8,0xe9,0xe8,0xe7,0xe5,0xff,0xff,0xff,
	  0xff,0xe5,0xe7,0xe5,0xef,0xe5,0xec,0xea,0xe5,0xea,0xec,0xe5,0xe9,0xe6,0xff,0xff,
	  0xff,0xe5,0xe6,0xe5,0xef,0xef,0xef,0xe5,0xef,0xef,0xe5,0xef,0xef,0xe8,0xe5,0xff,
	  0xff,0xe5,0xe9,0xea,0xe5,0xe8,0xe7,0xe6,0xe6,0xe8,0xe7,0xe5,0xec,0xe9,0xe5,0xff,
	  0xff,0xe5,0xe9,0xe8,0xe5,0xe7,0xe8,0xe8,0xe9,0xe9,0xe8,0xe5,0xe9,0xe9,0xe5,0xff,
	  0xff,0xe5,0xe6,0xec,0xea,0xe5,0xe6,0xe6,0xe7,0xe7,0xe6,0xe5,0xec,0xe8,0xe5,0xff,
	  0xff,0xff,0xe5,0xe9,0xe8,0xe9,0xe5,0xe8,0xe5,0xe8,0xe5,0xe9,0xe9,0xe7,0xe5,0xff,
	  0xff,0xff,0xe5,0xe7,0xe9,0xec,0xe8,0xec,0xe8,0xec,0xe8,0xec,0xe8,0xe5,0xff,0xff,
	  0xff,0xff,0xff,0xe5,0xe6,0xe8,0xe9,0xe9,0xe9,0xe9,0xe9,0xe8,0xe5,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xe5,0xe5,0xe5,0xe5,0xe5,0xe5,0xe5,0xe5,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff },
	// use
	{ 0xff,0xff,0xff,0xff,0xff,0xee,0xe1,0xeb,0xee,0xef,0xef,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xef,0xef,0xef,0xe4,0xeb,0xee,0xe5,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xeb,0xe4,0xe4,0xeb,0xe5,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xeb,0xe4,0xec,0xe4,0xef,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xeb,0xeb,0xe4,0xe4,0xee,0xef,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xee,0xeb,0xeb,0xeb,0xe1,0xef,0xee,0xef,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe5,0xe6,0xef,0xef,0xee,0xeb,0xeb,0xe4,0xee,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xe5,0xe6,0xff,0xff,0xff,0xef,0xeb,0xec,0xeb,0xef,
	  0xff,0xff,0xff,0xff,0xff,0xe5,0xe6,0xe5,0xff,0xff,0xff,0xee,0xe4,0xeb,0xef,0xff,
	  0xff,0xff,0xff,0xe5,0xe5,0xe6,0xe5,0xff,0xff,0xff,0xff,0xef,0xee,0xef,0xff,0xff,
	  0xff,0xff,0xe5,0xe6,0xe8,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,0xef,0xff,0xff,0xff,
	  0xff,0xe5,0xe6,0xe8,0xe6,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xe5,0xe6,0xe8,0xe6,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xe5,0xe6,0xe6,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xe5,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff },
	// wear
	{ 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xef,0xeb,0xed,0xe4,0xe2,0xeb,0xee,0xee,0xee,0xef,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xef,0xe2,0xec,0xe2,0xe1,0xee,0xef,0xef,0xee,0xef,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xef,0xeb,0xed,0xeb,0xee,0xef,0xef,0xef,0xee,0xef,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xef,0xee,0xe4,0xeb,0xee,0xef,0xef,0xee,0xef,0xef,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xef,0xe4,0xeb,0xee,0xef,0xef,0xee,0xef,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xef,0xe2,0xeb,0xee,0xef,0xef,0xee,0xef,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xef,0xeb,0xe1,0xee,0xef,0xef,0xee,0xef,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xef,0xeb,0xe1,0xee,0xef,0xef,0xef,0xef,0xff,0xff,0xff,0xff,
	  0xff,0xef,0xef,0xef,0xe1,0xe4,0xe4,0xe4,0xe1,0xeb,0xee,0xef,0xef,0xef,0xff,0xff,
	  0xef,0xee,0xee,0xef,0xee,0xee,0xee,0xee,0xee,0xef,0xef,0xef,0xee,0xee,0xef,0xff,
	  0xff,0xef,0xef,0xee,0xe1,0xe2,0xe4,0xe4,0xe4,0xeb,0xe1,0xee,0xef,0xef,0xff,0xff,
	  0xff,0xff,0xff,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff },
	// move
	{ 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xe1,0xe1,0xe1,0xe1,0xe1,0xe1,0xe1,0xe1,0xe1,0xe1,0xe1,0xe1,0xe1,0xe1,0xff,
	  0xff,0xe1,0xe2,0xe2,0xe2,0xe2,0xe2,0xe2,0xe2,0xe2,0xe2,0xe2,0xe2,0xe2,0xe1,0xff,
	  0xff,0xe1,0xe3,0xe3,0xe3,0xed,0xe3,0xe3,0xe3,0xe3,0xed,0xe3,0xe3,0xe3,0xe1,0xff,
	  0xff,0xe1,0xe3,0xe3,0xed,0xec,0xe3,0xe3,0xe3,0xe3,0xec,0xed,0xe3,0xe3,0xe1,0xff,
	  0xff,0xe1,0xe3,0xed,0xec,0xec,0xec,0xec,0xec,0xec,0xec,0xec,0xed,0xe3,0xe1,0xff,
	  0xff,0xe1,0xed,0xec,0xec,0xec,0xec,0xec,0xec,0xec,0xec,0xec,0xec,0xed,0xe1,0xff,
	  0xff,0xe1,0xe3,0xed,0xec,0xec,0xec,0xec,0xec,0xec,0xec,0xec,0xed,0xe3,0xe1,0xff,
	  0xff,0xe1,0xe3,0xe3,0xed,0xec,0xe3,0xe3,0xe3,0xe3,0xec,0xed,0xe3,0xe3,0xe1,0xff,
	  0xff,0xe1,0xe3,0xe3,0xe3,0xed,0xe3,0xe3,0xe3,0xe3,0xed,0xe3,0xe3,0xe3,0xe1,0xff,
	  0xff,0xe1,0xe2,0xe2,0xe2,0xe2,0xe2,0xe2,0xe2,0xe2,0xe2,0xe2,0xe2,0xe2,0xe1,0xff,
	  0xff,0xe1,0xe1,0xe1,0xe1,0xe1,0xe1,0xe1,0xe1,0xe1,0xe1,0xe1,0xe1,0xe1,0xe1,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff },
	// open
	{ 0xff,0xff,0xe5,0xe8,0xe8,0xe7,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xe5,0xe8,0xe7,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xe5,0xe7,0xe5,0xe7,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xe5,0xff,0xe5,0xe7,0xe6,0xe9,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xe6,0xea,0xe6,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xe6,0xea,0xe6,0xe7,0xe5,0xff,0xe5,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xe6,0xea,0xe6,0xff,0xe5,0xe7,0xe5,0xe7,0xe5,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xe6,0xea,0xe6,0xff,0xff,0xff,0xe5,0xe7,0xe8,0xe5,0xff,0xff,0xff,
	  0xff,0xe5,0xe6,0xea,0xe6,0xff,0xff,0xff,0xe5,0xe7,0xe8,0xe8,0xe5,0xff,0xff,0xff,
	  0xff,0xe5,0xe9,0xea,0xea,0xea,0xea,0xea,0xea,0xea,0xea,0xe5,0xff,0xff,0xff,0xff,
	  0xff,0xe5,0xe9,0xe7,0xe7,0xe7,0xe7,0xe7,0xe7,0xe7,0xea,0xe5,0xff,0xff,0xff,0xff,
	  0xff,0xe5,0xe9,0xe5,0xe5,0xe5,0xe5,0xe5,0xe5,0xe5,0xe9,0xe5,0xff,0xff,0xff,0xff,
	  0xff,0xe5,0xe9,0xe8,0xe8,0xe8,0xe8,0xe8,0xe7,0xe7,0xe9,0xe5,0xff,0xff,0xff,0xff,
	  0xff,0xe5,0xe9,0xe6,0xe6,0xe6,0xe6,0xe6,0xe6,0xe5,0xe9,0xe5,0xff,0xff,0xff,0xff,
	  0xff,0xe5,0xe9,0xe8,0xe8,0xe8,0xe8,0xe8,0xe8,0xe7,0xe9,0xe5,0xff,0xff,0xff,0xff,
	  0xff,0xe5,0xe9,0xe9,0xe9,0xe9,0xe9,0xe9,0xe9,0xe9,0xe9,0xe5,0xff,0xff,0xff,0xff },
	// question mark
	{ 0xff,0xff,0xff,0xff,0xff,0xe5,0xe5,0xe5,0xe5,0xe5,0xe5,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xe5,0xe7,0xea,0xec,0xec,0xec,0xe9,0xe5,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xe5,0xe7,0xea,0xec,0xea,0xe9,0xea,0xec,0xe9,0xe5,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xe5,0xe9,0xec,0xe9,0xe8,0xe7,0xe8,0xea,0xec,0xe5,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xe5,0xe8,0xe9,0xe8,0xe5,0xe5,0xe8,0xe9,0xec,0xe5,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xe5,0xe5,0xe5,0xe5,0xe8,0xe9,0xec,0xe9,0xe5,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xe5,0xe9,0xec,0xec,0xe9,0xe5,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xe5,0xe8,0xec,0xea,0xe8,0xe5,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xe5,0xe9,0xec,0xe9,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xe5,0xe9,0xea,0xe9,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xe5,0xe7,0xe9,0xe7,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xe5,0xe5,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xe5,0xe8,0xe9,0xe8,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xe5,0xe9,0xec,0xe9,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xe5,0xe8,0xe9,0xe8,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,
	  0xff,0xff,0xff,0xff,0xff,0xff,0xe5,0xe5,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,0xff },
};

void SimonEngine::draw_mouse_pointer() {
	if (_game & GF_SIMON2)
		_system->setMouseCursor(_simon2_cursors[_mouse_cursor], 16, 16, 7, 7);
	else
		_system->setMouseCursor(_simon1_cursor, 16, 16, 0, 0);
}

} // End of namespace Simon

#ifdef __PALM_OS__
#include "scumm_globals.h"

_GINIT(Simon_Cursor)
_GSETPTR(Simon::_simon1_cursor, GBVARS_SIMON1CURSOR_INDEX, byte, GBVARS_SIMON)
_GEND

_GRELEASE(Simon_Cursor)
_GRELEASEPTR(GBVARS_SIMON1CURSOR_INDEX, GBVARS_SIMON)
_GEND

#endif
