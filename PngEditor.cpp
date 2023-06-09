#include "PngEditor.h"

#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <random>
#include <regex>
#include <vector>

#include <boost/gil.hpp>
#include <boost/gil/io/io.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>

#include "utils/FileSystemUtil.h"
#include "TextWriter.h"

#include "models/labeling/images/Label.h"
#include "models/labeling/images/RuneLabel.h"
#include "models/labeling/images/ObjetLabel.h"
#include "models/labeling/images/CoefficientLabel.h"
#include "models/labeling/images/FenetreBrisageLabel.h"

#include "models/text/TextDimensions.h"

using namespace boost::gil;
namespace fs = std::filesystem;

const std::string ateliers_dir = "../../../images/ateliers";
const std::string objets_dir = "../../../images/objets";
const std::string rune_dir = "../../../images/runes";

const std::string fenetre_brisage_path = "../../../images/misc/fenetre_brisage.png";
const std::string fond_objet_path = "../../../images/misc/fond_objet_brisage.png";

const std::string fenetre_brisage_name = "fenetre_brisage";
const std::string objet_label_name = "objet";
const std::string coefficient_label_name = "coefficient";

const int coefficient_font_size = 16;

const int max_rune_number = 435; // nombre maximal de rune arbitraire
const int rune_img_width = 40;
const int rune_img_height = 40;
const int objet_img_width = 40;
const int objet_img_height = 40;

const int x_insert_ihm_in_atelier = 321;
const int y_insert_ihm_in_atelier = 78;
const int x_insert_rune_in_window = 516;
const int y_insert_rune_in_window = 140;
const int x_insert_objet_in_window = 37;
const int y_insert_objet_in_window = 140;
const int x_insert_coefficient_in_window = 407;
const int y_insert_coefficient_in_window = 166;

const std::regex img_name_regex("\\w+(?=.png)");

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

ObjetLabel PngEditor::inserer_objet_aleatoire(FenetreBrisageImg* ihm_brisage_img) {
	std::string objet_path = FileSystemUtil::get_random_file_path_from_dir(objets_dir);

	rgba8_image_t fond_brisage;
	read_png_img(fond_objet_path, &fond_brisage);
	rgba8_image_t objet;
	read_png_img(objet_path, &objet);

	rgba8_image_t resized_objet(objet_img_width, objet_img_height);
	resize_view(const_view(objet), view(resized_objet), bilinear_sampler());
	inserer_img(&resized_objet, &fond_brisage, 2, 2);

	inserer_img(&fond_brisage, ihm_brisage_img, x_insert_objet_in_window, y_insert_objet_in_window);

	TextWriter writer;
	std::smatch img_name_match;
	std::regex_search(objet_path, img_name_match, img_name_regex);
	std::string objet_name = img_name_match[0];
	writer.write_in_image(objet_name, ihm_brisage_img, 91, 166, 16);

	return ObjetLabel(objet_label_name, x_insert_objet_in_window, y_insert_objet_in_window, objet_img_width, objet_img_height, ihm_brisage_img->width(), ihm_brisage_img->height());
}

RuneLabel PngEditor::inserer_rune_aleatoire(FenetreBrisageImg* ihm_brisage_img) {
	std::string rune_path = FileSystemUtil::get_random_file_path_from_dir(rune_dir);

	rgba8_image_t fond_brisage;
	read_png_img(fond_objet_path, &fond_brisage);
	rgba8_image_t rune;
	read_png_img(rune_path, &rune);

	rgba8_image_t resized_rune(rune_img_width, rune_img_height);
	resize_view(const_view(rune), view(resized_rune), bilinear_sampler());

	TextWriter writer;
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::uniform_int_distribution<int> distribution(0, max_rune_number);
	int rune_number = distribution(gen);
	writer.write_in_image(std::to_string(rune_number), &resized_rune, 0, 12, 16);

	inserer_img(&resized_rune, &fond_brisage, 2, 2);
	inserer_img(&fond_brisage, ihm_brisage_img, x_insert_rune_in_window, y_insert_rune_in_window);

	std::smatch img_name_match;
	std::regex_search(rune_path, img_name_match, img_name_regex);
	std::string rune_name = img_name_match[0];

	return RuneLabel(rune_name, x_insert_rune_in_window, y_insert_rune_in_window, rune_img_width, rune_img_height, ihm_brisage_img->width(), ihm_brisage_img->height());
}

CoefficientLabel PngEditor::inserer_coefficient_aleatoire(FenetreBrisageImg* ihm_brisage_img) {
	TextWriter writer;
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::poisson_distribution<int> distribution(100); // coefficient maximal arbitraire
	int coefficient = distribution(gen);
	TextDimensions dimensions = writer.write_in_image(std::to_string(coefficient) + " %", ihm_brisage_img,
		x_insert_coefficient_in_window, y_insert_coefficient_in_window, coefficient_font_size);

	return CoefficientLabel(coefficient_label_name, x_insert_coefficient_in_window, y_insert_coefficient_in_window,
		dimensions.get_width(), dimensions.get_height(), ihm_brisage_img->width(), ihm_brisage_img->height());
}

vector<Label> PngEditor::create_atelier_img(fs::path output_path) {
	using Pixel = rgba8_image_t::value_type;

	std::string atelierPath = FileSystemUtil::get_random_file_path_from_dir(ateliers_dir);
	AtelierImg atelier;
	read_png_img(atelierPath, &atelier);

	FenetreBrisageImg fenetre_brisage;
	read_png_img(fenetre_brisage_path, &fenetre_brisage);

	Label objet_label = inserer_objet_aleatoire(&fenetre_brisage);
	Label rune_label = inserer_rune_aleatoire(&fenetre_brisage);
	Label coefficient_label = inserer_coefficient_aleatoire(&fenetre_brisage);
	
	inserer_img(&fenetre_brisage, &atelier, x_insert_ihm_in_atelier, y_insert_ihm_in_atelier);
	FenetreBrisageLabel ihm_label(fenetre_brisage_name, x_insert_ihm_in_atelier, y_insert_ihm_in_atelier,
		fenetre_brisage.width(), fenetre_brisage.height(), atelier.width(), atelier.height());

	descope_label(&objet_label, x_insert_ihm_in_atelier, y_insert_ihm_in_atelier,
		atelier.width(), atelier.height());
	descope_label(&rune_label, x_insert_ihm_in_atelier, y_insert_ihm_in_atelier,
		atelier.width(), atelier.height());

	write_png_img(output_path, &atelier);
	
	vector<Label> labels = { ihm_label, objet_label, rune_label, coefficient_label };

	return labels;
}

bool PngEditor::read_png_img(std::filesystem::path path, rgba8_image_t* img) {
	read_and_convert_image(path, *img, png_tag());
	return true;
}

bool PngEditor::write_png_img(fs::path path, rgba8_image_t* img) {
	write_view(path, view(*img), png_tag());
	return true;
}

void PngEditor::descope_label(Label* label, int current_parent_x, int current_parent_y, int new_parent_width, int new_parent_height) {
	int x_descoped = label->get_x() + current_parent_x;
	int y_descoped = label->get_y() + current_parent_y;

	label->set_x(x_descoped);
	label->set_y(y_descoped);
	label->set_parent_width(new_parent_width);
	label->set_parent_height(new_parent_height);

	if (!label->is_valid()) {
		throw runtime_error("Le label descope n'est pas valide");
	}
}