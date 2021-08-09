#include "pch.hpp"

#include "Hooks/Hooks.hpp"

#include "Globals.hpp"

#include "Util/Memory/Memory.hpp"

#include "Util/Console/Console.hpp"

DWORD __stdcall modEntry(void* const imageBase) {
    util::console::initialize("lol");

    printf_s("[+] init\n");

    if (!sdk::game::initialize())
        std::abort();

    hooks::initialize();

    while (!GetAsyncKeyState(VK_END))
        Sleep(50);

    hooks::uninitialize();
    util::console::uninitialize();

    FreeLibraryAndExitThread(static_cast<HMODULE>(imageBase), EXIT_SUCCESS);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);

        if (const HANDLE thread = CreateThread(nullptr, 0, modEntry, hModule, 0, nullptr))
            CloseHandle(thread);
    }
    return TRUE;
}

