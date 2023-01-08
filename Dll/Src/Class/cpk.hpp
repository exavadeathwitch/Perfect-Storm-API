#pragma once

#include "pch.hpp"

class cpk
{
public:
	cpk(std::string name, int priority) {
		if (priority > 20)
			priority = 20;
		if (priority < 0)
			priority = 0;
		this->name = name;
		this->priority = priority;
	}
	cpk() {
		this->name = "";
		this->priority = 0;
	}
	std::string getname() {
		return this->name;
	}
	int getpriority() {
		return this->priority;
	}
	void setname(std::string name) {
		this->name = name;
	}
	void setpriority(int priority) {
		if (priority > 20)
			priority = 20;
		if (priority < 0)
			priority = 0;
		this->priority = priority;
	}
private:
	std::string name;
	int priority;
};