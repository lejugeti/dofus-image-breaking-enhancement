#pragma once

#include <string>
#include <format>
#include <stdexcept>

#include "Label.h"

using namespace std;

class NormalizedLabel {
private:
	double _x;
	double _y;
	double _height;
	double _width;

	std::string _name;

	bool coordinate_is_valid(double coordinate) {
		return 0 < coordinate && coordinate < 1;
	}

public:
	double get_x() { return _x; }
	void set_x(double x) { _x = x; }

	double get_y() { return _y; }
	void set_y(double y) {	_y = y; }

	double get_height() { return _height; }
	void set_height(double height) { _height = height;	}

	double get_width() { return _width; }
	void set_width(double width) { _width = width;	}

	std::string get_name() { return _name; }
	void set_name(std::string name) { _name = name; }

	NormalizedLabel(std::string name, int x, int y, int width, int height, int parent_width, int parent_height)
		: _name(name)
	{
		_x = (double)x / (double)parent_width;
		_y = (double)y / (double)parent_height;
		_width = (double)width / (double)parent_width;
		_height = (double)height / (double)parent_height;

		if (!is_valid()) {
			throw runtime_error("Le label crée n'est pas valide");
		}
	}

	bool is_valid() {
		return _x >= 0 && _y >= 0 && _width >= 0 && _height >= 0
			&& _x <= 1 && _y <= 1 && _width <= 1 && _height <= 1
			&& _x - _width >= 0 && _x + _width <= 1
			&& _y - _height >= 0 && _y + _height <= 1;
	}
};