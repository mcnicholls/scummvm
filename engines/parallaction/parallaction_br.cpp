/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
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

#include "common/system.h"
#include "common/util.h"

#include "parallaction/parallaction.h"
#include "parallaction/input.h"
#include "parallaction/sound.h"

namespace Parallaction {


const char *Parallaction_br::_partNames[] = {
	"PART0",
	"PART1",
	"PART2",
	"PART3",
	"PART4"
};

const char *partFirstLocation[] = {
	"intro",
	"museo",
	"start",
	"bolscoi",
	"treno"
};

int Parallaction_br::init() {

	_screenWidth = 640;
	_screenHeight = 400;

	if (getGameType() == GType_BRA) {
		if (getPlatform() == Common::kPlatformPC) {
			_disk = new DosDisk_br(this);
			_disk->setLanguage(2);					// NOTE: language is now hardcoded to English. Original used command-line parameters.
			_soundMan = new DummySoundMan(this);
		} else {
			_disk = new AmigaDisk_br(this);
			_disk->setLanguage(2);					// NOTE: language is now hardcoded to English. Original used command-line parameters.
			_soundMan = new AmigaSoundMan(this);
		}
	} else {
		error("unknown game type");
	}


	initResources();
	initFonts();
	initCursors();
	initOpcodes();
	_locationParser = new LocationParser_br(this);
	_locationParser->init();
	_programParser = new ProgramParser_br(this);
	_programParser->init();

	_part = -1;

	Parallaction::init();

	return 0;
}

Parallaction_br::~Parallaction_br() {
	freeFonts();

	delete _dinoCursor;
	delete _dougCursor;
	delete _donnaCursor;

}

void Parallaction_br::callFunction(uint index, void* parm) {
	assert(index < 6);	// magic value 6 is maximum # of callables for Big Red Adventure

	(this->*_callables[index])(parm);
}

int Parallaction_br::go() {

	guiSplash("dyna");
	guiSplash("core");

	while (_vm->_quit == 0) {

		guiStart();

		if (_vm->_quit)
			return _rtl;

//		initCharacter();

		_input->_inputMode = Input::kInputModeGame;
		while (((_engineFlags & kEngineReturn) == 0) && (!_vm->_quit)) {
			runGame();
		}
		_engineFlags &= ~kEngineReturn;

		freePart();
//		freeCharacter();

	}

	return _rtl;
}



void Parallaction_br::freeFonts() {

	delete _menuFont;
	delete _dialogueFont;

	return;
}

void Parallaction_br::initCursors() {

	if (getPlatform() == Common::kPlatformPC) {
		_dinoCursor = _disk->loadPointer("pointer1");
		_dougCursor = _disk->loadPointer("pointer2");
		_donnaCursor = _disk->loadPointer("pointer3");

		_mouseArrow = _donnaCursor;
	} else {
		// TODO: Where are the Amiga cursors?
	}

}

void Parallaction_br::setMousePointer(int16 index) {
	// FIXME: Where are the Amiga cursors?
	if (getPlatform() == Common::kPlatformAmiga)
		return;

	Common::Rect r;
	_mouseArrow->getRect(0, r);

	_system->setMouseCursor(_mouseArrow->getData(0), r.width(), r.height(), 0, 0, 0);
	_system->showMouse(true);

}

void Parallaction_br::initPart() {

	memset(_counters, 0, ARRAYSIZE(_counters));

	_globalTable = _disk->loadTable("global");
	_objectsNames = _disk->loadTable("objects");
	_countersNames = _disk->loadTable("counters");

//	_disk->loadObjects("icone.ico");

}

void Parallaction_br::freePart() {

	delete _globalTable;
	delete _objectsNames;
	delete _countersNames;

	_globalTable = 0;
	_objectsNames = 0;
	_countersNames = 0;
}

void Parallaction_br::startPart() {

	initPart();

	strcpy(_location._name, partFirstLocation[_part]);

	parseLocation("common");
	changeLocation(_location._name);

}

void Parallaction_br::runPendingZones() {
	ZonePtr z;

	if (_activeZone) {
		z = _activeZone;	// speak Zone or sound
		_activeZone = nullZonePtr;
		runZone(z);			// FIXME: BRA doesn't handle sound yet
	}

	if (_activeZone2) {
		z = _activeZone2;	// speak Zone or sound
		_activeZone2 = nullZonePtr;
		runZone(z);
	}
}


void Parallaction_br::changeLocation(char *location) {

	// free open location stuff
	clearSubtitles();
	freeBackground();
	_gfx->clearGfxObjects();
	_location._programs.clear();
	freeZones();
	freeAnimations();
//	free(_location._comment);
//	_location._comment = 0;
//	_location._commands.clear();
//	_location._aCommands.clear();


	// load new location
	parseLocation(location);
	runCommands(_location._commands);
//	doLocationEnterTransition();
	runCommands(_location._aCommands);

	_engineFlags &= ~kEngineChangeLocation;
}


// FIXME: Parallaction_br::parseLocation() is now a verbatim copy of the same routine from Parallaction_ns.
void Parallaction_br::parseLocation(const char *filename) {
	debugC(1, kDebugParser, "parseLocation('%s')", filename);

	allocateLocationSlot(filename);
	Script *script = _disk->loadLocation(filename);

	_locationParser->parse(script);
	delete script;

	// this loads animation scripts
	AnimationList::iterator it = _vm->_location._animations.begin();
	for ( ; it != _vm->_location._animations.end(); it++) {
		if ((*it)->_scriptName) {
			loadProgram(*it, (*it)->_scriptName);
		}
	}

	debugC(1, kDebugParser, "parseLocation('%s') done", filename);
	return;
}

void Parallaction_br::loadProgram(AnimationPtr a, const char *filename) {
	debugC(1, kDebugParser, "loadProgram(Animation: %s, script: %s)", a->_name, filename);

	Script *script = _disk->loadScript(filename);
	ProgramPtr program(new Program);
	program->_anim = a;

	_programParser->parse(script, program);

	delete script;

	_vm->_location._programs.push_back(program);

	debugC(1, kDebugParser, "loadProgram() done");

	return;
}



void Parallaction_br::changeCharacter(const char *name) {
	const char *charName = _char.getName();
	if (!scumm_stricmp(charName, name)) {
		return;
	}

	_char.setName(name);
	_char._talk = _disk->loadTalk(name);
}


void Parallaction_br::setArrowCursor() {



}

void Parallaction_br::setInventoryCursor(int pos) {



}

} // namespace Parallaction
