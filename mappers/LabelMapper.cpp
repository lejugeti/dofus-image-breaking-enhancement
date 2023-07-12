#include "LabelMapper.h"

NormalizedLabel LabelMapper::normalize_label(Label label) {
	return NormalizedLabel(
		label.get_name(),
		label.get_x(),
		label.get_y(),
		label.get_width(),
		label.get_height(),
		label.get_parent_width(),
		label.get_parent_height()
	);
}