#pragma once

#include <array>
#include <ranges>

namespace util::memory {
	consteval std::uint8_t getHex(const char c) {
		if (c >= '0' && c <= 9)
			return static_cast<std::uint8_t>(c) - '0';
		else if (c >= 'a' && c <= 'f')
			return static_cast<std::uint8_t>(c) - 'a' + 10;
		else if (c >= 'A' && c <= 'F')
			return static_cast<std::uint8_t>(c) - 'A' + 10;

		return std::uint8_t();
	}

	consteval std::uint8_t getByte(const char first, const char second) {
		return (getHex(first) << 4) + getHex(second);
	}

	template<std::size_t size>
	struct Signature {
		consteval Signature(const char(&data)[size]) {
			std::copy(data, data + size, m_Data.begin());
		}
		std::array<char, size> m_Data;
	};

	namespace string_literals {
		template<Signature sig>
		consteval auto operator_sig() {
			constexpr auto data = sig.m_Data;

			std::array<std::uint8_t, std::ranges::count(data, ' ') + 1> signatureBytes{};

			for (auto i = 0u, str_i = 0u; str_i < data.size() - 1; ++str_i) {
				const auto current = data[str_i];
				const auto next = data[str_i + 1];

				if (current == ' ')
					continue;

				if (current == '?') {
					signatureBytes[i] = 0;
					++i;
					++str_i;
				}
				else {
					signatureBytes[i] = getByte(current, next);
					++i;
					++str_i;
				}
			}
			return signatureBytes;
		}
	}
}


