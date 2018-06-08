#pragma once
#include <org\segames\library\util\pointer_iterator.h>
#include <org\segames\library\index_out_of_bounds_exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{

				/*
					A checked version of the pointer iterator, ie. it stores an upper limit

					* @author	Philip Rosberg
					* @since	2018-05-17
					* @edited	2018-05-17
				*/
				template<class T> class CheckedPointerIterator : 
					public PointerIterator<T>
				{
				public:
					typedef T value_type;
					typedef T* pointer;
					typedef T& reference;
					typedef std::ptrdiff_t difference_type;
					typedef std::forward_iterator_tag iterator_category;

				protected:
					
					/*
						The current pointer positions
					*/
					size_t position;

					/*
						The upper pointer limit
					*/
					size_t upperLimit;

				public:
					
					/*
						Creates a zeroed checked pointer iterator
					*/
					CheckedPointerIterator() :
						PointerIterator<T>(),
						position(ZERO),
						upperLimit(ZERO)
					{}

					/*
						Creates a pointer iterator with checked upper bound
						* @param[in] cpos The current pointer position, must be less than upper
						* @param[in] upper The upper pointer value, ie. the end value not the last
						* @param[in] point The current pointer
					*/
					CheckedPointerIterator(const size_t cpos, const size_t upper, const T* point) :
						PointerIterator<T>(point),
						position(cpos),
						upperLimit(upper)
					{
						if (cpos > upper)
							throw IndexOutOfBoundsException("Pointer position exceeds the upper limit on construction.");
					}

					/*
						Returns true if the iterator has a next iterator step
					*/
					virtual bool hasNext() const noexcept
					{
						return (position + 1) < upperLimit;
					}

					/*
						Moves the iterator one step
					*/
					virtual void next()
					{
						if ((position + 1) > upperLimit)
							throw IndexOutOfBoundsException("Pointer position has reached the upper limit.");
						PointerIterator<T>::next();
						position++;
					}

				};

			}

		}

	}

}