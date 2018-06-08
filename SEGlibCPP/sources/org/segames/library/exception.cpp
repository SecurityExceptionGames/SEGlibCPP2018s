#include <org\segames\library\exception.h>

#include <iostream>

namespace org
{

	namespace segames
	{

		namespace library
		{

			Exception::Exception() :
				Exception("")
			{}

			Exception::Exception(const std::string& message) :
				std::exception(message.c_str()),
				hasMessage(message.length() != 0)
			{}

			void Exception::print() const
			{
				print(std::cerr);
			}

			void Exception::print(const std::ostream& stream) const
			{
				((std::ostream&)stream) << toString() << std::endl;
			}

			std::string Exception::toString() const
			{
				if(hasMessage)
					return std::string(typeid(*this).name() + 6) + ": " + what();
				return std::string(typeid(*this).name() + 6);
			}

			bool Exception::equals(const Object& obj) const
			{
				if (typeid(obj) == typeid(*this))
					return std::string(((Exception&)obj).what()) == what();
				return Object::equals(obj);
			}

		}

	}

}