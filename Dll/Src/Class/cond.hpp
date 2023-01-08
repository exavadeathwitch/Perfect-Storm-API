#pragma once

#include "pch.hpp"

class specialcond
{
public:
	specialcond(int charcode, int condcharcode) {
		this->charcode = charcode;
		this->condcharcode = condcharcode;
	}
	specialcond() {
		this->charcode = 0;
		this->condcharcode = 0;
	}
	int getcharcode() {
		return this->charcode;
	}
	int getcondcharcode() {
		return this->condcharcode;
	}
	void setcharcode(int charcode) {
		this->charcode = charcode;
	}
	void setcondcharcode(int condcharcode) {
		this->condcharcode = condcharcode;
	}
private:
	int charcode;
	int condcharcode;
};

class partnercond
{
public:
	partnercond(int charcode, int condcharcode, int partnercharcode) {
		this->charcode = charcode;
		this->condcharcode = condcharcode;
		this->partnercharcode = partnercharcode;
	}
	partnercond() {
		this->charcode = 0;
		this->condcharcode = 0;
		this->partnercharcode = 0;
	}
	int getcharcode() {
		return this->charcode;
	}
	int getcondcharcode() {
		return this->condcharcode;
	}
	int getpartnercharcode() {
		return this->partnercharcode;
	}
	void setcharcode(int charcode) {
		this->charcode = charcode;
	}
	void setcondcharcode(int condcharcode) {
		this->condcharcode = condcharcode;
	}
	void setpartnercharcode(int partnercharcode) {
		this->partnercharcode = partnercharcode;
	}
private:
	int charcode;
	int condcharcode;
	int partnercharcode;
};