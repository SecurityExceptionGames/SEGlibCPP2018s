#pragma once
#include <org\segames\library\object.h>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace io
			{
				
				/*
					Super class for JSON entries

					* @author	Philip Rosberg
					* @since	2018-12-01
					* @edited	2018-12-01
				*/
				class SEG_API JSONEntry :
					public Object
				{
				public:

					/*
						JSON-entry type enumeration

						* @author	Philip Rosberg
						* @since	2018-12-01
						* @edited	2018-12-01
					*/
					enum Type
					{
						NONE,		//No entry exists
						NULL_,
						BOOL,
						INT,
						FLOAT,
						STRING,
						OBJECT,
						ARRAY
					};

				protected:

					/*
						The type of the entry
					*/
					Type type;

					/*
						The data of the entry
					*/
					std::unique_ptr<char> data;

				public:

					/*
						Creates an empty JSON entry of type boolean
					*/
					JSONEntry();

					/*
						Creates a JSON entry
						* @param[in] type The entry type
						* @param[in] ptr The data to store
					*/
					JSONEntry(const Type type, void* ptr);

					/*
						Returns true if the type of this entry is the same as the given type
						* @param[in] type The entry type
					*/
					virtual bool isType(const Type type) const;

					/*
						Returns the type of this entry
					*/
					virtual Type getType() const;

					/*
						Returns a reference to the stored data
					*/
					virtual const std::unique_ptr<char>& getData() const;

					/*
						Returns a string representation of the value
					*/
					virtual std::string toString() const;

					/*
						Returns a string representation of the value
					*/
					virtual std::string toString() const;

				};

			}

		}

	}

}