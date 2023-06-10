#pragma once

#include <iostream>

#include <boost/gil.hpp>

#include "models/images/AtelierImg.h"
#include "models/images/FenetreBrisageImg.h"

using namespace std;
using namespace boost::gil;

class PngEditor
{
public:
	static bool inserer_img(rgba8_image_t* insert_img, rgba8_image_t* base_img, int x, int y);
	static bool inserer_objet_aleatoire(FenetreBrisageImg* ihm_brisage_img);
	static bool inserer_rune_aleatoire(FenetreBrisageImg* ihm_brisage_img);
	static bool inserer_coefficient_aleatoire(FenetreBrisageImg* ihm_brisage_img);

	/// <summary>
	/// Méthode permettant de créer de bout en bout une image similaire à un screen de brisage.
	/// </summary>
	/// <param name="output_path">Le chemin où écrire l'image de sortie</param>
	/// <returns></returns>
	static bool create_atelier_img(std::string output_path);

private:
	static bool read_png_img(std::string path, rgba8_image_t* img);
	static bool write_png_img(std::string path, rgba8_image_t* img);
};