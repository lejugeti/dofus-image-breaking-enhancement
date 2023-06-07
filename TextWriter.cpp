#include "TextWriter.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <stdexcept>
#include <iostream>

#include <boost/gil.hpp>
#include <boost/gil/io/io.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
using namespace boost::gil;

using namespace std;


TextWriter::TextWriter() {

}

void TextWriter::write() {
	FT_Face face;

	FT_Error error = FT_Init_FreeType(&library);
	if (error) {
		throw runtime_error("L'initialisation de Freetype a échoué");
	}

	error = FT_New_Face(library,
		"D:/Dev/dofus-image-breaking-enhancement/fonts/arial.ttf",
		0,
		&face);
	if (error == FT_Err_Unknown_File_Format)
	{
		cout << "Format non reconnu";
	}
	else if (error)
	{
		cout << "Autre erreur :(";
	}
	error = FT_Set_Pixel_Sizes(
		face,   /* handle to face object */
		0,      /* pixel_width           */
		64);   /* pixel_height          */
	if (error)
	{
		cout << "resize pas ok";
	}

	int glyph_index = FT_Get_Char_Index(face, 'a');
	FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
	FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

	FT_Bitmap bpm = face->glyph->bitmap;
	gray8_image_t img(bpm.width, bpm.rows);
	gray8_view_t gray_view = view(img);

	for (int y = 0; y < bpm.rows; ++y) {
		gray8_view_t::x_iterator col_iterator = gray_view.row_begin(y);

		for (int x = 0; x < bpm.width; ++x) {
			uint8_t val = bpm.buffer[x + y * bpm.width];
			*col_iterator = gray8_pixel_t(val);
			++col_iterator;
		}
	}

	write_view("D:/Dev/dofus-image-breaking-enhancement/images/yo.png", view(img), png_tag());
}