#include <iostream>
#include <sstream>
#include <cmath>

#include <thread>
#include <chrono>

#include <org\segames\library\null_pointer_exception.h>
#include <org\segames\library\util\array.h>
#include <org\segames\library\util\array_list.h>

using namespace org::segames::library;
using namespace org::segames::library::util;

int main()
{
	try
	{
		{
			ArrayList<ArrayList<ArrayList<int>>> a = ArrayList<ArrayList<ArrayList<int>>>(1);

			a.add({ { 1, 2, 3 } });

		}
		
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::getline(std::cin, (std::string)"");
	return 0;
}