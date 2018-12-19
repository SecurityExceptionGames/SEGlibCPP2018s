#include <org\segames\library\io\json_array.h>
#include <org\segames\library\io\json_object.h>
#include <org\segames\library\array_index_out_of_bounds_exception.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace io
			{

				char* JSONArray::getEntryValueOfType(const JSONEntry::Type type, const int index)
				{
					const JSONEntry* entry = get<JSONEntry>(index);
					if (entry)
						if (entry->isType(type))
							return entry->getData().get();
					return nullptr;
				}

				void JSONArray::putEntry(const int index, std::unique_ptr<JSONEntry>& ptr)
				{
					if (!ptr.get())
						return;
					getEntries().insert(getEntries().begin() + index, std::unique_ptr<JSONEntry>(ptr.release()));
				}

				void JSONArray::addEntry(std::unique_ptr<JSONEntry>& ptr)
				{
					if (!ptr.get())
						return;
					getEntries().push_back(std::unique_ptr<JSONEntry>(ptr.release()));
				}

				JSONArray::JSONArray() :
					JSONEntry(ARRAY, new std::vector<std::unique_ptr<JSONEntry>>())
				{}

				int JSONArray::length()
				{
					return getEntries().size();
				}

				std::vector<std::unique_ptr<JSONEntry>>& JSONArray::getEntries()
				{
					return *((std::vector<std::unique_ptr<JSONEntry>>*)nullptr);
				}

				JSONEntry::Type JSONArray::typeOf(const int index)
				{
					const JSONEntry* entry = get<JSONEntry>(index);
					if (entry)
						return entry->getType();
					return NONE;
				}
				
				template<> bool* JSONArray::get<bool>(const int index)
				{
					return (bool*)getEntryValueOfType(BOOL, index);
				}

				template<> int* JSONArray::get<int>(const int index)
				{
					return (int*)getEntryValueOfType(INT, index);
				}

				template<> float* JSONArray::get<float>(const int index)
				{
					return (float*)getEntryValueOfType(FLOAT, index);
				}

				template<> std::string* JSONArray::get<std::string>(const int index)
				{
					return (std::string*)getEntryValueOfType(STRING, index);
				}

				template<> JSONEntry* JSONArray::get<JSONEntry>(const int index)
				{
#ifdef SEG_API_DEBUG_THROW
					if (index < 0 || index >= getEntries().size())
						throw ArrayIndexOutOfBoundsException(index);
#endif
					return getEntries().at(index).get();
				}

				template<> JSONObject* JSONArray::get<JSONObject>(const int index)
				{
					return (JSONObject*)get<JSONEntry>(index);
				}

				template<> JSONArray* JSONArray::get<JSONArray>(const int index)
				{
					return (JSONArray*)get<JSONEntry>(index);
				}

				void JSONArray::put(const int index, const bool value)
				{
					putEntry(index, std::unique_ptr<JSONEntry>(new JSONEntry(BOOL, new bool(value))));
				}

				void JSONArray::put(const int index, const int value)
				{
					putEntry(index, std::unique_ptr<JSONEntry>(new JSONEntry(INT, new int(value))));
				}

				void JSONArray::put(const int index, const float value)
				{
					putEntry(index, std::unique_ptr<JSONEntry>(new JSONEntry(FLOAT, new float(value))));
				}

				void JSONArray::put(const int index, const std::string& value)
				{
					putEntry(index, std::unique_ptr<JSONEntry>(new JSONEntry(STRING, new std::string(value))));
				}

				void JSONArray::put(const int index, JSONEntry* entry)
				{
					putEntry(index, std::unique_ptr<JSONEntry>(entry));
				}

				void JSONArray::add(const bool value)
				{
					addEntry(std::unique_ptr<JSONEntry>(new JSONEntry(BOOL, new bool(value))));
				}

				void JSONArray::add(const int value)
				{
					addEntry(std::unique_ptr<JSONEntry>(new JSONEntry(INT, new int(value))));
				}

				void JSONArray::add(const float value)
				{
					addEntry(std::unique_ptr<JSONEntry>(new JSONEntry(FLOAT, new float(value))));
				}

				void JSONArray::add(const std::string& value)
				{
					addEntry(std::unique_ptr<JSONEntry>(new JSONEntry(STRING, new std::string(value))));
				}

				void JSONArray::add(JSONEntry* entry)
				{
					addEntry(std::unique_ptr<JSONEntry>(entry));
				}

				void JSONArray::remove(const int index)
				{
					getEntries().erase(getEntries().begin() + index);
				}

				void JSONArray::clear()
				{
					getEntries().clear();
				}

			}

		}

	}

}