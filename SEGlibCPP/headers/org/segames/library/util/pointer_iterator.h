#pragma once
#include <org\segames\library\object.h>
#include <org\segames\library\null_pointer_exception.h>
#include <org\segames\library\util\iterator.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{

				/*
					An iterator storing a pointer

					* @author	Philip Rosberg
					* @since	2018-05-15
					* @edited	2018-05-15
				*/
				template<class T> class PointerIterator :
					public Object,
					public Iterator<T>
				{
				public:
					typedef T value_type;
					typedef T* pointer;
					typedef T& reference;
					typedef std::ptrdiff_t difference_type;
					typedef std::forward_iterator_tag iterator_category;

				protected:

					/*
						The pointer stored in the iterator
					*/
					T* itrPointer;

				public:

					/*
						Creates a zeroed pointer iterator
					*/
					PointerIterator() :
						itrPointer(nullptr)
					{}

					/*
						Creates a pointer iterator with the given pointer
						* @param[in] point The pointer
					*/
					PointerIterator(const T* point) :
						itrPointer((T*)point)
					{
						if (!itrPointer)
							throw NullPointerException("Pointer iterator expects a non-null pointer.");
					}

					/*
						Returns the stored pointer
					*/
					virtual T* getPointer() const
					{
						return itrPointer;
					}

					/*
						Returns true if the iterator has a next iterator step
					*/
					virtual bool hasNext() const noexcept
					{
						return true;
					}

					/*
						Moves the iterator one step
					*/
					virtual void next()
					{
						itrPointer++;
					}

					/*
						Moves the iterator one step, as standard same as next()
					*/
					virtual PointerIterator<T>& operator++()
					{
						next();
						return *this;
					}

					/*
						Moves the iterator one step, as standard same as next()
					*/
					PointerIterator<T> operator++(int)
					{
						PointerIterator<T> temp = *this;
						next();
						return temp;
					}

					/*
						Moves the iterator by the given amount of steps
						* @param[in] count The amount of steps to move the iterator
					*/
					PointerIterator<T>& operator+=(const size_t count)
					{
						itrPointer += count;
						return *this;
					}

					/*
						Retruns the value at the iterator position, ie. derefrences the stored pointer in the iterator
					*/
					virtual T& operator*() const
					{
						return *itrPointer;
					}

					/*
						Returns true if the given iterator is the same as this one
						* @param[in] itr The iterator to check with
					*/
					bool operator==(const PointerIterator<T>& itr) const
					{
						return itr.itrPointer == this->itrPointer;
					}

					/*
						Returns true if the given iterator is not the same as this one
						* @param[in] itr The iterator to check with
					*/
					virtual bool operator!=(const PointerIterator<T>& itr) const
					{
						return !(*this == itr);
					}

				};

			}

		}

	}

}