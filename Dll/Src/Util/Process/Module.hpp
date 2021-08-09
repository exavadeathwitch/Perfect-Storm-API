#pragma once

#include <memory>
#include <unordered_map>

namespace util::process {
	class Module {
	public:
		struct Section {
			std::uintptr_t m_VirtualAddress;
			std::size_t m_VirtualSize;
		};
	public:
		Module() noexcept = default;
		~Module() noexcept = default;

		explicit Module(std::string_view name) noexcept;

		std::uintptr_t getBase() const noexcept {
			return m_Base;
		}

		std::size_t getSize() const noexcept {
			return m_Size;
		}

		Section* getSection(const std::string_view name) noexcept {
			return m_Sections[name].get();
		}

		std::uintptr_t getImportedFunction(std::string_view importedModule, std::string_view function) const noexcept;
	private:
		std::uintptr_t m_Base;
		std::size_t m_Size;
		PIMAGE_DOS_HEADER m_DosHeader;
		PIMAGE_NT_HEADERS m_NtHeaders;
		std::unordered_map<std::string_view, std::shared_ptr<Section>> m_Sections;
	};
}
