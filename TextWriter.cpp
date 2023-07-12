#include "TextWriter.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <stdexcept>
#include <iostream>

#include "models/text/TextDimensions.h"

using namespace std;

TextWriter::TextWriter() {
	FT_Error error = FT_Init_FreeType(&library);
	if (error) {
		throw runtime_error("L'initialisation de Freetype a échoué");
	}
}

TextDimensions TextWriter::write_in_image(std::string texte, rgba8_image_t* img, int base_col, int base_ligne, int taille_pixel) {
	FT_Face face;
	FT_Error error;

	error = FT_New_Face(library,
		"D:/Dev/dofus-image-breaking-enhancement/fonts/arial.ttf",
		0,
		&face);
	if (error == FT_Err_Unknown_File_Format) {
		throw runtime_error("Format non reconnu");
	} else if (error) {
		throw runtime_error("Erreur Freetype inconnue");
	}
	error = FT_Set_Pixel_Sizes(
		face,   /* handle to face object */
		0,      /* pixel_width           */
		taille_pixel);   /* pixel_height          */
	if (error) {
		throw runtime_error("Le resize a échoué");
	}

	rgba8_view_t rgb_view = view(*img);
	int sum_width = 0;
	int max_height = 0;

	for (char character : texte) {
		int glyph_index = FT_Get_Char_Index(face, character);
		FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
		FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

		FT_Bitmap bpm = face->glyph->bitmap;
		sum_width += bpm.width;
		if (bpm.rows > max_height) {
			max_height = bpm.rows;
		}

		int ligne_debut_ecriture = base_ligne - (face->glyph->metrics.horiBearingY >> 6); // on part de la ligne de base et on retranche le bearingY du caractère pour aligner

		for (int row = 0; row < bpm.rows; ++row) {
			rgba8_view_t::x_iterator dest_col_iterator = rgb_view.x_at(base_col, ligne_debut_ecriture + row);

			for (int col = 0; col < bpm.width; ++col) {
				uint8_t gray_val = bpm.buffer[col + row * bpm.width];
				if (gray_val != 0) {
					*dest_col_iterator = rgba8_pixel_t(gray_val, gray_val, gray_val, 255);
				}
				++dest_col_iterator;
			}
		}
		base_col += face->glyph->advance.x >> 6;
	}

	return TextDimensions(sum_width, max_height);
}