#pragma once

#include <list>

#include <boost/gil.hpp>

# include "../../models/labeling/images/Label.h"


using namespace boost::gil;

class AtelierImg : public rgba8_image_t {

private:
	std::list<Label> _labels = {};

public:
	std::list<Label> get_labels() { return _labels; }
	void add_label(Label label) { _labels.push_back(label); }
};