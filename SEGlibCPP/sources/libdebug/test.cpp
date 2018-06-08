#include <iostream>
#include <sstream>
#include <cmath>

#include <thread>
#include <chrono>

#include <org\segames\library\null_pointer_exception.h>
#include <org\segames\library\util\array.h>
#include <org\segames\library\util\array_list.h>
#include <org\segames\library\util\timer.h>

using namespace org::segames::library;
using namespace org::segames::library::util;

/*
	A comment
*/

int main()
{
	try
	{

		Timer timer(1);
		Timer dt;
		while (true)
		{
			std::cout << dt.deltaTime() << std::endl;
			timer.sync();
		}
		
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::getline(std::cin, (std::string)"");
	return 0;
}