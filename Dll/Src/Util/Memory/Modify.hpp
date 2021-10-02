#pragma once

#include <cstdint>
#include <windows.h>
#include <array>
#include <string>
#include <iostream>
//Modifying Bytes in Memory, reading and writing, mainly used for nopping/modifying exe code

namespace util::memory {
	class Modify {
	public:
		template <std::size_t size>
		static auto write_bytes(const std::uintptr_t start, const std::array<std::uint8_t, size>& bytes) -> bool {
			DWORD old_prot;

			if (!VirtualProtect(reinterpret_cast<void*>(start), bytes.size(), PAGE_EXECUTE_READWRITE, &old_prot))
				return false;

			for (auto i = 0u; i < bytes.size(); ++i)
				*reinterpret_cast<std::uint8_t*>(start + i) = bytes.at(i);

			VirtualProtect(reinterpret_cast<void*>(start), bytes.size(), old_prot, &old_prot);
			return true;
		}

		template<std::size_t size>
		static auto read_bytes(const std::uintptr_t address)->std::array<std::uint8_t, size> {
			std::array<std::uint8_t, size> read_bytes{};

			for (auto i = 0u; i < size; ++i)
				read_bytes[i] = *std::bit_cast<std::uint8_t*>(address + i);

			return read_bytes;
		}

		template<typename T>
		static void writePointer(const std::uintptr_t base, const std::vector<std::uintptr_t>& offsets, const T val) {
			auto tmp = base;

			for (const auto& off : offsets) {
				tmp = *reinterpret_cast<std::uintptr_t*>(tmp);

				if (!tmp)
					return;

				tmp += off;
			}

			*reinterpret_cast<T*>(tmp) = val;
		}

		static std::uintptr_t readPointer(const std::uintptr_t base, const std::vector<std::uintptr_t>& offsets) {
			auto tmp = base;

			for (const auto& off : offsets) {
				tmp = *reinterpret_cast<std::uintptr_t*>(tmp);
				
				if (!tmp)
					return 0;

				tmp += off;
			}
			//std::cout << std::hex << tmp << std::endl;
			std::dec;
			return tmp;
			//*reinterpret_cast<T*>(tmp) = val;
		}
	private:
		
	};
}
