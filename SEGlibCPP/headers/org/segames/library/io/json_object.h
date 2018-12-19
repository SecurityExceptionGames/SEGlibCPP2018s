#pragma once
#include<org\segames\library\io\json_entry.h>

#include <unordered_map>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace io
			{

				/*
					The class housing a JSON object

					* @author	Philip Rosberg
					* @since	2018-12-01
					* @edited	2018-12-01
				*/
				class SEG_API JSONObject :
					public JSONEntry
				{
				protected:

					/*
						Returns a pointer to the value of the entry of the given name
						* @param[in] type The type of the entry
						* @param[in] name The name of the entry
					*/
					virtual char* getEntryValueOfType(const JSONEntry::Type type, const std::string& name);

					/*
						Places the given JSON entry at the given name
						* @param[in] name The name of the entry
						* @param[in] ptr A pointer to the JSON entry to add
					*/
					virtual void putEntry(const std::string& name, std::unique_ptr<JSONEntry>& ptr);

				public:

					/*
						Creates a JSON object
					*/
					JSONObject();

					/*
						Returns the entries of the object entries/members
					*/
					virtual std::unordered_map<std::string, std::unique_ptr<JSONEntry>>& getEntries();

					/*
						Returns the type of the entry with the given name, returns NONE if there is no entry of that name
						* @param[in] name The name of the entry
					*/
					virtual JSONEntry::Type typeOf(const std::string& name);

					/*
						Returns the entry of the given type and name
						* @param[in] name The name of the entry
					*/
					template<typename T> T* get(const std::string& name);

					/*
						Puts the given value at the given name, overrides any entry that already exists at that name
						* @param[in] name The name of the entry
						* @param[in] value The value to put in the object
					*/
					virtual void put(const std::string& name, const bool value);

					/*
						Puts the given value at the given name, overrides any entry that already exists at that name
						* @param[in] name The name of the entry
						* @param[in] value The value to put in the object
					*/
					virtual void put(const std::string& name, const int value);

					/*
						Puts the given value at the given name, overrides any entry that already exists at that name
						* @param[in] name The name of the entry
						* @param[in] value The value to put in the object
					*/
					virtual void put(const std::string& name, const float value);

					/*
						Puts the given value at the given name, overrides any entry that already exists at that name
						* @param[in] name The name of the entry
						* @param[in] value The value to put in the object
					*/
					virtual void put(const std::string& name, const std::string& value);

					/*
						Puts the given JSON entry at the given name, overrides any entry that already exists at that name
						* @param[in] name The name of the entry
						* @param[in] entry The JSON entry to put in the object
					*/
					virtual void put(const std::string& name, JSONEntry* entry);

					/*
						Removes the entry of the given name
						* @param[in] name The name of the entry
					*/
					virtual void remove(const std::string& name);

					/*
						Empties the JSON object
					*/
					virtual void clear();

					/*
						Returns a string representation of the object
					*/
					virtual std::string toString() const;

				};

			}

		}

	}

}