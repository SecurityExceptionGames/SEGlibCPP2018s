#include <org\segames\library\io\json_entry.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace io
			{

				JSONEntry::JSONEntry() :
					JSONEntry(NULL_, nullptr)
				{}

				JSONEntry::JSONEntry(const Type type_, void* ptr) :
					type(type_),
					data((char*)ptr)
				{}

				bool JSONEntry::isType(const Type type_) const
				{
					return type == type_;
				}

				JSONEntry::Type JSONEntry::getType() const
				{
					return type;
				}

				const std::unique_ptr<char>& JSONEntry::getData() const
				{
					return data;
				}
				
				std::string JSONEntry::toString() const
				{
					if (isType(NULL_) || !getData().get())
						return "null";
					else
					{
						switch (getType())
						{
						case BOOL:
							return *((bool*)getData().get()) ? "true" : "false";
						case INT:
							return std::to_string(*((int*)getData().get()));
						case FLOAT:
							return std::to_string(*((float*)getData().get()));
						case STRING:
							return *((std::string*)getData().get());
						default:
							return "???";
						}

					}

				}

			}

		}

	}

}