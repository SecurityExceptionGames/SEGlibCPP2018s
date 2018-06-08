#pragma once
#include <iterator>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{

				/*
					Iterator interface for backwards going iterators

					* @author	Philip Rosberg
					* @since	2018-05-17
					* @edited	2018-05-17
				*/
				template<class T> class ReverseIterator
				{
				public:

					/*
						Returns true if the reverse iterator has a next value to reverse to, ie. in an array as a previous value
					*/
					virtual bool hasPrevious() const noexcept = 0;

					/*
						Moves the iterator to the next reverseable value, the previous
					*/
					virtual void previous() = 0;

					/*
						Returns true if the given iterator is the same (mostly on the same position) as this one
						* @param[in] itr The iterator to check with
					*/
					virtual bool operator==(const ReverseIterator<T>& itr) const
					{
						return false;
					}

					/*
						Returns true if the given iterator is not the same as this one
						* @param[in] itr The iterator to check with
					*/
					virtual bool operator!=(const ReverseIterator<T>& itr) const
					{
						return !(*this == itr);
					}

				};

			}

		}

	}

}