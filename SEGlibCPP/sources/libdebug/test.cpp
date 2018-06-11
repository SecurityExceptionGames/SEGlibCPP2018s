#include <iostream>
#include <sstream>
#include <cmath>

#include <thread>
#include <chrono>

#include <org\segames\library\null_pointer_exception.h>
#include <org\segames\library\util\array.h>
#include <org\segames\library\util\array_list.h>
#include <org\segames\library\util\timer.h>
#include <org\segames\library\util\thread.h>

using namespace org::segames::library;
using namespace org::segames::library::util;

/*
	A comment
*/

class A :
	public Runnable
{

	void run()
	{
		std::cout << "This" << " is " << "working" << std::endl;
		std::cout << "This" << " is " << "working" << std::endl;
		std::cout << "This" << " is " << "working" << std::endl;
		std::cout << "This" << " is " << "working" << std::endl;
		std::cout << "This" << " is " << "working" << std::endl;
		std::cout << "This" << " is " << "working" << std::endl;
	}

};

int main()
{
	try
	{

		A a;
		Thread myThread(&a);

		myThread.start();
		std::cout << "A very long" << " string that will" << " hopefully conflict with the thread." << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::getline(std::cin, (std::string)"");
	return 0;
}