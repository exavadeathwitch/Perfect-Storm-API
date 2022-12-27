#include "pch.hpp"

namespace util::memory {
	class String {
	public:

		//Returns a string from the given memory address.
		static std::string strFromAddr(__int64 a1) {
			const std::string state = reinterpret_cast<const char*>(a1);
			return state;
		}

		//Returns the amount of characters specified from the given memory address.
		static std::string strFromAddrSpec(__int64 a1, int a2) {
			const std::size_t size = a2;
			std::vector<char> chars;
			for (int x = 0; x < a2; x++) {
				chars.push_back(*(char*)reinterpret_cast<char*>(a1 + x));
			}
			int sizeString = chars.size() / sizeof(char);
			std::string name = "";
			for (std::size_t i = 0; i < sizeString; i++) {
				name = name + chars[i];
			}
			return name;
		}
	};
}