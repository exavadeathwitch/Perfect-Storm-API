#pragma once

#include "pch.hpp"

class Mod {
public:
	std::string name;
	std::string directory;
	std::string author;
	std::string path;
	HINSTANCE dll;
	int priority;
	int type; //0 for old, 1 for new
	Mod() {
		this->name = "";
		this->directory = "";
		this->author = "";
		this->priority = 1;
		this->type = 0;
		this->path = "";
		this->dll = NULL;
	}
	Mod(std::string name, std::string directory, std::string author, int priority, int type, std::string path) {
		this->name = name;
		this->directory = directory;
		this->author = author;
		this->priority = priority;
		this->type = type;
		this->path = path;
		this->dll = NULL;
	}
};

class Plugin {

};