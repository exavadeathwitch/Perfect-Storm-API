#pragma once

#include <algorithm>

#include "Address.hpp"
#include "Signature.hpp"

#include "Util/Process/Module.hpp"

namespace util::memory {
	template<std::size_t size>
	Address findSignature(process::Module* mod, const std::array<std::uint8_t, size>& signatureBytes, const std::uintptr_t start, const std::uintptr_t end) {
		std::uint8_t* const result = std::search(std::bit_cast<std::uint8_t*>(mod->getBase() + start),
												 std::bit_cast<std::uint8_t*>(mod->getBase() + (start + (end - start))),
												 signatureBytes.data(),
												 signatureBytes.data() + size,
												 [](const std::uint8_t first, const std::uint8_t second) -> bool {return first == second || second == 0; });

		return !result ? nullptr : result;
	}
	
	template<std::size_t size>
	Address findSignature(process::Module* mod, const std::array<std::uint8_t, size>& signatureBytes, const std::string_view sectionName = ".text") {
		process::Module::Section* section = mod->getSection(sectionName);

		return findSignature<size>(mod, signatureBytes, section->m_VirtualAddress, section->m_VirtualSize);
	}
}
