#pragma once

#include <iostream>

using namespace std;

class DatasetLabel {
public:
	DatasetLabel(int index, std::string libelle) 
		: _index(index), _libelle(libelle) 
	{};

	int get_index() { return _index; }
	std::string get_libelle() { return _libelle; }

private:
	int _index;
	std::string _libelle;
};