#pragma once

#include <iostream>

#include <boost/gil.hpp>

using namespace std;
using namespace boost::gil;

class PngEditor
{
public:
	static bool insert_img(std::string baseImgPath, std::string insertedImgPath, int x, int y);
	static bool insert_img(rgba8_image_t* insert_img, rgba8_image_t* base_img, int x, int y);
	static bool insert_random_object(rgba8_image_t* ihm_brisage_img);
	static bool insert_random_rune(rgba8_image_t* ihm_brisage_img);
	
	static bool read_png_img(rgba8_image_t* img, std::string path);
	static bool write_png_img(rgba8_image_t* png, std::string path);

	static bool create_atelier_img();

private:
	static std::string get_random_file_path_from_dir(std::string dirPath);
};