#pragma once
#include <org\segames\library\util\checked_bidir_pointer_iterator.h>
#include <org\segames\library\util\memory_block.h>
#include <org\segames\library\array_index_out_of_bounds_exception.h>

#include <algorithm>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{

				/*
					Super-class for collections, eg. ArrayList

					* @author	Philip Rosberg
					* @since	2018-05-28
					* @edited	2018-05-28
				*/
				template<class T> class Collection :
					public Object
				{
				protected:

					/*
						The backing memory block
					*/
					MemoryBlock<T> memory;

				public:

					/*
						Creates an empty collection
					*/
					Collection() :
						memory(MemoryBlock<T>())
					{}

					/*
						Creates a collection of the given size in num. elements
						* @param[in] size The size of the collection in num elements
					*/
					Collection(const size_t size) :
						memory(MemoryBlock<T>(size))
					{}

					/*
						Collection copy constructor
						* @param[in] obj The collection to copy
					*/
					Collection(const Collection<T>& obj) :
						memory(MemoryBlock<T>(obj.size()))
					{
						if (memory.isPrimitive())
							memcpy(memory.getPointer(), obj.getMemory().getPointer(), memory.getNativeSize());
						else
							std::copy(obj.begin(), obj.end(), stdext::checked_array_iterator<T*>(memory.getPointer(), size()));
					}

					/*
						Returns the current size of the editable part of the collection
					*/
					virtual size_t size() const noexcept
					{
						return memory.getSize();
					}

					/*
						Returns true if the collection is empty, ie. has a size of zero
					*/
					virtual bool isEmpty() const noexcept
					{
						return size() == 0;
					}

					/*
						Returns the backing memory
					*/
					virtual MemoryBlock<T> getMemory() const noexcept
					{
						return memory;
					}

					/*
						Returns true if the collection contains the given element
						* @param[in] obj The element to search for
					*/
					virtual bool contains(const T& obj) const
					{
						return indexOf(obj) != (size_t)-1;
					}

					/*
						Returns the index of the first occurrence of the given element, returns size_t maximum value if the element was not found
						* @param[in] obj The element to search for
					*/
					virtual size_t indexOf(const T& obj) const
					{
						for (size_t i = 0; i < size(); i++)
							if (((Collection<T>&)*this).get(i) == obj)
								return i;
						return (size_t)-1;
					}

					/*
						Returns the index of the last occurrence of the given element, returns size_t maximum value if the element was not found
						* @param[in] obj The element to search for
					*/
					virtual size_t lastIndexOf(const T& obj) const
					{
						for (size_t i = size() - 1; i >= 0; i--)
							if (((Collection<T>&)*this).get(i) == obj)
								return i;
						return (size_t)-1;
					}

					/*
						Returns the begining iterator
					*/
					virtual CheckedBidirPointerIterator<T> begin() const
					{
						return CheckedBidirPointerIterator<T>(0, 0, size(), memory.getPointer());
					}

					/*
						Returns the end iterator
					*/
					virtual CheckedBidirPointerIterator<T> end() const
					{
						return CheckedBidirPointerIterator<T>(size(), 0, size(), memory.getPointer() + size());
					}

					/*
						Returns a copy of the element at the given index
						* @param[in] index The index of the element
					*/
					virtual T& peek(const size_t index) const
					{
						return (T&)((Collection<T>&)*this).get(index);
					}

					/*
						Returns a reference to the element at the given index
						* @param[in] index The index of the element
					*/
					virtual T& get(const size_t index)
					{
#ifdef SEG_API_DEBUG_THROW
						if (index < 0 || index >= size())
							throw ArrayIndexOutOfBoundsException(index);
#endif
						return memory.getPointer()[index];
					}

					/*
						Sets the value of the element at the given index and retrurns the prior one
						* @param[in] index The index of the element
						* @param[in] value The value to set the element to
					*/
					virtual T set(const size_t index, const T& value)
					{
						T out = get(index);
						get(index) = value;
						return out;
					}

				};

			}

		}

	}

}