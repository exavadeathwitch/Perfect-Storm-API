#include <iostream>
#include <string>

#include "Functions.h"

unsigned int moddingApi::Functions::str2int(std::string_view str, int h)
{
	return !str[h] ? 5381 : (moddingApi::Functions::str2int(str, h + 1) * 33) ^ str[h];
}
