#include "main.h"

#include <windows.h>

#include "PngEditor.h"
#include "TextWriter.h"
#include "utils/FileSystemUtil.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;

	auto baseImgPath = "../../../images/base.png";
	auto insertImgPath = "../../../images/insert.png";
	auto ateliersPath = "../../../images/ateliers";

	//PngEditor::create_atelier_img();
	TextWriter writer;
	writer.write();
}
