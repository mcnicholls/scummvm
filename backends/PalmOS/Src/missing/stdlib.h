/* ScummVM - Scumm Interpreter
 * Copyright (C) 2001  Ludvig Strigeus
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

#ifndef STDLIB_H
#define STDLIB_H

#include <PalmOS.h>
#include "MemGlue.h"

extern ErrJumpBuf stdlib_errJumpBuf;

#define DO_EXIT( code ) \
	if (ErrSetJump(stdlib_errJumpBuf) == 0) { code }
	
#define atoi				StrAToI
#define atol				StrAToI
#define abs(a)				((a) < 0 ? -(a) : (a))
//#define abs					fabs
#define	malloc(a)			MemGluePtrNew(a)
//#define free				MemPtrFree
//#define strtol(a,b,c)		StrAToI(a)
#define qsort(a,b,c,d)		SysQSort((a), (b), (c), (CmpFuncPtr)(&d), 0);
#define rand()				SysRandom(0)
#define abort()
#define strtoul(a,b,c)		((unsigned long)strtol(a,b,c))

void	*bsearch	(const void *key, const void *base, UInt32 nmemb, UInt32 size, int (*compar)(const void *, const void *));
MemPtr	 calloc		(UInt32 nelem, UInt32 elsize);
void	 exit		(Int16 status);
Err		 free		(MemPtr memP);
MemPtr	 realloc	(MemPtr oldP, UInt32 size);
long	 strtol		(const char *s, char **endptr, int base);

#endif
