/* ScummVM - Scumm Interpreter
 * Copyright (C) 2002-2005 The ScummVM project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header$
 */

#ifndef ENGINE_H
#define ENGINE_H

#include "common/scummsys.h"
#include "common/str.h"

class GameDetector;
class OSystem;
class SaveFileManager;
class SoundMixer;
class Timer;

class Engine {
public:
	OSystem *_system;
	SoundMixer *_mixer;
	Timer * _timer;

protected:
	const Common::String _gameDataPath;
	SaveFileManager *_saveFileMan;

public:
	Engine(OSystem *syst);
	virtual ~Engine();
	
	/**
	 * Init the engine.
	 * @return 0 for success, else an error code.
	 */
	virtual int init(GameDetector &detector) = 0;

	/**
	 * Start the main engine loop.
	 * The return value is not yet used, but could indicate whether the user
	 * wants to return to the launch or to fully quit ScummVM. 
	 * @return a result code
	 */
	virtual int go() = 0;

	/** Get the path to the game data directory. */
	virtual const char *getGameDataPath() const;

	/** Specific for each engine: prepare error string. */
	virtual void errorString(const char *buf_input, char *buf_output) = 0;

	void initCommonGFX(GameDetector &detector);
};

extern Engine *g_engine;

#endif
