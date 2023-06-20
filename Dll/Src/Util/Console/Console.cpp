#include "pch.hpp"

#include "Console.hpp"

namespace util::console {
	void initialize(const std::string_view name) {
		AllocConsole();

		SetConsoleTitleA(name.data());
		FILE* file = nullptr;
		freopen_s(&file, "CONIN$", "r", stdin);
		freopen_s(&file, "CONOUT$", "w", stdout);
	}

	void uninitialize() {
		FreeConsole();
		fclose(stdout);
		PostMessageA(GetConsoleWindow(), WM_CLOSE, 0, 0);
	}
}
