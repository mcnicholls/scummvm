/* ScummVM - Scumm Interpreter
 * Copyright (C) 2006 The ScummVM project
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

#ifndef PARALLACTION_INVENTORY_H
#define PARALLACTION_INVENTORY_H



namespace Parallaction {

struct Cnv;

struct InventoryItem {
	uint32		_id;
	uint16		_index;
};

extern InventoryItem _inventory[];

void initInventory();
void openInventory();
void closeInventory();
int16 isItemInInventory(int32 v);
void cleanInventory();
void addInventoryItem(uint16 item);

void redrawInventory();
void highlightInventoryItem(int16 pos, byte color);
void refreshInventoryItem(const char *character, uint16 index);
void refreshInventory(const char *character);

void extractInventoryGraphics(int16 pos, byte *dst);


} // namespace Parallaction

#endif
