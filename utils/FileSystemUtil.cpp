#include "FileSystemUtil.h"

#include <filesystem>
#include <random>

namespace fs = std::filesystem;

std::default_random_engine gen;

std::string FileSystemUtil::get_random_file_path_from_dir(std::string dirPath) {
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::uniform_int_distribution<int> distribution(0, count_files_in_dir(dirPath) - 1);
	int selectedFileIndex = distribution(gen);
	
	auto iter = fs::directory_iterator(dirPath);
	int fileIndex = 0;
	for (const auto& entry : iter) {
		if (entry.is_regular_file() && fileIndex == selectedFileIndex) {
			return entry.path().string();
		}
		++fileIndex;
	}

	return nullptr;
}

int FileSystemUtil::count_files_in_dir(std::string dirPath) {
	auto fileCountIter = fs::directory_iterator(dirPath);
	int fileCount = 0;

	for (const auto& entry : fileCountIter) {
		if (fs::is_regular_file(entry)) {
			++fileCount;
		}
	}

	return fileCount;
}