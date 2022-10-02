#include <string>

#include <stdio.h>

#include <stdlib.h>
namespace util::memory {
	class String {
	public:
		//Gets a string from a memory address.
		static std::string strFromAddr(__int64 a1) {
			const std::string state = reinterpret_cast<const char*>(a1);
			return state;
		}
		//Gets the first 5 characters from a string from a memory address.
		static std::string strFromAddrSpec(__int64 a1, int a2) {
			if (a2 <= 0)
				return "";
			std::string retval;
			const std::string state = reinterpret_cast<const char*>(a1);
			for (int i = 0; i < a2; i++) {
				retval += state[i];
			}
			return retval;
		}
			/*
			const std::size_t size = a2;
			char chars[size] = "";
			memcpy(chars, reinterpret_cast<char*>(a1), size);
			int sizeString = sizeof(chars) / sizeof(char);
			std::string name = "";
			for (std::size_t i = 0; i < sizeString; i++) {
				name = name + chars[i];
			}
			return name;
		}*/
	};
}