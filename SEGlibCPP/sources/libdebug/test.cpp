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
#include <org/segames/library/core.h>
#include <org\segames\library\io\file.h>

using namespace org::segames::library;
using namespace org::segames::library::io;
using namespace org::segames::library::util;
using namespace org::segames::library::math;

int main()
{
	try
	{
		File file("C:\\");

		auto files = file.listFiles();
		for (int i = 0; i < files.size(); i++)
		{
			std::cout << files.get(i) << std::endl;

			auto files2 = files.get(i).listFiles();
			for (int c = 0; c < files2.size(); c++)
				std::cout << "  " << files2.get(c) << std::endl;
		}

	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::getline(std::cin, (std::string)"");
	return 0;
}