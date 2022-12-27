#include "pch.hpp"

#include "Console.hpp"

#include "Core/SDK/Game.hpp"

namespace util::console {
	void initialize(const std::string_view name) {
		if (!sdk::game::debugPrint)
			return;
		AllocConsole();

		SetConsoleTitleA(name.data());

		freopen_s(std::bit_cast<FILE**>(stdout), "conout$", "w", stdout);

		debugPrint("[+] init\n");
	}

	void debugPrint(std::string print) {
		if (sdk::game::debugPrint)
			printf_s(print.c_str());
	}

	void uninitialize() {
		FreeConsole();
		fclose(stdout);
		PostMessageA(GetConsoleWindow(), WM_CLOSE, 0, 0);
	}
}
