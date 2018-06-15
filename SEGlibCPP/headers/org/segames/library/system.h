#pragma once

namespace org
{

	namespace segames
	{

		namespace library
		{

			/*
				Returns true if the system is big endian and false if the system is little endian
			*/
			constexpr inline bool bigEndian()
			{
				size_t v = 1;
				return *((char*)&v) != 1;
			}

		}

	}

}