#include "PngEditor.h"

#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <random>

#include <boost/gil.hpp>
#include <boost/gil/io/io.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>

#include "utils/FileSystemUtil.h"
#include "TextWriter.h"

using namespace boost::gil;
namespace fs = std::filesystem;

const std::string ateliers_dir = "../../../images/ateliers";
const std::string objets_dir = "../../../images/objets";
const std::string rune_dir = "../../../images/runes";

const std::string fenetre_brisage_path = "../../../images/misc/fenetre_brisage.png";
const std::string fond_objet_path = "../../../images/misc/fond_objet_brisage.png";

bool PngEditor::inserer_img(rgba8_image_t* insert_img, rgba8_image_t* base_img, int x, int y) {
	using Pixel = rgba8_image_t::value_type;

	if ((insert_img->width() + x) > base_img->width() || (insert_img->height() + y) > base_img->height()) {
		throw length_error(std::format("Can't insert image of size ({0}, {1}) beginning at ({2}, {3})", insert_img->width(), insert_img->height(), x, y));
	} else {
		auto base_sub_view = subimage_view(view(*base_img), x, y, insert_img->width(), insert_img->height());
		transform_pixels(base_sub_view, view(*insert_img), base_sub_view,
			[](Pixel const& a, Pixel const& b) {
				return get_color(b, alpha_t()) ? b : a;
			});

		return true;
	}
}

bool PngEditor::inserer_objet_aleatoire(rgba8_image_t* ihm_brisage_img) {
	std::string objet_path = FileSystemUtil::get_random_file_path_from_dir(objets_dir);

	rgba8_image_t fond_brisage;
	read_png_img(fond_objet_path, &fond_brisage);
	rgba8_image_t objet;
	read_png_img(objet_path, &objet);

	rgba8_image_t resized_objet(40, 40);
	resize_view(const_view(objet), view(resized_objet), bilinear_sampler());
	inserer_img(&resized_objet, &fond_brisage, 2, 2);

	inserer_img(&fond_brisage, ihm_brisage_img, 37, 140);

	TextWriter writer;
	writer.write_in_image("Anneau du Champ Champ", ihm_brisage_img, 91, 166, 16);

	return true;
}

bool PngEditor::inserer_rune_aleatoire(rgba8_image_t* ihm_brisage_img) {
	std::string rune_path = FileSystemUtil::get_random_file_path_from_dir(rune_dir);

	rgba8_image_t fond_brisage;
	read_png_img(fond_objet_path, &fond_brisage);
	rgba8_image_t rune;
	read_png_img(rune_path, &rune);

	rgba8_image_t resized_rune(40, 40);
	resize_view(const_view(rune), view(resized_rune), bilinear_sampler());

	TextWriter writer;
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::uniform_int_distribution<int> distribution(0, 435); // nombre maximal de rune arbitraire
	int rune_number = distribution(gen);
	writer.write_in_image(std::to_string(rune_number), &resized_rune, 0, 12, 16);

	inserer_img(&resized_rune, &fond_brisage, 2, 2);
	inserer_img(&fond_brisage, ihm_brisage_img, 516, 140);

	return true;
}

bool PngEditor::inserer_coefficient_aleatoire(rgba8_image_t* ihm_brisage_img) {
	TextWriter writer;
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::poisson_distribution<int> distribution(100); // coefficient maximal arbitraire
	int coefficient = distribution(gen);
	writer.write_in_image(std::to_string(coefficient) + " %", ihm_brisage_img, 407, 166, 16);

	return true;
}

bool PngEditor::create_atelier_img(std::string output_path) {
	using Pixel = rgba8_image_t::value_type;

	std::string atelierPath = FileSystemUtil::get_random_file_path_from_dir(ateliers_dir);
	rgba8_image_t atelier;
	read_png_img(atelierPath, &atelier);

	rgba8_image_t fenetre_brisage;
	read_png_img(fenetre_brisage_path, &fenetre_brisage);

	inserer_objet_aleatoire(&fenetre_brisage);
	inserer_rune_aleatoire(&fenetre_brisage);
	inserer_coefficient_aleatoire(&fenetre_brisage);

	inserer_img(&fenetre_brisage, &atelier, 321, 78);

	write_png_img(output_path, &atelier);
	return true;
}

bool PngEditor::read_png_img(std::string path, rgba8_image_t* img) {
	read_and_convert_image(path, *img, png_tag());
	return true;
}

bool PngEditor::write_png_img(std::string path, rgba8_image_t* img) {
	write_view(path, view(*img), png_tag());
	return true;
}