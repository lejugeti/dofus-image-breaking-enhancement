#include "LabelCreator.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <regex>
#include <algorithm>
#include <vector>

#include "mappers/LabelMapper.h"

#include "models/labeling/images/Label.h"

using namespace std;

const std::string space = " ";
const std::string text_file_ext = ".txt";

LabelCreator* LabelCreator::instance = nullptr;

LabelCreator* LabelCreator::getInstance() {
	if (LabelCreator::instance == nullptr) {
		instance = new LabelCreator();
	}
	return LabelCreator::instance;
}

LabelCreator::LabelCreator() {	
	if (fs::is_regular_file(dataset_file_path)) {
		std::ifstream stream(dataset_file_path);
		const std::regex index_regex("\\d+(?=:)");
		const std::regex label_regex("[a-zA-Z_]+");

		dataset_labels = new std::set<DatasetLabel, DatasetLabelCmp>();

		std::string line;
		while (std::getline(stream, line)) {
			std::smatch match_index;
			if (std::regex_search(line, match_index, index_regex)) {
				std::smatch match_label;
				std::regex_search(line, match_label, label_regex);
				DatasetLabel label(std::stoi(match_index[0]), match_label[0]);
				dataset_labels->insert(label);
			}
		}
	}
	else {
		throw runtime_error("Le chemin vers le dataset est incorrect. Chemin actuel : " + dataset_file_path);
	}
}

LabelCreator::~LabelCreator() {
	delete LabelCreator::instance;
}

int LabelCreator::get_label_index_by_libelle(std::string label) {
	int index = -1;
	for (DatasetLabel rune_label : *dataset_labels) {
		if (label == rune_label.get_libelle()) {
			index = rune_label.get_index();
			break;
		}
	}
	return index;
}

bool LabelCreator::write_label_file(fs::path file_path, DatasetType type, vector<Label> labels) {

	ofstream label_file;
	label_file.open(file_path);

	LabelMapper mapper;
	for (Label label : labels) {
		NormalizedLabel normalized = mapper.normalize_label(label);
		int label_index = get_label_index_by_libelle(normalized.get_name());
		if (label_index < 0) {
			throw runtime_error("Le label n'a pas été trouvé dans le set de labels");
		}

		streamsize precision = cout.precision();
		label_file << setprecision(7) << label_index << space
			<< normalized.get_x() << space
			<< normalized.get_y() << space
			<< normalized.get_width() << space
			<< normalized.get_height() << space
			<< setprecision(precision) << endl;
	}
	label_file.close();
	
	return true;
}