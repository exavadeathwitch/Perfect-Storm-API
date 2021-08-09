#pragma once

#include <unordered_map>

namespace util::hook {
	class HookManager {
	public:
		HookManager() = default;
		~HookManager() = default;
	private:
		struct HookEntry {
			void* m_Original;
			void* m_Trampoline;
		};
	public:
		void initialize() const;
		void addEntry(std::uintptr_t original, void* detour);
		void hookEntry(void* detour);
		void unhookEntry(void* detour) noexcept;
		void hookAllEntries();
		void unhookAllEntries() noexcept;
		void uninitialize() const;

		template<typename T>
		T getOriginal(void* detour) noexcept {
			return static_cast<T>(m_Entries[detour].m_Trampoline);
		}

		template<typename T, typename ... Ts>
		decltype(auto) callOriginal(void* detour, Ts&&... args) noexcept {
			return getOriginal<T>(detour)(std::forward<Ts>(args)...);
		}
	private:
		std::unordered_map<void*, HookEntry> m_Entries;
	};
}