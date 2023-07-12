#pragma once

#include <string>

#include "Label.h"

using namespace std;

class FenetreBrisageLabel: public Label {
public:
	FenetreBrisageLabel(std::string name, int x_insert, int y_insert, int width_insert, int height_insert, int parent_width, int parent_heigth)
		: Label(name, x_insert, y_insert, width_insert, height_insert, parent_width, parent_heigth)
	{}
};