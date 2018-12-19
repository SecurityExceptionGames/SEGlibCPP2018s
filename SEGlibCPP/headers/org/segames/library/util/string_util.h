#pragma once
#include <org\segames\library\util\array_list.h>

#include <string>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{

				/*
					Returns true if the given source string starts with the given expression
					* @param[in] src The source string
					* @param[in] expr The expression to check for
				*/
				const bool stringStartsWith(const std::string& src, const std::string& expr);
				
				/*
					Returns true if the given source string ends with the given expression
					* @param[in] src The source string
					* @param[in] expr The expression to check for
				*/
				const bool stringEndsWith(const std::string& src, const std::string& expr);

				/*
					Creates a hash code from the given c-string
					* @param[in] str The c-string to create a hash from
				*/
				inline size_t stringHash(const char* str)
				{
					char c;
					size_t code = 0;
					for (int i = 0; (c = str[i]) != '\0'; i++)
					{
						size_t partCode = 1;
						for (int e = 0; e <= i; e++)
							partCode *= 31;
						code += partCode * c;
					}
					return code;
				}

				/*
					Creates a hash code from the given string
					* @param[in] str The string to create a hash from
				*/
				inline size_t stringHash(const std::string& str)
				{
					return stringHash(str.c_str());
				}

				/*
					Concats the strings from the given list
					* @param[in] first The begining iterator or pointer to a list/array of strings
					* @param[in] last The ending iterator or pointer
				*/
				template<class Itr> inline std::string stringConcat(const Itr& first, const Itr& last)
				{
					size_t size = ZERO;
					for (Itr itr = first; itr != last; itr++)
						size += (*itr).size();

					std::string out;
					out.reserve(size);
					for (Itr itr = first; itr != last; itr++)
						out.append(*itr);
					
					return out;
				}

				/*
					Concats strings from the given collection
					* @param[in] col The collection with strings
				*/
				std::string stringConcat(const Collection<std::string>& col);

				/*
					Concats the strings from the given list and separates them by the given separator
					* @param[in] separator The separator sequence, ie. the string inserted between the strings that are being concatenated
					* @param[in] first The begining iterator or pointer to a list/array of strings
					* @param[in] last The ending iterator or pointer
				*/
				template<class ItrBeg, class ItrEnd> inline std::string stringConcat(const std::string& separator, const ItrBeg& first, const ItrEnd& last)
				{
					size_t size = ZERO;
					for (ItrBeg itr = first; itr != last; itr++)
						size += (*itr).size() + separator.size();
					if (size > ZERO)
						size -= separator.size();

					std::string out;
					out.reserve(size);
					for (ItrBeg itr = first; itr != last; itr++)
					{
						std::string& s = *itr;
						out.append(s);
						
						size -= s.size();
						if (size > ZERO)
						{
							out.append(separator);
							size -= separator.size();
						}

					}
					return out;
				}

				/*
					Concats the strings from the given collection and separates them by the given separator
					* @param[in] separator The separator sequence, ie. the string inserted between the strings that are being concatenated
					* @param[in] col The collection with strings to concat
				*/
				std::string stringConcat(const std::string separator, const Collection<std::string>& col);
				
				/*
					Splits the given string by the given separator sequence
					* @param[in] src The string to split
					* @param[in] separator The string to split the first one by
				*/
				ArrayList<std::string> stringSplit(const std::string& src, const std::string& separator);
				
				/*
					Splits the given string by the given separator sequences
					* @param[in] src The string to split
					* @param[in] separators The strings to split the first one by
				*/
				ArrayList<std::string> stringSplit(const std::string& src, const Collection<std::string>& separators);
				
				/*
					Parses a boolean if one exists from the given string
					* @param[in] src The source string
				*/
				const bool parseBool(const std::string& src);

				/*
					Parses an integer if one exists from the given string
					* @param[in] src The source string
				*/
				const int parseInt(const std::string& src);

				/*
					Parses a long long if one exists from the given string
					* @param[in] src The source string
				*/
				const long long parseLong(const std::string& src);

				/*
					Parses a float if one exists from the given string
					* @param[in] src The source string
				*/
				const float parseFloat(const std::string& src);
				
				/*
					Parses a double if one exists from the given string
					* @param[in] src The source string
				*/
				const double parseDouble(const std::string& src);

			}

		}

	}

}