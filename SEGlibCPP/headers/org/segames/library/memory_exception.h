#pragma once
#include <org\segames\library\exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				An exception for memory errors, eg. malloc failure

				* @author	Philip Rosberg
				* @since	2018-05-11
				* @edited	2018-05-11
			*/
			class SEG_API MemoryException : 
				public Exception
			{
			public:

				/*
					Creates a memory exception with no message
				*/
				MemoryException();

				/*
					Creates a memory exception with the given message
					* @param[in] message The message to use for the exception
				*/
				MemoryException(const std::string& message);

			};

		}

	}

}