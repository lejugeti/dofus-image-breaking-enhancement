#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <boost/gil.hpp>
#include <boost/gil/io/io.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>

#include "models/text/TextDimensions.h"

using namespace boost::gil;

class TextWriter {
	
public:
	TextWriter();

	/// <summary>
	/// Ecrit un texte donn� dans une image rgba boost::gil.
	/// </summary>
	/// <param name="text">Le texte � �crire</param>
	/// <param name="img">L'image dans laquelle le texte sera �crit</param>
	/// <param name="base_col">Coordonn�e horizontale de la ligne sur laquelle le texte sera �crit</param>
	/// <param name="base_ligne">Coordonn�e vertical de la ligne sur laquelle le texte sera �crit</param>
	TextDimensions write_in_image(std::string texte, rgba8_image_t* img, int base_col, int base_ligne, int taille_pixel);
private:
	FT_Library library;
};