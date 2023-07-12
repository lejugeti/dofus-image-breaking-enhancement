#pragma once

#include <stdexcept>

class TextDimensions {
private:
	int _width, _height;

public:
	TextDimensions(int width, int height)
		: _width(width), _height(height)
	{
		if (_width < 0 or _height < 0) {
			throw std::invalid_argument("Width and height must be positive");
		}
	}

	int get_width() { return _width; }
	int get_height() { return _height; }
};