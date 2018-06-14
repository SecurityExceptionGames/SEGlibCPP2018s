#pragma once
#include <org\segames\library\object.h>

#ifndef SEG_API_DIR_SEPARATOR
#ifdef _WIN32
#define SEG_API_DIR_SEPARATOR '\\'
#else
#define SEG_API_DIR_SEPARATOR '/'
#endif
#endif // !SEG_API_DIR_SEPARATOR

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace io
			{

				/*
					A class storing the attributes of a file, initialized on creation

					* @author	Philip Rosberg
					* @since	2018-06-13
					* @edited	2018-06-13
				*/
				class SEG_API FileAttributes :
					public Object
				{
				protected:

					/*
						True if the file exists
					*/
					bool existsAttr;

					/*
						True if the file is a directory
					*/
					bool dirAttrib;

					/*
						The length/size of the file
					*/
					size_t lengthAttrib;

					/*
						The file path
					*/
					std::string pathAttrib;

					//ArrayList<std::string> 

				};

				class SEG_API File :
					public Object
				{
				protected:


				};

			}

		}

	}

}