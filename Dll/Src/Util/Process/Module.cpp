#include "pch.hpp"

#include "Module.hpp"

namespace util::process {
	Module::Module(const std::string_view name) noexcept {
		void* imageBase = GetModuleHandleA(name.data());

		if (!imageBase)
			return;

		m_Base = std::bit_cast<std::uintptr_t>(imageBase);

		m_DosHeader = static_cast<PIMAGE_DOS_HEADER>(imageBase);

		if (!m_DosHeader)
			return;

		m_NtHeaders = std::bit_cast<PIMAGE_NT_HEADERS>(static_cast<std::uint8_t*>(imageBase) + m_DosHeader->e_lfanew);

		if (!m_NtHeaders)
			return;

		const auto sections = IMAGE_FIRST_SECTION(m_NtHeaders);

		if (!sections)
			return;

		m_Size = static_cast<std::size_t>(m_NtHeaders->OptionalHeader.SizeOfImage);

		for (auto i = 0u; i < m_NtHeaders->FileHeader.NumberOfSections; ++i) {
			const auto sectionName = std::bit_cast<const char*>(&sections[i].Name);
			m_Sections[sectionName] = std::make_shared<Section>(Section(sections[i].VirtualAddress, sections[i].Misc.VirtualSize));
		}
	}

	std::uintptr_t Module::getImportedFunction(const std::string_view importedModule, const std::string_view function) const noexcept {
		auto imports = std::bit_cast<PIMAGE_IMPORT_DESCRIPTOR>(
			m_Base + m_NtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

		for (; imports->Name; ++imports) {
			if (_stricmp(std::bit_cast<const char*>(m_Base + imports->Name), importedModule.data()))
				continue;

			auto originalFirstThunk = std::bit_cast<PIMAGE_THUNK_DATA>(m_Base + imports->OriginalFirstThunk);
			auto firstThunk = std::bit_cast<PIMAGE_THUNK_DATA>(m_Base + imports->FirstThunk);

			for (; originalFirstThunk->u1.AddressOfData; ++originalFirstThunk, ++firstThunk) {

				if (originalFirstThunk->u1.Ordinal & IMAGE_ORDINAL_FLAG) {
					if (_stricmp(std::bit_cast<const char*>(originalFirstThunk->u1.Ordinal & 0xFFFF), function.data()))
						continue;
				}
				else {
						if (_stricmp(static_cast<const char*>(std::bit_cast<PIMAGE_IMPORT_BY_NAME>(
						m_Base + originalFirstThunk->u1.AddressOfData)->Name), function.data()))
							continue;
				}

				return static_cast<std::uintptr_t>(firstThunk->u1.Function);
			}
		}
		return 0u;
	}
}