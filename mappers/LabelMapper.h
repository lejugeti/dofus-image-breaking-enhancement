#pragma once

#include "../models/labeling/images/Label.h"
#include "../models/labeling/images/NormalizedLabel.h"

class LabelMapper {
public:
	NormalizedLabel normalize_label(Label label);
};