#pragma once

#include <iostream>
#include <vector>
#include <filesystem>

#include <boost/gil.hpp>

#include "models/images/AtelierImg.h"
#include "models/images/FenetreBrisageImg.h"

#include "models/labeling/images/Label.h"
#include "models/labeling/images/RuneLabel.h"
#include "models/labeling/images/ObjetLabel.h"
#include "models/labeling/images/CoefficientLabel.h"

using namespace boost::gil;

class PngEditor
{
public:
	static bool inserer_img(rgba8_image_t* insert_img, rgba8_image_t* base_img, int x, int y);
	static ObjetLabel inserer_objet_aleatoire(FenetreBrisageImg* ihm_brisage_img);
	static RuneLabel inserer_rune_aleatoire(FenetreBrisageImg* ihm_brisage_img);
	static CoefficientLabel inserer_coefficient_aleatoire(FenetreBrisageImg* ihm_brisage_img);

	/// <summary>
	/// Méthode permettant de créer de bout en bout une image similaire à un screen de brisage.
	/// </summary>
	/// <param name="output_path">Le chemin où écrire l'image de sortie</param>
	/// <returns></returns>
	static vector<Label> create_atelier_img(std::filesystem::path);

private:
	static bool read_png_img(std::filesystem::path path, rgba8_image_t* img);
	static bool write_png_img(std::filesystem::path path, rgba8_image_t* img);
	
	static void descope_label(Label* label, int current_parent_insert_x, int current_parent_insert_y, int new_parent_width, int new_parent_height);
};