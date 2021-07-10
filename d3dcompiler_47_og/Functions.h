#ifndef FUNCTIONS_H 
#define FUNCTIONS_H

#include <Windows.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>

namespace moddingApi
{

	class Functions
	{
	public:
		static unsigned int str2int(std::string_view str, int h = 0);
	};
}
#endif