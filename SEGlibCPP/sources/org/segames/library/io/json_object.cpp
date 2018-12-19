#include <org\segames\library\io\json_object.h>
#include <org\segames\library\io\json_array.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace io
			{

				char* JSONObject::getEntryValueOfType(const JSONEntry::Type type, const std::string& name)
				{
					const JSONEntry* entry = get<JSONEntry>(name);
					if (entry)
						if (entry->isType(type))
							return entry->getData().get();
					return nullptr;
				}

				void JSONObject::putEntry(const std::string& name, std::unique_ptr<JSONEntry>& ptr)
				{
					if (!ptr.get())
						return;

					auto entry = getEntries().find(name);
					if (entry == getEntries().end())
						getEntries().insert(std::pair<std::string, std::unique_ptr<JSONEntry>>(name, ptr.release()));
					else
						entry->second.swap(ptr);
				}

				JSONObject::JSONObject() :
					JSONEntry(OBJECT, new std::unordered_map<std::string, std::unique_ptr<JSONEntry>>())
				{}

				std::unordered_map<std::string, std::unique_ptr<JSONEntry>>& JSONObject::getEntries()
				{
					return *((std::unordered_map<std::string, std::unique_ptr<JSONEntry>>*)getData().get());
				}

				JSONEntry::Type JSONObject::typeOf(const std::string& name)
				{
					const JSONEntry* entry = get<JSONEntry>(name);
					if (entry)
						return entry->getType();
					return NONE;
				}

				template<> bool* JSONObject::get<bool>(const std::string& name)
				{
					return (bool*)getEntryValueOfType(BOOL, name);
				}

				template<> int* JSONObject::get<int>(const std::string& name)
				{
					return (int*)getEntryValueOfType(INT, name);
				}

				template<> float* JSONObject::get<float>(const std::string& name)
				{
					return (float*)getEntryValueOfType(FLOAT, name);
				}

				template<> std::string* JSONObject::get<std::string>(const std::string& name)
				{
					return (std::string*)getEntryValueOfType(STRING, name);
				}

				template<> JSONEntry* JSONObject::get<JSONEntry>(const std::string& name)
				{
					auto entry = getEntries().find(name);
					if (entry != getEntries().end())
						return entry->second.get();
					return nullptr;
				}

				template<> JSONObject* JSONObject::get<JSONObject>(const std::string& name)
				{
					return (JSONObject*)get<JSONEntry>(name);
				}

				template<> JSONArray* JSONObject::get<JSONArray>(const std::string& name)
				{
					return (JSONArray*)get<JSONEntry>(name);
				}

				void JSONObject::put(const std::string& name, const bool value)
				{
					putEntry(name, std::unique_ptr<JSONEntry>(new JSONEntry(BOOL, new bool(value))));
				}

				void JSONObject::put(const std::string& name, const int value)
				{
					putEntry(name, std::unique_ptr<JSONEntry>(new JSONEntry(INT, new int(value))));
				}

				void JSONObject::put(const std::string& name, const float value)
				{
					putEntry(name, std::unique_ptr<JSONEntry>(new JSONEntry(FLOAT, new float(value))));
				}

				void JSONObject::put(const std::string& name, const std::string& value)
				{
					putEntry(name, std::unique_ptr<JSONEntry>(new JSONEntry(STRING, new std::string(value))));
				}

				void JSONObject::put(const std::string& name, JSONEntry* entry)
				{
					putEntry(name, std::unique_ptr<JSONEntry>(entry));
				}

				void JSONObject::remove(const std::string& name)
				{
					getEntries().erase(name);
				}

				void JSONObject::clear()
				{
					getEntries().clear();
				}

				std::string JSONObject::toString() const
				{
					std::string s = "{\n";
					for (auto e : getEntries());
					return s + "}";
				}

			}

		}

	}

}