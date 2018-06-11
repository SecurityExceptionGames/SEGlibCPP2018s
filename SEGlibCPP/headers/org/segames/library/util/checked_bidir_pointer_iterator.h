#pragma once
#include <org\segames\library\util\checked_pointer_iterator.h>
#include <org\segames\library\util\reverse_iterator.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{

				/*
					A checked bidirectional pointer iterator

					* @author	Philip Rosberg
					* @since	2018-05-22
					* @edited	2018-05-22
				*/
				template<class T> class CheckedBidirPointerIterator :
					public CheckedPointerIterator<T>,
					public ReverseIterator<T>
				{
				public:
					typedef T value_type;
					typedef T* pointer;
					typedef T& reference;
					typedef std::ptrdiff_t difference_type;
					typedef std::bidirectional_iterator_tag iterator_category;

				protected:

					/*
						The lower pointer limit
					*/
					size_t lowerLimit;

				public:

					/*
						Creates a zeroed checked bidirectional pointer iterator
					*/
					CheckedBidirPointerIterator() :
						CheckedPointerIterator<T>(),
						lowerLimit(ZERO)
					{}

					/*
						Creates a checked bidirectional pointer iterator with the given attributes, but with the lower limit set to zero
						* @param[in] cpos The current pointer position, must be less than upper
						* @param[in] upper The upper pointer value, ie. the end value not the last
						* @param[in] point The current pointer
					*/
					CheckedBidirPointerIterator(const size_t cpos, const size_t upper, const T* point) :
						CheckedBidirPointerIterator<T>(cpos, ZERO, upper, point)
					{}

					/*
						Creates a checked bidirectional pointer iterator with the given attributes
						* @param[in] cpos The current pointer position, must be less than upper
						* @param[in] lower The lower pointer value, ie. the lowest value reachable, standard is 0
						* @param[in] upper The upper pointer value, ie. the end value not the last
						* @param[in] point The current pointer
					*/
					CheckedBidirPointerIterator(const size_t cpos, const size_t lower, const size_t upper, const T* point) :
						CheckedPointerIterator<T>(cpos, upper, point),
						lowerLimit(lower)
					{
						if (cpos < lower)
							throw IndexOutOfBoundsException("Pointer position is below the lower limit on construction.");
					}
					
					/*
						Returns true if the reverse iterator has a next value to reverse to
					*/
					virtual bool hasPrevious() const noexcept
					{
						return position > lowerLimit;
					}

					/*
						Moves the iterator to the previous position
					*/
					virtual void previous()
					{
						if (position < lowerLimit)
							throw IndexOutOfBoundsException("Pointer position has reached the lower limit.");
						itrPointer--;
						position--;
					}

					/*
						Moves the iterator one step, as standard same as previous()
					*/
					virtual CheckedPointerIterator<T>& operator--()
					{
						previous();
						return *this;
					}

					/*
						Moves the iterator one step, as standard same as previous()
					*/
					CheckedBidirPointerIterator<T> operator--(int) {
						CheckedBidirPointerIterator<T> temp = *this;
						previous();
						return temp;
					}

					/*
						Reverses the iterator the given amount of steps
						* @param[in] count The amount of steps to move the iterator
					*/
					CheckedBidirPointerIterator<T>& operator-=(const size_t count)
					{
						if ((position - count) < lowerLimit)
							throw IndexOutOfBoundsException("Pointer position has reached the lower limit.");
						itrPointer -= count;
						position -= count;
					}

					/*
						Returns true if the given iterator is the same as this one
						* @param[in] itr The iterator to check with
					*/
					bool operator==(const CheckedBidirPointerIterator<T>& itr) const
					{
						return CheckedPointerIterator<T>::operator==(itr);
					}

					/*
						Returns true if the given iterator is not the same as this one
						* @param[in] itr The iterator to check with
					*/
					virtual bool operator!=(const CheckedBidirPointerIterator<T>& itr) const
					{
						return CheckedPointerIterator<T>::operator!=(itr);
					}

				};

			}

		}

	}

}