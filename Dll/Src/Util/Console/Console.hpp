#pragma once

#include <string_view>

namespace util::console {
	void initialize(std::string_view name);
	void uninitialize();
	void debugPrint(std::string print);
}
