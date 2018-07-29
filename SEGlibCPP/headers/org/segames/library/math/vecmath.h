#pragma once
#include <org\segames\library\object.h>
#include <org\segames\library\index_out_of_bounds_exception.h>
#include <org\segames\library\invalid_value_exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace math
			{

				/*
					Base class for a n-dimensional euclidean vector with templates for different data type and dimensions

					* @author	Philip Rosberg
					* @since	2018-06-21
					* @edited	2018-06-22
				*/
				template<typename T, int dim> class BasicVector :
					public Object
				{
				protected:
					
					/*
						Vector data
					*/
					T data[dim];

				public:

					/*
						Standard vector constructor
					*/
					BasicVector()
					{}

					/*
						Vector value constructor. Constructs a vector from the given values
						* @param[in] items The vector data to place in the vector
					*/
					template<typename... T2> BasicVector(const T2... items)
					{
#ifdef SEG_API_DEBUG_THROW
						if (sizeof...(items) != dim)
							throw InvalidValueException("Number of elements in parameter pack (" + std::to_string(sizeof...(items)) + ") is not equal to the vector dimensions (" + std::to_string(dim) + ").");
#endif
						T list[sizeof...(items)] = { (T)items... };
						for (int i = 0; i < dimensions(); i++)
							data[i] = list[i];
					}

					/*
						Cast vector constructor. A constructor that casts one type of vector into another if the element types are castable
						* @param[in] obj The vector to cast from
					*/
					template<typename T2> BasicVector(const BasicVector<T2, dim>& obj)
					{
						for (int i = 0; i < dimensions(); i++)
							data[i] = (T)obj.peek(i);
					}

					/*
						Returns the number of dimensions of the vector
					*/
					inline virtual int dimensions() const noexcept
					{
						return dim;
					}

					/*
						Returns the pointer to the first position in the backing data array
					*/
					inline virtual T* getPointer() noexcept
					{
						return data;
					}

					/*
						Returns the value of the element at the given position
						* @param[in] n The position of the element, composant, to return
					*/
					inline virtual T peek(const int n) const
					{
						return ((BasicVector<T, dim>&)*this)[n];
					}

					/*
						Returns a reference to the element at the given position
						* @param[in] n The position of the element, composant, to return
					*/
					inline T& operator[](const int n)
					{
#ifdef SEG_API_DEBUG_THROW
						if (n < 0 || n >= dim)
							throw IndexOutOfBoundsException("The given vector element is not in the dimension of the vector." + std::to_string(n));
#endif
						return data[n];
					}

					/*
						Returns a string representation of the object
					*/
					virtual std::string toString() const
					{
						std::string out = "[";
						for (int i = 0; i < dimensions(); i++)
						{
							out += std::to_string(peek(i));
							if (i < dimensions() - 1)
								out += ",";
						}
						return out + "]";
					}

					/*
						Returns true if the the given object is equal to this one
						* @param[in] obj The object to check
					*/
					virtual bool equals(const Object& obj) const
					{
						if (typeid(obj) == typeid(*this))
						{
							for (int i = 0; i < dimensions(); i++)
								if (((BasicVector<T, dim>&)obj).peek(i) != peek(i))
									return false;
							return true;
						}
						else
							return false;
					}
					
					/*
						Returns true if the the given vector is equal to this one, calls the equals() method
						* @param[in] obj The vector to check
					*/
					template<typename T2> inline bool operator==(const BasicVector<T2, dim>& obj) const
					{
						return equals(obj);
					}

					/*
						Returns true if the the given vector is not equal to this one, inverse of operator==
						* @param[in] obj The vector to check
					*/
					template<typename T2> inline bool operator!=(const BasicVector<T2, dim>& obj) const
					{
						return !(*this == obj);
					}

					/*
						Returns true if the the given vector is equal to this one
						* @param[in] obj The vector to check
					*/
					template<typename T2> inline bool equals(const BasicVector<T2, dim>& obj) const
					{
						for (int i = 0; i < dimensions(); i++)
							if (obj.peek(i) != peek(i))
								return false;
						return true;
					}

					/*
						Multiplies the vector by the given scalar
						* @param[in] scalar The scalar to multiply this vector by
					*/
					template<typename T2> inline BasicVector<T, dim>& operator*=(const T2 scalar)
					{
						for (int i = 0; i < dimensions(); i++)
							data[i] *= scalar;
						return *this;
					}

					/*
						Adds the given vector to this one
						* @param[in] obj The vector to add to this one
					*/
					template<typename T2> inline BasicVector<T, dim>& operator+=(const BasicVector<T2, dim>& obj)
					{
						for (int i = 0; i < dimensions(); i++)
							data[i] += obj.peek(i);
						return *this;
					}

					/*
						Subtracts the given vector from this one
						* @param[in] obj The vector to subtract from this one
					*/
					template<typename T2> inline BasicVector<T, dim>& operator-=(const BasicVector<T2, dim>& obj)
					{
						for (int i = 0; i < dimensions(); i++)
							data[i] -= obj.peek(i);
						return *this;
					}

				};

				/*
					Base class for a m x n euclidean matrix with template parameters for data type and size

					* @author	Philip Rosberg
					* @since	2018-06-21
					* @edited	2018-06-22
				*/
				template<class T, int rows, int cols> class BasicMatrix :
					public Object
				{
				protected:

					/*
						The matrix data
					*/
					T data[rows][cols];

				public:
					
					/*
						Standard matrix constructor
					*/
					BasicMatrix()
					{}

					/*
						Matrix initializer list constructor. Constructs a matrix form the contents of the given initializer list
						* @param[in] list The initializer list with data
					*/
					BasicMatrix(const std::initializer_list<std::initializer_list<T>>& list)
					{
#ifdef SEG_API_DEBUG_THROW
						if (list.size() != m())
							throw InvalidValueException("Initializer list size is not correct.");
						if (list.begin()->size() != n())
							throw InvalidValueException("Initializer list size is not correct.");
#endif
						for (int i = 0; i < m(); i++)
							memcpy((T*)data[i], list.begin()[i].begin(), sizeof(T) * n());
					}
					
					/*
						Cast matrix constructor. A constructor that casts one type of matrix into another if the element types are castable
						* @param[in] obj The matrix to cast from
					*/
					template<class T2> BasicMatrix(const BasicMatrix<T2, rows, cols>& obj)
					{
						for (int i = 0; i < m(); i++)
							for (int j = 0; j < n(); j++)
								data[i][j] = (T)obj.peek(i, j);
					}

					/*
						Returns the number of rows in the matrix
					*/
					inline virtual int m() const noexcept
					{
						return rows;
					}

					/*
						Returns the number of columns in the matrix
					*/
					inline virtual int n() const noexcept
					{
						return cols;
					}

					/*
						Returns a pointer to the first element of the matrix data
					*/
					inline virtual T* getPointer() noexcept
					{
						return (T*)data;
					}

					/*
						Returns the value at the given row and column position
						* @param[in] i The index of the row of the element to return
						* @param[in] j The index of the column of the element to return
					*/
					inline virtual T peek(const int i, const int j) const
					{
#ifdef SEG_API_DEBUG_THROW
						if (i < 0 || i >= m())
							throw IndexOutOfBoundsException("The index of the requested row is outside of the matrix: " + std::to_string(i));
						if (j < 0 || j >= n())
							throw IndexOutOfBoundsException("The index of the requested column is outside of the matrix: " + std::to_string(j));
#endif
						return data[i][j];
					}

					/*
						Returns a pointer to the given row of the matrix
						* @param[in] i The index of the row to returns the pointer to
					*/
					inline T* operator[](const int i)
					{
#ifdef SEG_API_DEBUG_THROW
						if (i < 0 || i >= m())
							throw IndexOutOfBoundsException("The index of the requested row is outside of the matrix: " + std::to_string(i));
#endif
						return data[i];
					}

					/*
						Returns a string representation of the object
					*/
					virtual std::string toString() const
					{
						std::string out = "";
						for (int i = 0; i < m(); i++)
						{
							out += "| ";

							for (int j = 0; j < n(); j++)
							{
								out += std::to_string(peek(i, j));
								if (j < n() - 1)
									out += "\t";
							}

							out += " |\n";
						}

						return out;
					}

					/*
						Returns true if the the given object is equal to this one
						* @param[in] obj The object to check
					*/
					virtual bool equals(const Object& obj) const
					{
						if (typeid(obj) == typeid(*this))
						{
							for (int i = 0; i < m(); i++)
								for (int j = 0; j < n(); j++)
									if (((BasicMatrix<T, rows, cols>&)obj).peek(i, j) != peek(i, j))
										return false;
							return true;
						}
						else
							return false;
					}

					/*
						Returns true if the the given matrix is equal to this one, calls the equals() method
						* @param[in] obj The matrix to check
					*/
					template<class T2> bool operator==(const BasicMatrix<T2, rows, cols>& obj) const
					{
						return equals(obj);
					}

					/*
						Returns true if the the given matrix is not equal to this one, inverse of operator==
						* @param[in] obj The matrix to check
					*/
					template<class T2> bool operator!=(const BasicMatrix<T2, rows, cols>& obj) const
					{
						return !(*this == obj);
					}

					/*
						Returns true if the the given matrix is equal to this one
						* @param[in] obj The matrix to check
					*/
					template<class T2> bool equals(const BasicMatrix<T2, rows, cols>& obj) const
					{
						for (int i = 0; i < m(); i++)
							for (int j = 0; j < n(); j++)
								if (obj.peek(i, j) != peek(i, j))
									return false;
						return true;
					}

				};


				// TODO Add operator overrides and generic functions like dot() and inv()
				// Under this line there is currently only debugg content

				/*
					~~~~~~~~~~~~~~~~~~~~~~~~~~~
					This is a temporary comment
					~~~~~~~~~~~~~~~~~~~~~~~~~~~
				*/
				template<class T, class T2, int dim> inline BasicVector<T, dim> operator+(const BasicVector<T, dim>& a, const BasicVector<T2, dim>& b)
				{
					BasicVector<T, dim> out;
					for (int i = 0; i < out.dimensions(); i++)
						out[i] = (T)(a.peek(i) + b.peek(i));
					return out;
				}

				template<int dim> using Vector = BasicVector<double, dim>;
				template<int dim> using Vectorf = BasicVector<float, dim>;
				template<int dim> using Vectorl = BasicVector<long double, dim>;
				using vec2 = Vector<2>;
				using vec3 = Vector<3>;
				using vec4 = Vector<4>;

			}

		}

	}

}