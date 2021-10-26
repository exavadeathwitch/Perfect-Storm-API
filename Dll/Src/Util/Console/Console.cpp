#include "pch.hpp"

#include "Console.hpp"

namespace util::console {
	void initialize(const std::string_view name) {
		AllocConsole();

		SetConsoleTitleA(name.data());

		freopen_s(std::bit_cast<FILE**>(stdout), "conout$", "w", stdout);
	}

	void uninitialize() {
		FreeConsole();
		fclose(stdout);
		PostMessageA(GetConsoleWindow(), WM_CLOSE, 0, 0);
	}
}