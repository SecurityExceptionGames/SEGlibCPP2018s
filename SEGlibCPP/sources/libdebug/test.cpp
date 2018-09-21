#include <iostream>
#include <sstream>
#include <cmath>

#include <thread>
#include <chrono>

#include <org\segames\library\system.h>
#include <org\segames\library\util\string_util.h>
#include <org/segames/library/util/random.h>
#include <org\segames\library\math\vecmath.h>
#include <org\segames\library\math\math.h>

using namespace org::segames::library;
using namespace org::segames::library::util;
using namespace org::segames::library::math;

int main()
{
	try
	{
		BasicVector<double, 3> a = { 1, 0, 0 };
		BasicVector<double, 3> b = { 0, 1, 0 };

		std::cout << cross(a, b) << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::getline(std::cin, (std::string)"");
	return 0;
}