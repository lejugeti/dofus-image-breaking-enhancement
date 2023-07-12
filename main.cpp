#include "main.h"

#include <windows.h>
#include <vector>
#include <filesystem>
#include <boost/gil.hpp>

#include "PngEditor.h"
#include "TextWriter.h"
#include "utils/FileSystemUtil.h"
#include "LabelCreator.h"

#include "models/labeling/dataset/DatasetType.h"
#include "models/labeling/images/Label.h"

using namespace boost::gil;

using std::cout;

namespace fs = std::filesystem;

const fs::path output_path = "../../../../datasets/dofus-enhancement";
const fs::path labels_dir = "labels";
const fs::path img_dir = "images";

const std::string txt_ext = ".txt";
const std::string png_ext = ".png";

// Changer le type de dataset pour créer des images/labels pour 
// les différents datasets
const DatasetType type = DatasetType::TRAIN;
const int generation_number = 1;

int main()
{
	cout << "Breaking image generator running" << endl;
	cout << "Generations number = " << generation_number << endl;

	fs::path dataset_type_dir;
	switch (type) {
	case DatasetType::TRAIN: dataset_type_dir = "train"; break;
	case DatasetType::VAL: dataset_type_dir = "val"; break;
	case DatasetType::TEST: dataset_type_dir = "test"; break;
	}

	for (int gen_index = 0; gen_index < generation_number; ++gen_index) {
		const fs::path img_out = output_path / img_dir / dataset_type_dir / (std::to_string(gen_index) + png_ext);
		vector<Label> labels = PngEditor::create_atelier_img(img_out);
		
		fs::path label_out = output_path / labels_dir / dataset_type_dir / (std::to_string(gen_index) + txt_ext);
		LabelCreator::getInstance()->write_label_file(label_out, DatasetType::TRAIN, labels);
		cout << "\rAvancement : " << gen_index + 1 << " / " << generation_number;
	}

	cout << "\n\nGeneration terminee" << endl;
}
