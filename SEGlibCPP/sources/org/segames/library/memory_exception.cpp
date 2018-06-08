#include <org\segames\library\memory_exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{
			
			MemoryException::MemoryException() :
				MemoryException("")
			{}

			MemoryException::MemoryException(const std::string& message) :
				Exception(message)
			{}

		}

	}

}