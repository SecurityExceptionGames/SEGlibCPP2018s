#pragma once
#include <org\segames\library\memory_exception.h>

#include <iterator>
#include <memory>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{
				
				/*
					A memory block handling class, automatically frees memory when it goes out of scope

					* @author	Philip Rosberg
					* @since	2018-05-23
					* @edited	2018-05-23
				*/
				template<class T> class MemoryBlock
				{
				private:
					
					/*
						True if T is primitive
					*/
					bool primitive;

					/*
						The memory block size in T
					*/
					size_t size;

					/*
						The memory block size in bytes
					*/
					size_t nativeSize;

					/*
						The pointer
					*/
					T* pointer;

					/*
						Attempts to alloc memory, throws a MemoryException if it fails
						* @param[in] count The amount of elements to alloc memory for
					*/
					T* allocMem(const size_t count)
					{
						T* tempPtr = nullptr;
						if (count > 0)
						{
							if (primitive)
								tempPtr = (T*)calloc(count, sizeof(T));
							else
							{
								try
								{
									tempPtr = new T[count];
								}
								catch (const std::exception&)
								{
									tempPtr = nullptr;
								}

							}

							if (!tempPtr)
								throw MemoryException("Could not alloc memory. Out of RAM?");
						}

						return tempPtr;
					}

				public:

					/*
						Creates a zeroed memory block
					*/
					MemoryBlock() : 
						size(ZERO),
						nativeSize(ZERO),
						pointer(nullptr),
						primitive(std::is_fundamental_v<T>)
					{}

					/*
						Creates a memory block with the given amount of elements
						* @param[in] count The amount of elements to alloc memory for
					*/
					MemoryBlock(const size_t count) :
						size(count),
						nativeSize(count * sizeof(T)),
						pointer(allocMem(count)),
						primitive(std::is_fundamental_v<T>)
					{}

					/*
						MemoryBlock copy constructor
						* @param[in] obj The memory-block to copy
					*/
					MemoryBlock(const MemoryBlock<T>& obj) :
						size(obj.getSize()),
						nativeSize(obj.getNativeSize()),
						pointer(allocMem(size)),
						primitive(std::is_fundamental_v<T>)
					{
						if (primitive)
							memcpy(pointer, obj.getPointer(), nativeSize);
						else
							std::copy(obj.getPointer(), obj.getPointer() + size, stdext::checked_array_iterator<T*>(pointer, size));
					}

					/*
						Destructor
					*/
					~MemoryBlock()
					{
						if (pointer)
						{
							if (primitive)
								free(pointer);
							else
								delete[] pointer;
						}

					}

					/*
						Returns true if the template type is primitive
					*/
					virtual bool isPrimitive() const noexcept
					{
						return primitive;
					}

					/*
						Returns the memory size in elements
					*/
					virtual size_t getSize() const noexcept
					{
						return size;
					}

					/*
						Returns the size of the allocated memory block in bytes
					*/
					virtual size_t getNativeSize() const noexcept
					{
						return nativeSize;
					}

					/*
						Returns the memory pointer
					*/
					virtual T* getPointer() const noexcept
					{
						return pointer;
					}

					/*
						Resizes the memory block
						* @param[in] newCount The amount of elements to re-alloc memory for
					*/
					virtual void resize(const size_t newCount)
					{
						T* tempPtr = (primitive ? (T*)realloc(pointer, newCount * sizeof(T)) : nullptr);
						if (!tempPtr)
						{
							tempPtr = allocMem(newCount);
							
							if (primitive)
							{
								memcpy(tempPtr, pointer, nativeSize);
								free(pointer);
							}
							else
							{
								std::copy(pointer, pointer + size, stdext::checked_array_iterator<T*>(tempPtr, size));
								delete[] pointer;
							}

						}
						else if (size < newCount)
							memset(tempPtr + size, ZERO, (newCount - size) * sizeof(T));

						pointer = tempPtr;
						size = newCount;
						nativeSize = size * sizeof(T);
					}

					/*
						Set operator override, copies the data from one block to the other
					*/
					MemoryBlock<T>& operator=(const MemoryBlock& obj)
					{
						this->~MemoryBlock();
						size = obj.getSize();
						nativeSize = obj.getNativeSize();
						pointer = allocMem(size);

						if (primitive)
							memcpy(pointer, obj.getPointer(), nativeSize);
						else
							std::copy(obj.getPointer(), obj.getPointer() + size, stdext::checked_array_iterator<T*>(pointer, size));
						return *this;
					}

				};
				
				/*
					Attempts to alloc memory, throws a MemoryException if it fails
					* @param[in] count The amount of elements to alloc memory for
				*/
				template<> void* MemoryBlock<void>::allocMem(const size_t count)
				{
#ifdef SEG_API_MEMORY_HANDLING_STRICT
					throw MemoryException("Cannot alloc memory of type void.");
					return nullptr;
#else
					void* tempPtr = malloc(count);
					if (!tempPtr)
						throw MemoryException("Could not alloc memory. Out of RAM?");
					return tempPtr;
#endif
				}

				/*
					Resizes the memory block
					* @param[in] newCount The amount of elements to re-alloc memory for
				*/
				template<> void MemoryBlock<void>::resize(const size_t newCount)
				{
#ifdef SEG_API_MEMORY_HANDLING_STRICT
					throw MemoryException("Cannot resize memory of type void.")
#else
					void* tempPtr = realloc(pointer, newCount);
					if (!tempPtr)
					{
						tempPtr = allocMem(newCount);
						memcpy(tempPtr, pointer, size);
						free(pointer);
					}
					else if (size < newCount)
						memset((char*)tempPtr + size, ZERO, newCount - size);

					pointer = tempPtr;
					size = newCount;
					nativeSize = size;
#endif
				}

			}

		}

	}

}