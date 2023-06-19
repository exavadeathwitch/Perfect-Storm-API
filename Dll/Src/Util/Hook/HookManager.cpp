#include "pch.hpp"
#include "HookManager.hpp"

#include <minhook/include/MinHook.h>

namespace util::hook {

	void HookManager::initialize() const {
		try {
			if (MH_Initialize() != MH_OK)
				throw std::runtime_error("MinHook initialization failed.");
		}
		catch (const std::runtime_error& e) {
			MessageBoxA(nullptr, e.what(), "Runtime error", MB_ICONERROR | MB_OK);
		}
	}

	void HookManager::addEntry(const std::uintptr_t original, void* detour) {
		m_Entries[detour] = {.m_Original = std::bit_cast<void*>(original)};

		try {
			if (MH_CreateHook(m_Entries[detour].m_Original, detour, &m_Entries[detour].m_Trampoline) != MH_OK)
				throw std::runtime_error(std::format("Failed to add hook entry @ 0x{:x}.", std::bit_cast<std::uintptr_t>(m_Entries[detour].m_Original)));
		}
		catch (const std::runtime_error& e) {
			MessageBoxA(nullptr, e.what(), "Runtime error", MB_ICONERROR | MB_OK);
		}
	}

	void HookManager::hookEntry(void* detour) {
		try {
			if (MH_EnableHook(m_Entries[detour].m_Original) != MH_OK) {
				throw std::runtime_error(std::format("Failed to enable hook entry @ 0x{:x}.", std::bit_cast<std::uintptr_t>(m_Entries[detour].m_Original)));
			}
		}
		catch (const std::runtime_error& e) {
			MessageBoxA(nullptr, e.what(), "Runtime error", MB_ICONERROR | MB_OK);
		}
	}

	void HookManager::unhookEntry(void* detour) noexcept {
		MH_DisableHook(m_Entries[detour].m_Original);

		m_Entries.erase(detour);
	}

	void HookManager::hookAllEntries() {
		MH_EnableHook(MH_ALL_HOOKS);
	}

	void HookManager::unhookAllEntries() noexcept {
		MH_DisableHook(MH_ALL_HOOKS);

		MH_Uninitialize();
	}

	void HookManager::uninitialize() const {
		MH_Uninitialize();
	}
}