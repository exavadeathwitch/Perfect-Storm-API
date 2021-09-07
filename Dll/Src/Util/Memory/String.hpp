#include <string>

namespace util::memory {
	class String {
	public:
		//Gets a string from a memory address.
		std::string strFromAddr(__int64 a1) {
			const std::string state = reinterpret_cast<const char*>(a1);
			return state;
		}
		//Gets the first 2 characters of a string from a memory address.
		std::string strFromAddrSmall(__int64 a1) {
			const std::size_t size = 2;
			char chars[size] = "";
			memcpy(chars, reinterpret_cast<char*>(a1), size);
			int sizeString = sizeof(chars) / sizeof(char);
			std::string name = "";
			for (std::size_t i = 0; i < sizeString; i++) {
				name = name + chars[i];
			}
			return name;
		}
	};
}