#include <iostream>
#include <sstream>
#include <cmath>

#include <thread>
#include <chrono>

#include <org\segames\library\system.h>
#include <org\segames\library\util\string_util.h>

using namespace org::segames::library;
using namespace org::segames::library::util;

int main()
{
	try
	{
		ArrayList<std::string> arr = {
			"This",
			"is",
			"a",
			"list",
			"and",
			"it",
			"is",
			"not",
			"very",
			"long"
		};
		
		std::string myString = stringConcat("#", arr);

		auto myArr = stringSplit(myString, { "#", "i" });

		for (size_t i = 0; i < myArr.size(); i++)
			std::cout << myArr.peek(i) << std::endl;

		std::cout << "BIG_ENDIAN? " << bigEndian() << std::endl;
		
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::getline(std::cin, (std::string)"");
	return 0;
}