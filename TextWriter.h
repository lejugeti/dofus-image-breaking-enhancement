#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

class TextWriter {
	
public:
	TextWriter();

	void write();
private:
	FT_Library library;
};