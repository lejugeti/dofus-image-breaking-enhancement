#include "PngEditor.h"

#include <iostream>
#include <filesystem>
#include <stdexcept>

#include <boost/gil.hpp>
#include <boost/gil/io/io.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>

#include "utils/FileSystemUtil.h"

using namespace boost::gil;
namespace fs = std::filesystem;

const std::string ateliers_dir = "../../../images/ateliers";
const std::string objets_dir = "../../../images/objets";
const std::string rune_dir = "../../../images/runes";

const std::string fenetre_brisage_path = "../../../images/misc/fenetre_brisage.png";
const std::string fond_objet_path = "../../../images/misc/fond_objet_brisage.png";

bool PngEditor::insert_img(std::string baseImgPath, std::string insertedImgPath, int x, int y) {
	rgba8_image_t baseImg;
	read_and_convert_image(baseImgPath, baseImg, png_tag());
	rgba8_image_t insertImg;
	read_and_convert_image(insertedImgPath, insertImg, png_tag());

	if ((insertImg.width() + x) > baseImg.width() || (insertImg.height() + y) > baseImg.height()) {
		throw length_error(std::format("Can't insert image of size ({0}, {1}) beginning at ({2}, {3})", insertImg.width(), insertImg.height(), x, y));
	}
	else {		
		rgba8_view_t baseView = view(baseImg);
		rgba8_view_t insertView = view(insertImg);

		copy_pixels(insertView, subimage_view(baseView, x, y, insertView.width(), insertView.height()));
		
		write_view("../../../images/test.png", view(baseImg), png_tag());

		return true;
	}
}

bool PngEditor::insert_img(rgba8_image_t* insert_img, rgba8_image_t* base_img, int x, int y) {
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

bool PngEditor::insert_random_object(rgba8_image_t* ihm_brisage_img) {
	std::string objet_path = FileSystemUtil::get_random_file_path_from_dir(objets_dir);

	rgba8_image_t fond_brisage;
	read_and_convert_image(fond_objet_path, fond_brisage, png_tag());
	rgba8_image_t objet;
	read_and_convert_image(objet_path, objet, png_tag());
	
	rgba8_image_t resized_objet(40, 40);
	resize_view(const_view(objet), view(resized_objet), bilinear_sampler());
	insert_img(&resized_objet, &fond_brisage, 2, 2);

	insert_img(&fond_brisage, ihm_brisage_img, 37, 140);
	return true;
}

bool PngEditor::insert_random_rune(rgba8_image_t* ihm_brisage_img) {
	std::string rune_path = FileSystemUtil::get_random_file_path_from_dir(rune_dir);

	rgba8_image_t fond_brisage;
	read_and_convert_image(fond_objet_path, fond_brisage, png_tag());
	rgba8_image_t rune;
	read_and_convert_image(rune_path, rune, png_tag());

	rgba8_image_t resized_rune(40, 40);
	resize_view(const_view(rune), view(resized_rune), bilinear_sampler());
	insert_img(&resized_rune, &fond_brisage, 2, 2);

	insert_img(&fond_brisage, ihm_brisage_img, 516, 140);

	return true;
}


bool PngEditor::read_png_img(rgba8_image_t* img, std::string path) {
	read_and_convert_image(path, *img, png_tag());
	return true;
}

bool PngEditor::write_png_img(rgba8_image_t* png, std::string path) {
	write_view(path, view(*png), png_tag());
	return true;
}

bool PngEditor::create_atelier_img() {
	using Pixel = rgba8_image_t::value_type;

	std::string atelierPath = FileSystemUtil::get_random_file_path_from_dir(ateliers_dir);
	rgba8_image_t atelier;
	read_and_convert_image(atelierPath, atelier, png_tag());

	rgba8_image_t fenetre_brisage;
	read_and_convert_image(fenetre_brisage_path, fenetre_brisage, png_tag());

	insert_random_object(&fenetre_brisage);
	insert_random_rune(&fenetre_brisage);
	insert_img(&fenetre_brisage, &atelier, 321, 78);

	// TODO : calculer le nom de l'image. Surtout si le nom existe déjà
	//std::string resultOutPath = "";
	//write_png_img(atelier, resultOutPath);
	std::string resultOutPath = "../../../images/out/atelier_entier_test.png";
	write_png_img(&atelier, resultOutPath);
	return true;
}
