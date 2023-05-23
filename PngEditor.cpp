#include "PngEditor.h"

#include <iostream>

#include <stdexcept>

#include <boost/gil/extension/io/png.hpp>
#include <boost/gil.hpp>
#include <boost/gil/io/io.hpp>

using namespace boost::gil;

bool PngEditor::insert_img(std::string baseImgPath, std::string insertedImgPath, int x, int y) {
	rgb8_image_t baseImg;
	read_and_convert_image(baseImgPath, baseImg, png_tag());
	rgb8_image_t insertImg;
	read_and_convert_image(insertedImgPath, insertImg, png_tag());

	if ((insertImg.width() + x) > baseImg.width() || (insertImg.height() + y) > baseImg.height()) {
		throw length_error(std::format("Can't insert image of size ({0}, {1}) beginning at ({2}, {3})", insertImg.width(), insertImg.height(), x, y));
	}
	else {		
		rgb8_view_t baseView = view(baseImg);
		rgb8_view_t insertView = view(insertImg);
		rgb8_loc_t baseLoc = baseView.xy_at(x, y);
		rgb8_loc_t insertLoc = insertView.xy_at(0, 0);

		for (int x = 0; x < insertView.width(); ++x) {
			for (int y = 0; y < insertView.height(); ++y) {
				*baseLoc = *insertLoc;
				++baseLoc.y();
				++insertLoc.y();
			}
			baseLoc += point_t(0, -insertView.height());
			insertLoc += point_t(0, -insertView.height());
			++baseLoc.x();
			++insertLoc.x();
		}

		write_view("D:/Dev/dofus-image-breaking-enhancement/images/test.png", view(baseImg), png_tag());

		return true;
	}
}

