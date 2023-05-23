#include <iostream>

#include <boost/gil.hpp>

using namespace std;
using namespace boost::gil;

class PngEditor
{
public:
	static bool insert_img(std::string baseImgPath, std::string insertedImgPath, int x, int y);
};