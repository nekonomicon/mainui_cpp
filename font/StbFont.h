/*
StbFont.h -- stb_truetype font renderer
Copyright (C) 2017 a1batross

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/
#pragma once
#if !defined( _WIN32 ) && !defined( FREETYPEFONT_H )
#define FREETYPEFONT_H

#if defined(MAINUI_USE_CUSTOM_FONT_RENDER) && defined(MAINUI_USE_STB)

#include "BaseFontBackend.h"
#include "utl/utlmemory.h"
#include "utl/utlrbtree.h"
#include "stb_truetype.h"

struct abc_t
{
	int ch;
	int a, b, c;
};

class CStbFont : public IBaseFont
{
public:
	CStbFont();
	~CStbFont();

	bool Create(const char *name,
		int tall, int weight,
		int blur, float brighten,
		int outlineSize,
		int scanlineOffset, float scanlineScale,
		int flags);
	void GetCharRGBA(int ch, Point pt, Size sz, unsigned char *rgba, Size &drawSize);
	bool IsValid() const;
	void GetCharABCWidths( int ch, int &a, int &b, int &c );
	bool HasChar( int ch ) const;

private:
	char m_szRealFontFile[4096];
	bool FindFontDataFile(const char *name, int tall, int weight, int flags, char *dataFile, int dataFileChars);

	byte *m_pFontData;
	stbtt_fontinfo m_fontInfo;

	float scale;

	CUtlRBTree<abc_t, int> m_ABCCache;

	friend class CFontManager;
};

#endif // defined(MAINUI_USE_CUSTOM_FONT_RENDER) && defined(MAINUI_USE_FREETYPE)

#endif // FREETYPEFONT_H
