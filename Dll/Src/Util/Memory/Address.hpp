#pragma once

#include <bit>

namespace util::memory {

	class Address {
	public:
		Address() noexcept = default;
		~Address() noexcept = default;

		Address(const std::uintptr_t address) noexcept : m_Ptr(address) {

		}

		Address(void* const address) noexcept : m_Ptr(std::bit_cast<std::uintptr_t>(address)) {

		}

		bool isValid() const noexcept {
			return std::bit_cast<void*>(m_Ptr) != nullptr;
		}

		Address& selfGetRelative(const std::uint32_t offset = 1u) noexcept {
			m_Ptr = getRelative(offset);
			return *this;
		}

		Address& selfAddOffset(const std::uint32_t offset) noexcept {
			m_Ptr = addOffset(offset);
			return *this;
		}

		Address& selfSubOffset(const std::uint32_t offset) noexcept {
			m_Ptr = subOffset(offset);
			return *this;
		}

		std::uintptr_t getRelative(const std::uint32_t offset = 1u) const noexcept {
			std::uintptr_t dummy = m_Ptr + offset;

			const auto disp = *std::bit_cast<std::int32_t*>(dummy);

			return dummy + sizeof(std::uint32_t) + disp;
		}

		std::uintptr_t addOffset(const std::uint32_t offset) const noexcept {
			return m_Ptr + offset;
		}

		std::uintptr_t subOffset(const std::uint32_t offset) const noexcept {
			return m_Ptr - offset;
		}

		std::uintptr_t get() const noexcept {
			return m_Ptr;
		}

		template<typename T>
		T as(std::uint32_t timesToDeref = 0u) const noexcept {
			std::uintptr_t dummy = m_Ptr;

			while (timesToDeref-- != 0u)
				if (dummy)
					dummy = *std::bit_cast<std::uintptr_t*>(dummy);

			return std::bit_cast<T>(dummy);
		}
	private:
		std::uintptr_t m_Ptr;
	};
}
