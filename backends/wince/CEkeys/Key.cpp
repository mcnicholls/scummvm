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
#include "Key.h"

namespace CEKEYS {
	Key::Key() :
	_ascii(0), _keycode(0), _flags(0) {
	}

	Key::Key(int ascii, int keycode, int flags) :
	_ascii(ascii), _keycode(keycode), _flags(flags) {
	}

	int Key::ascii() {
		return _ascii;
	}

	int Key::keycode() {
		return _keycode;
	}

	int Key::flags() {
		return _flags;
	}


	void Key::setAscii(int ascii) {
		_ascii = ascii;
		_keycode = ascii; // default
	}

	void Key::setKeycode(int keycode) {
		_keycode = keycode;
	}

	void Key::setFlags(int flags) {
		_flags = flags;
	}
}
