#pragma once

#include <set>
#include <string>
#include <regex>
#include <filesystem>
#include <vector>

#include "models/labeling/dataset/DatasetLabel.h"
#include "models/labeling/dataset/DatasetType.h"
#include "models/labeling/images/Label.h"

using namespace std;

namespace fs = std::filesystem;

class LabelCreator {
public:
	static LabelCreator* getInstance();
	
	bool write_label_file(fs::path, DatasetType, vector<Label>);

private:
	const std::string dataset_file_path = "../../../../snapshot-detection/yolov5/dataset.yml";
	const fs::path label_out_path = "../../../../datasets/dofus-enhancement/labels";

	static LabelCreator* instance;

	struct DatasetLabelCmp {
		bool operator()(DatasetLabel a, DatasetLabel b) const
		{
			return a.get_index() < b.get_index();
		}
	};
	std::set<DatasetLabel, DatasetLabelCmp>* dataset_labels;

	LabelCreator();
	~LabelCreator();

	// prevent copying
	LabelCreator(const LabelCreator &other) = delete;
	void operator=(const LabelCreator&) = delete;

	int get_label_index_by_libelle(std::string label);
};

