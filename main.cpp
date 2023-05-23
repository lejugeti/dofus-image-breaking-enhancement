#include "main.h"
#include <boost/gil/extension/io/png.hpp>

#include <boost/gil.hpp>
#include <boost/gil/io/io.hpp>
#include <boost/gil/image_view.hpp>

#include "PngEditor.h"

using namespace std;
using namespace boost::gil;

int main()
{
	cout << "Hello CMake." << endl;

	auto baseImgPath = "D:/Dev/dofus-image-breaking-enhancement/images/base.png";
	auto insertImgPath = "D:/Dev/dofus-image-breaking-enhancement/images/insert.png";

	PngEditor::insert_img(baseImgPath, insertImgPath, 200, 400);
}
