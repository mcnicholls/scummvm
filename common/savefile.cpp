/* ScummVM - Scumm Interpreter
 * Copyright (C) 2002-2004 The ScummVM project
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
#include "common/util.h"
#include "common/savefile.h"

#include <stdio.h>
#include <string.h>

#ifdef USE_ZLIB
#include <zlib.h>
#endif

uint32 SaveFile::read(void *ptr, uint32 size) {
	return fread(ptr, 1, size);
}

uint32 SaveFile::write(const void *ptr, uint32 size) {
	return fwrite(ptr, 1, size);
}


class StdioSaveFile : public SaveFile {
private:
	FILE *fh;
public:
	StdioSaveFile(const char *filename, bool saveOrLoad)
		{ fh = ::fopen(filename, (saveOrLoad? "wb" : "rb")); }
	~StdioSaveFile()
		{ if(fh) ::fclose(fh); }

	bool isOpen() const { return fh != 0; }

protected:
	int fread(void *buf, int size, int cnt)
		{ return ::fread(buf, size, cnt, fh); }
	int fwrite(const void *buf, int size, int cnt)
		{ return ::fwrite(buf, size, cnt, fh); }
};


#ifdef USE_ZLIB
class GzipSaveFile : public SaveFile {
private:
	gzFile fh;
public:
	GzipSaveFile(const char *filename, bool saveOrLoad)
		{ fh = ::gzopen(filename, (saveOrLoad? "wb" : "rb")); }
	~GzipSaveFile()
		{ if(fh) ::gzclose(fh); }

	bool isOpen() const { return fh != 0; }

protected:
	int fread(void *buf, int size, int cnt) {
		return ::gzread(fh, buf, size * cnt);
	}
	int fwrite(const void *buf, int size, int cnt) {
		// Due to a "bug" in the zlib headers (or maybe I should say,
		// a bug in the C++ spec? Whatever <g>) we have to be a bit
		// hackish here and remove the const qualifier.
		// Note that gzwrite's buf param is declared as "const voidp"
		// which you might think is the same as "const void *" but it
		// is not - rather it is equal to "void const *" which is the 
		// same as "void *". Hrmpf
		return ::gzwrite(fh, const_cast<void *>(buf), size * cnt);
	}
};
#endif


SaveFile *SaveFileManager::open_savefile(const char *filename, const char *directory, bool saveOrLoad) {
	char buf[256];
	join_paths(filename, directory, buf, sizeof(buf));
	SaveFile *sf = makeSaveFile(buf, saveOrLoad);
	if (!sf->isOpen()) {
		delete sf;
		sf = 0;
	}
	return sf;
}

void SaveFileManager::join_paths(const char *filename, const char *directory,
								 char *buf, int bufsize) {
	buf[bufsize-1] = '\0';
	strncpy(buf, directory, bufsize-1);

#ifdef WIN32
	// Fix for Win98 issue related with game directory pointing to root drive ex. "c:\"
	if ((buf[0] != 0) && (buf[1] == ':') && (buf[2] == '\\') && (buf[3] == 0)) {
		buf[2] = 0;
	}
#endif

	const int dirLen = strlen(buf);

	if (dirLen > 0) {
#ifdef __MORPHOS__
		if (buf[dirLen-1] != ':' && buf[dirLen-1] != '/')
#endif

#if !defined(__GP32__) && !defined(__PALM_OS__)
		strncat(buf, "/", bufsize-1);	// prevent double /
#endif
	}
	strncat(buf, filename, bufsize-1);
}

SaveFile *SaveFileManager::makeSaveFile(const char *filename, bool saveOrLoad) {
#ifdef USE_ZLIB
	return new GzipSaveFile(filename, saveOrLoad);
#else
	return new StdioSaveFile(filename, saveOrLoad);
#endif
}
