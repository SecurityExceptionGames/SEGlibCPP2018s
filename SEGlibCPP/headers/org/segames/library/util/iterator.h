#pragma once

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{

				/*
					Standard iterator interface

					* @author	Philip Rosberg
					* @since	2018-05-15
					* @edited	2018-05-15
				*/
				template<class T> class Iterator
				{
				public:
					/*
						Returns true if the iterator has a next iterator
					*/
					virtual bool hasNext() const noexcept = 0;

					/*
						Moves the iterator one step
					*/
					virtual void next() = 0;

					/*
						Returns true if the given iterator is the same (mostly on the same position) as this one
						* @param[in] itr The iterator to check with
					*/
					virtual bool operator==(const Iterator<T>& itr) const
					{
						return false;
					}

					/*
						Returns true if the given iterator is not the same as this one
						* @param[in] itr The iterator to check with
					*/
					virtual bool operator!=(const Iterator<T>& itr) const
					{
						return !(*this == itr);
					}

				};

			}

		}

	}

}