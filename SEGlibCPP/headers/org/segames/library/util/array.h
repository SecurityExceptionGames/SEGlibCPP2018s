#pragma once
#include <org\segames\library\util\collection.h>

#include <initializer_list>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{

				/*
					Standard array class with fixed boundaries

					* @author	Philip Rosberg
					* @since	2018-05-28
					* @edited	2018-05-28
				*/
				template<class T> class Array :
					public Collection<T>
				{
				public:

					/*
						Creates an empty array
					*/
					Array() :
						Collection<T>()
					{}
					
					/*
						Creates an array with the given size
						* @param[in] size The size of the array
					*/
					Array(const size_t size) :
						Collection<T>(size)
					{}

					/*
						Array collection copy constructor
						* @param[in] obj The collection to copy from
					*/
					Array(const Collection<T>& obj) :
						Collection<T>(obj)
					{}

					/*
						Creates an array with the given elements
						* @param[in] list The initializer list with values
					*/
					Array(const std::initializer_list<T>& list) :
						Collection<T>(list.size())
					{
						if (memory.isPrimitive())
							memcpy(memory.getPointer(), list.begin(), memory.getNativeSize());
						else
							std::copy(list.begin(), list.end(), stdext::checked_array_iterator<T*>(memory.getPointer(), memory.getSize()));
					}

					/*
						Returns the length/size of the array
					*/
					virtual size_t length() const noexcept
					{
						return size();
					}

					/*
						Returns a reference to the index at the given position, same as get()
					*/
					virtual T& operator[](const size_t index)
					{
						return get(index);
					}

				};

			}

		}

	}

}