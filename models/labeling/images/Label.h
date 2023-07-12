#pragma once

#include <string>
#include <format>
#include <stdexcept>

#include "NormalizedLabel.h"

using namespace std;

class Label {
protected:
	int _x;
	int _y;
	int _height;
	int _width;
	int _parent_width;
	int _parent_height;

	std::string _name;

	bool coordinate_is_valid(double coordinate) {
		return 0 < coordinate && coordinate < 1;
	}

public:
	int get_x() { return _x; }
	void set_x(int x) { _x = x; }

	int get_y() { return _y; }
	void set_y(int y) {	_y = y; }

	int get_height() { return _height; }
	void set_height(int height) { _height = height;	}

	int get_width() { return _width; }
	void set_width(int width) { _width = width;	}

	int get_parent_height() { return _parent_height; }
	void set_parent_height(int parent_height) {	_parent_height = parent_height; }

	int get_parent_width() { return _parent_width; }
	void set_parent_width(int parent_width) { _parent_width = parent_width;	}

	std::string get_name() { return _name; }
	void set_name(std::string name) { _name = name; }

	Label(std::string name, int x_insert, int y_insert, int width_insert, int height_insert, int parent_width, int parent_heigth)
		: _name(name), _parent_width(parent_width), _parent_height(parent_heigth)
	{
		int x = x_insert + width_insert / 2;
		int y = y_insert + height_insert / 2;
		int width = width_insert / 2;
		int height = height_insert / 2;

		set_x(x);
		set_y(y);
		set_width(width);
		set_height(height);

		if (!is_valid()) {
			throw runtime_error("Le label crée n'est pas valide");
		}
	}

	bool is_valid() {
		return _x > 0 && _y > 0 && _width > 0 && _height > 0 && _parent_width > 0 && _parent_height > 0
			&& _x < _parent_width && _y < _parent_height
			&& _x - _width >= 0 && _x + _width <= _parent_width
			&& _y - _height >= 0 && _y + _height <= _parent_height;
	}
};