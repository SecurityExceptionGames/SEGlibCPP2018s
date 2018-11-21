#pragma once
#include <org\segames\library\util\collection.h>

#ifndef SEG_API_ARRAY_LIST_CAPACITY
#define SEG_API_ARRAY_LIST_CAPACITY 32
#endif // SEG_API_ARRAY_LIST_CAPACITY

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{

				/*
					ArrayList class, fast appendable array

					* @author	Philip Rosberg
					* @since	2018-06-04
					* @edited	2018-06-04
				*/
				template<class T> class ArrayList :
					public Collection<T>
				{
				private:

					/*
						The current write head, ie. the current usable array size
					*/
					size_t writeHead;

				public:

					/*
						Creates an ArrayList with the standard capacity
					*/
					ArrayList() :
						ArrayList<T>(SEG_API_ARRAY_LIST_CAPACITY)
					{}

					/*
						Creates an ArrayList with the given start capacity, if less than or equal to zero a size of one is enforced
						* @param[in] initialCapacity The initial capacity of the backing buffer in the arraylist
					*/
					ArrayList(const size_t initialCapacity) :
						Collection<T>(initialCapacity > 0 ? initialCapacity : 0),
						writeHead(ZERO)
					{}

					/*
						Creates an arraylist with the given content
						* @param[in] list The content to create the arraylist from
					*/
					ArrayList(const std::initializer_list<T>& list) :
						Collection<T>(list.size() > 0 ? list.size() : 0),
						writeHead(list.size())
					{
						if (memory.isPrimitive())
							memcpy(memory.getPointer(), list.begin(), memory.getNativeSize());
						else
							std::copy(list.begin(), list.end(), stdext::checked_array_iterator<T*>(memory.getPointer(), memory.getSize()));
					}

					/*
						Collection copy constructor
						* @param[in] obj The Collection to copy
					*/
					ArrayList(const Collection<T>& obj) :
						Collection<T>(obj),
						writeHead(obj.size())
					{}

					/*
						ArrayList copy constructor
						* @param[in] obj The ArrayList to copy
					*/
					ArrayList(const ArrayList<T>& obj) :
						Collection<T>(obj.capacity()),
						writeHead(obj.size())
					{
						if (memory.isPrimitive())
							memcpy(memory.getPointer(), obj.begin().getPointer(), memory.getNativeSize());
						else
							std::copy(obj.begin(), obj.end(), stdext::checked_array_iterator<T*>(memory.getPointer(), memory.getSize()));
					}

					/*
						Returns the current size of the arraylist in num. elements
					*/
					virtual size_t size() const noexcept
					{
						return writeHead;
					}

					/*
						Returns the size of the backing memory in num. elements
					*/
					virtual size_t capacity() const noexcept
					{
						return memory.getSize();
					}

					/*
						Adds the given element to the ArrayList
						* @param[in] e The element to add
					*/
					virtual size_t add(const T& e)
					{
						if (size() >= capacity())
							memory.resize(capacity() * 2);
						memory.getPointer()[writeHead] = e;
						return writeHead++;
					}

					/*
						Adds all elements from the given collection
						* @param[in] obj The collection to add all elements from
					*/
					virtual void addAll(const Collection<T>& obj)
					{
						while (size() + obj.size() >= capacity())
							memory.resize(capacity() * 2);

						if (memory.isPrimitive())
							memcpy(memory.getPointer() + size(), obj.begin().getPointer(), obj.getMemory().getNativeSize());
						else
							std::copy(obj.begin(), obj.end(), stdext::checked_array_iterator<T*>(memory.getPointer() + size(), memory.getSize()));
						writeHead += obj.size();
					}

					/*
						Adds all elements from the given initializer_list
						* @param[in] obj The initializer list to add all elements from
					*/
					virtual void addAll(const std::initializer_list<T>& obj)
					{
						while (size() + obj.size() >= capacity())
							memory.resize(capacity() * 2);

						if (memory.isPrimitive())
							memcpy(memory.getPointer() + size(), obj.begin(), obj.size() * sizeof(T));
						else
							std::copy(obj.begin(), obj.end(), stdext::checked_array_iterator<T*>(memory.getPointer() + size(), memory.getSize()));
						writeHead += obj.size();
					}

					/*
						Removes the element with the given index
						* @param[in] index The index of the element
					*/
					virtual T remove(const size_t index)
					{
						T out = get(index);

						if (size() > index)
							if (memory.isPrimitive())
								memcpy(memory.getPointer() + index, memory.getPointer() + index + 1, (size() - index - 1) * sizeof(T));
							else
								std::copy(memory.getPointer() + index + 1, memory.getPointer() + size(), stdext::checked_array_iterator<T*>(memory.getPointer() + index, memory.getSize()));

						writeHead--;
						return out;
					}

					/*
						Clears the ArrayList
					*/
					virtual void clear() noexcept
					{
						writeHead = ZERO;
					}

					/*
						Resizes the backing memory to the list size
					*/
					virtual void compact()
					{
						if (writeHead == ZERO)
							memory = MemoryBlock<T>(1);
						else
							memory.resize(writeHead);
					}

				};

			}

		}

	}

}