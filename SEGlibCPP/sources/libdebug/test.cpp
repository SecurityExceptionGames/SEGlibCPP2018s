#include <iostream>
#include <sstream>
#include <cmath>

#include <thread>
#include <chrono>

#include <org\segames\library\system.h>
#include <org\segames\library\util\string_util.h>
#include <org\segames\library\math\vecmath.h>

using namespace org::segames::library;
using namespace org::segames::library::util;
using namespace org::segames::library::math;

int main()
{
	try
	{
		vec2 a = { 0, 1 };
		Vectorf<2> b = { 0, 1 };

		BasicMatrix<double, 2, 2> mat = {
			{3, 0},
			{0, 3}
		};

		std::cout << ((BasicMatrix<char, 2, 2>)mat) << std::endl;

	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::getline(std::cin, (std::string)"");
	return 0;
}