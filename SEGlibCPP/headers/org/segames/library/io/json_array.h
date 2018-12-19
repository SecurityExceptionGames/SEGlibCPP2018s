#pragma once
#include <org\segames\library\io\json_entry.h>

#include <vector>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace io
			{

				/*
					The class housing a JSON array

					* @author	Philip Rosberg
					* @since	2018-12-03
					* @edited	2018-12-03
				*/
				class SEG_API JSONArray :
					public JSONEntry
				{
				protected:

					/*
						Returns a pointer to the value of the entry of the given index
						* @param[in] type The type of the entry
						* @param[in] index The index of the entry
					*/
					virtual char* getEntryValueOfType(const JSONEntry::Type type, const int index);
					
					/*
						Places the given JSON entry at the given index
						* @param[in] index The index of the entry
						* @param[in] ptr A pointer to the JSON entry to add
					*/
					virtual void putEntry(const int index, std::unique_ptr<JSONEntry>& ptr);

					/*
						Places the given JSON entry at the end of the list
						* @param[in] ptr A pointer to the JSON entry to add
					*/
					virtual void addEntry(std::unique_ptr<JSONEntry>& ptr);

				public:

					/*
						Creates a JSON array
					*/
					JSONArray();
					
					/*
						Returns the length of the JSON array
					*/
					virtual int length();

					/*
						Returns the entries of the array entries/members
					*/
					virtual std::vector<std::unique_ptr<JSONEntry>>& getEntries();

					/*
						Returns the type of the entry with the given index, returns NONE if there is no entry of that index
						* @param[in] index The index of the entry
					*/
					virtual JSONEntry::Type typeOf(const int index);

					/*
						Returns the entry of the given type and index
						* @param[in] index The index of the entry
					*/
					template<typename T> T* get(const int index);

					/*
						Puts the given value at the given index, overrides any entry that already exists at that index
						* @param[in] index The index of the entry
						* @param[in] value The value to put in the array
					*/
					virtual void put(const int index, const bool value);

					/*
						Puts the given value at the given index, overrides any entry that already exists at that index
						* @param[in] index The index of the entry
						* @param[in] value The value to put in the array
					*/
					virtual void put(const int index, const int value);

					/*
						Puts the given value at the given index, overrides any entry that already exists at that index
						* @param[in] index The index of the entry
						* @param[in] value The value to put in the array
					*/
					virtual void put(const int index, const float value);

					/*
						Puts the given value at the given index, overrides any entry that already exists at that index
						* @param[in] index The index of the entry
						* @param[in] value The value to put in the array
					*/
					virtual void put(const int index, const std::string& value);

					/*
						Puts the given JSON entry at the given index, overrides any entry that already exists at that index
						* @param[in] index The index of the entry
						* @param[in] entry The JSON entry to put in the array
					*/
					virtual void put(const int index, JSONEntry* entry);

					/*
						Puts the given value at the end of the array, overrides any entry that already exists at that index
						* @param[in] value The value to add to the array
					*/
					virtual void add(const bool value);

					/*
						Puts the given value at the end of the array, overrides any entry that already exists at that index
						* @param[in] value The value to add to the array
					*/
					virtual void add(const int value);

					/*
						Puts the given value at the end of the array, overrides any entry that already exists at that index
						* @param[in] value The value to add to the object
					*/
					virtual void add(const float value);

					/*
						Puts the given value at the end of the array, overrides any entry that already exists at that index
						* @param[in] value The value to add to the array
					*/
					virtual void add(const std::string& value);

					/*
						Puts the given JSON entry at the end of the array, overrides any entry that already exists at that index
						* @param[in] entry The JSON entry to add to the array
					*/
					virtual void add(JSONEntry* entry);

					/*
						Removes the entry of the given name
						* @param[in] index The index of the entry
					*/
					virtual void remove(const int index);

					/*
						Empties the JSON object
					*/
					virtual void clear();

				};

			}

		}

	}

}