#include "main.h"

#include <windows.h>

#include "PngEditor.h"
#include "TextWriter.h"
#include "utils/FileSystemUtil.h"

#include <boost/gil.hpp>

using namespace std;
using namespace boost::gil;

int main()
{
	auto output_path = "../../../images/out/";

	int generation_number = 2;
	cout << "Breaking image generator running" << endl;
	cout << "Generations number = " << generation_number << endl;

	for (int gen_index = 0; gen_index < generation_number; ++gen_index) {
		PngEditor::create_atelier_img(output_path + std::to_string(gen_index) + ".png");
		cout << "\rAvancement : " << gen_index + 1 << " / " << generation_number;
	}

	cout << "\n\nGeneration terminee" << endl;
}
