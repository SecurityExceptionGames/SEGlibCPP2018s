#pragma once
#include <org\segames\library\util\pointer_iterator.h>
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
					A bidirectional pointer iterator

					* @author	Philip Rosberg
					* @since	2018-05-17
					* @edited	2018-05-17
				*/
				template<class T> class BidirPointerIterator : 
					public PointerIterator<T>,
					public ReverseIterator<T>
				{
				public:
					typedef T value_type;
					typedef T* pointer;
					typedef T& reference;
					typedef std::ptrdiff_t difference_type;
					typedef std::bidirectional_iterator_tag iterator_category;

				public:

					/*
						Creates a zeroed bidirectional pointer iterator
					*/
					BidirPointerIterator() :
						PointerIterator<T>()
					{}

					/*
						Creates a pointer iterator with the given pointer
						* @param[in] point The pointer
					*/
					BidirPointerIterator(const T* point) :
						PointerIterator<T>(point)
					{}

					/*
						Returns true if the reverse iterator has a next value to reverse to, ie. in an array as a previous value
					*/
					virtual bool hasPrevious() const noexcept
					{
						return true;
					}

					/*
						Moves the iterator to the previous position
					*/
					virtual void previous()
					{
						itrPointer--;
					}

					/*
						Moves the iterator one step, as standard same as next()
					*/
					BidirPointerIterator<T> operator++(int) {
						BidirPointerIterator<T> temp = *this;
						PointerIterator<T>::next();
						return temp;
					}

					/*
						Moves the iterator one step, as standard same as previous()
					*/
					virtual BidirPointerIterator<T>& operator--()
					{
						previous();
						return *this;
					}

					/*
						Moves the iterator one step, as standard same as previous()
					*/
					BidirPointerIterator<T> operator--(int) {
						BidirPointerIterator<T> temp = *this;
						previous();
						return temp;
					}

					/*
						Reverses the iterator the given amount of steps
						* @param[in] count The amount of steps to move the iterator
					*/
					BidirPointerIterator<T>& operator-=(const size_t count)
					{
						itrPointer -= count;
						return *this;
					}

					/*
						Returns true if the given iterator is the same as this one
						* @param[in] itr The iterator to check with
					*/
					bool operator==(const BidirPointerIterator<T>& itr) const
					{
						return PointerIterator<T>::operator==(itr);
					}

				};

			}

		}

	}

}