#include "pch.hpp"

#include "gInput.hpp"

#include "Util/Memory/Modify.hpp"

#include <iostream>
int gInput::functions::getMenuInput() {
	int input = 0;
	std::uintptr_t retval = util::memory::Modify::readPointer((std::uintptr_t)(globals::moduleBase + 0x016BF5A8), { 0x0, 0x8, 0x3C8, 0x5F8, 0x160 });
	if (retval != 0) {
		input = *(uint8_t*)(retval + 0x1);
		//std::cout << input << std::endl;
		return input;
	}
	else
		return 0;
		
}