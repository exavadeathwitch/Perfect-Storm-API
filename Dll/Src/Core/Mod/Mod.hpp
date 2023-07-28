#pragma once

#include "pch.hpp"

typedef enum ModType {
	OLD = 0,
	NEW = 1
} ModType;

class Mod {
public:
	Mod() {
		this->name = "";
		this->description = "";
		this->directory = "";
		this->author = "";
		this->priority = 1;
		this->type = ModType::OLD;
		this->path = "";
		this->dll = NULL;
	}

	Mod(std::string name, std::string description, std::string directory, std::string author, int priority, ModType type, std::string path) {
		this->name = name;
		this->description = description;
		this->directory = directory;
		this->author = author;
		this->priority = priority;
		this->type = type;
		this->path = path;
		this->dll = NULL;
	}

	std::string name;
	std::string description;
	std::string directory;
	std::string author;
	std::string path;
	HINSTANCE dll;
	int priority;
	ModType type;
};