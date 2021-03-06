#include <org\segames\library\null_pointer_exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			NullPointerException::NullPointerException() :
				NullPointerException("")
			{}

			NullPointerException::NullPointerException(const std::string& message) :
				Exception(message)
			{}

		}

	}

}