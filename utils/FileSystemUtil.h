#pragma once

#include <iostream>

//using namespace std;

class FileSystemUtil
{
public:
	static std::string get_random_file_path_from_dir(std::string dirPath);
	static int count_files_in_dir(std::string dirPath);
};