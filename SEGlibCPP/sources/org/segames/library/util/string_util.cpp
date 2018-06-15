#include <org\segames\library\util\string_util.h>

#include <org\segames\library\invalid_value_exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{

				inline const bool stringStartsWith(const std::string& src, const std::string& expr)
				{
					return src.compare(0, expr.size(), expr) == ZERO;
				}

				inline const bool stringEndsWith(const std::string& src, const std::string& expr)
				{
					return src.compare(src.size() - expr.size(), expr.size(), expr) == ZERO;
				}

				std::string stringConcat(const Collection<std::string>& col)
				{
					return stringConcat(col.begin(), col.end());
				}

				std::string stringConcat(const std::string separator, const Collection<std::string>& col)
				{
					return stringConcat(separator, col.begin(), col.end());
				}

				ArrayList<std::string> stringSplit(const std::string& src, const std::string& separator)
				{
					ArrayList<std::string> out;

					size_t pos;
					std::string str = src;
					while ((pos = str.find(separator)) != std::string::npos)
					{
						std::string token = str.substr(0, pos);
						if (token.size() != ZERO)
							out.add(token);
						str.erase(0, pos + separator.size());
					}

					if (str.size() != ZERO)
						out.add(str);
					return out;
				}

				ArrayList<std::string> stringSplit(const std::string& src, const Collection<std::string>& separators)
				{
					ArrayList<std::string> pices = {src};

					for (size_t n = 0; n < separators.size(); n++)
					{
						ArrayList<std::string> tempPices;

						for (size_t i = 0; i < pices.size(); i++)
						{
							size_t pos;
							std::string& str = pices.get(i);
							std::string& separator = ((Collection<std::string>&)separators).get(n);
							while ((pos = str.find(separator)) != std::string::npos)
							{
								std::string token = str.substr(0, pos);
								if (token.size() != ZERO)
									tempPices.add(token);
								str.erase(0, pos + separator.size());
							}

							if (str.size() != ZERO)
								tempPices.add(str);
						}

						std::swap(pices, tempPices);
					}

					return pices;
				}

				inline const bool parseBool(const std::string& src)
				{
					std::string str = src;
					std::transform(str.begin(), str.end(), str.begin(), tolower);
					if (str.find("true") != std::string::npos)
						return true;
					else if (str.find("false") != std::string::npos)
						return false;
					throw InvalidValueException("The given string does not contain a boolean.");
				}

				inline const signed int parseInt(const std::string& src)
				{
					if (src.find(".") != std::string::npos)
						throw InvalidValueException("The given string contains a period, could possibly be a float and not an integer.");
					return std::stoi(src);
				}

				const signed long long parseLong(const std::string& src)
				{
					if (src.find(".") != std::string::npos)
						throw InvalidValueException("The given string contains a period, could possibly be a float and not a long long.");
					return std::stoll(src);
				}

				inline const float parseFloat(const std::string& src)
				{
					return std::stof(src);
				}

				inline const double parseDouble(const std::string& src)
				{
					return std::stod(src);
				}

			}

		}

	}

}