#pragma once

#include "pch.hpp"

class message
{
	public:
		message(std::string original, std::string converted) {
			this->original = original;
			this->converted = converted;
		}
		message() {
			this->original = "";
			this->converted = "";
		}
		std::string getoriginal() {
			return this->original;
		}
		std::string getconverted() {
			return this->converted;
		}
		void setoriginal(std::string original) {
			this->original = original;
		}
		void setconverted(std::string converted) {
			this->converted = converted;
		}
	private:
		std::string original;
		std::string converted;
};