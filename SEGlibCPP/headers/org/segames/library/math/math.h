#pragma once
#include <cmath>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace math
			{

				/*
					A function that clamps the given value between the given minimum and maximum limit
					* @param[in] value The value to clamp
					* @param[in] min The minimum limit
					* @param[in] max The maximum limit
				*/
				template<typename T> inline T clamp(const T value, const T min, const T max)
				{
					if (value > max)
						return max;
					else if (value < min)
						return min;
					return value;
				}

				/*
					A function that returns the latter value if it is larger than the former, otherwise it returns the former
					* @param[in] a The former value
					* @param[in] b The latter value
				*/
				template<typename T> inline T max(const T a, const T b)
				{
					if (b > a)
						return b;
					return a;
				}

				/*
					A function that returns the latter value if it is smaller than the former, otherwise it returns the former
					* @param[in] a The former value
					* @param[in] b The latter value
				*/
				template<typename T> inline T min(const T a, const T b)
				{
					if (b < a)
						return b;
					return a;
				}

				/*
					Performs a linear interpolation between x and y using a to weight between them
					* @param[in] x The primary value
					* @param[in] y The secondary value
					* @param[in] a The weighting value
				*/
				template<typename T> inline T mix(const T x, const T y, const T a)
				{
					return x * (1 - a) + y * a;
				}

				/*
					Performes a smooth Hermite interpolation between 0 and 1 when edge0 < x < edge1. Undefined for edge0 >= edge1
					* @param[in] edge0 The lower edge of the Hermite function
					* @param[in] edge1 The upper edge of the Hermite function
					* @param[in] x The source value for interpolation
				*/
				template<typename T> inline T smoothstep(const T edge0, const T edge1, const T x)
				{
					T t = clamp((x - edge0) / (edge1 - edge0), (T)0.0, (T)1.0);
					return t * t * ((T)3.0 - (T)2.0 * t);
				}

				/*
					Returns a random value between 0 and 1 with standard floating point precision
				*/
				float randomf();

				/*
					Returns a random value between 0 and 1 with double precision
				*/
				double random();

			}

		}

	}

}