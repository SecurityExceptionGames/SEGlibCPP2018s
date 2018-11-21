#pragma once
#include <org\segames\library\util\array_list.h>

#ifdef _WIN32
#include <Windows.h>
#include <direct.h>
#endif

#ifndef SEG_API_SYSTEM_DIR_SEPARATOR
#ifdef _WIN32
#define SEG_API_SYSTEM_DIR_SEPARATOR_CHAR '\\'
#define SEG_API_SYSTEM_DIR_SEPARATOR "\\"
#else
#define SEG_API_SYSTEM_DIR_SEPARATOR_CHAR '/'
#define SEG_API_SYSTEM_DIR_SEPARATOR "/"
#endif
#endif // !SEG_API_SYSTEM_DIR_SEPARATOR

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace io
			{

				/*
					A class storing the attributes of a file, initialized on creation, copied on copy

					* @author	Philip Rosberg
					* @since	2018-11-05
					* @edited	2018-11-05
				*/
				class SEG_API FileAttributes :
					public Object
				{
				protected:

					/*
						True if the file exists
					*/
					bool existsAttr;

					/*
						True if the file is a directory
					*/
					bool dirAttr;

					/*
						The length/size of the file
					*/
					size_t lengthAttr;

					/*
						The file path
					*/
					std::string pathAttr;

					/*
						The file path dissected
					*/
					util::ArrayList<std::string> pathDissectedAttr;

					/*
						Loads the attributes using the windows library
						* @param[in] path The path of the file
					*/
					virtual void loadAttribWindows(const char* path);

				public:

					/*
						Creates an empty file attributes object
					*/
					FileAttributes();

					/*
						Loads the file attributes for the given path
						* @param[in] path The path of the file
					*/
					FileAttributes(const char* path);

					/*
						Loads the file attributes for the given path
						* @param[in] path The path of the file
					*/
					FileAttributes(const std::string& path);

					/*
						Returns true if the file exists
					*/
					virtual bool exists() const;

					/*
						Returns true if the given file is a directory
					*/
					virtual bool isDirectory() const;

					/*
						Returns the length of the file in num. bytes
					*/
					virtual size_t length() const;

					/*
						Returns a hash code from the path
					*/
					virtual size_t hashCode() const;

					/*
						Returns the file path (absolute)
					*/
					virtual std::string& getPath() const;

					/*
						Returns a string representation of the file attributes
					*/
					virtual std::string toString() const;

					/*
						Retruns the path dissected into all sub-parts
					*/
					virtual util::ArrayList<std::string>& getPathDissection() const;

					/*
						Sets if the file exists or not
						* @param[in] flag True if the file exists
					*/
					virtual void setExisting(const bool flag);

					/*
						Sets if the file is a directory or not
						* @param[in] float True if the file is a directory
					*/
					virtual void setDirectory(const bool flag);

					/*
						Sets the file representation length
						* @param[in] length The length of the file
					*/
					virtual void setLength(const size_t length);

					/*
						Sets the path of the file representation
						* @param[in] path The path
					*/
					virtual void setPath(const std::string& path);

					/*
						Updates the file attributes
					*/
					virtual void update();

				};

				/*
					A class for representing a file in the standard file system.
					Note! This class is not thread safe, which means that a file instance
					should not be copied from one thread to another. Copying using the
					file attributes is thread safe (as thread safe as the os allows it to be).

					* @author	Philip Rosberg
					* @since	2018-11-05
					* @edited	2018-11-05
				*/
				class SEG_API File :
					public Object
				{
				protected:

					/*
						The file attributes, eg. path, existance etc.
					*/
					std::shared_ptr<FileAttributes> attributes;

					/*
						Creates a new file using the windows library and returns true if the creation succeeded
					*/
					virtual bool createNewFileWindows();

					/*
						Creates the directory to this directory using the windows library
					*/
					virtual bool mkdirsWindows();

					/*
						Lists the sub files and folders of this file using the windows library
						* @param[out] files The arraylist to place the files in
					*/
					virtual void listFilesWindows(util::ArrayList<File>& files) const;

				public:

					/*
						Creates an empty file object
					*/
					File();

					/*
						Creates a new file representation from the given path
						* @param[in] path The path of the file
					*/
					File(const char* path);

					/*
						Creates a new file representation from the given path
						* @param[in] path The path of the file
					*/
					File(const std::string& path);

					/*
						Creates a copy of the file representation from the given file attributes (Thread safe copying)
						* @param[in] attrib The file attributes, gets copied
					*/
					File(const FileAttributes& attrib);

					/*
						Creates a copy of the file representation (Not 100% thread safe copying)
						* @param[in] obj The file instance to copy
					*/
					File(const File& obj);

					/*
						Returns true if the file attributes is null
					*/
					virtual bool isNull() const;

					/*
						Returns true if the file exists
					*/
					virtual bool exists() const;

					/*
						Returns true if the given file is a directory
					*/
					virtual bool isDirectory() const;

					/*
						Creates a new file and returns true if the creation succeeded
					*/
					virtual bool createNewFile();

					/*
						Deletes the file or directory denoted by this path
					*/
					virtual bool deleteFile();

					/*
						Creates the directory to this directory
					*/
					virtual bool mkdirs();

					/*
						Renames the file denoted by this pathname
						* @param[in] path The path to rename to
					*/
					virtual bool renameTo(const char* path);

					/*
						Renames the file denoted by this pathname
						* @param[in] path The path to rename to
					*/
					virtual bool renameTo(const std::string& path);

					/*
						Renames the file denoted by this pathname
						* @param[in] attrib The file attributes to rename to
					*/
					virtual bool renameTo(const FileAttributes& attrib);

					/*
						Renames the file denoted by this pathname
						* @param[in] file The file to rename to
					*/
					virtual bool renameTo(const File& file);

					/*
						Returns the length of the file in num. bytes
					*/
					virtual size_t length() const;

					/*
						Returns a hash code from the path
					*/
					virtual size_t hashCode() const;

					/*
						Returns the name (the last part of the path) of the file
					*/
					virtual std::string& getName() const;

					/*
						Returns the file path (absolute)
					*/
					virtual std::string& getPath() const;

					/*
						Returns the path to the parent file
					*/
					virtual std::string getParent() const;

					/*
						Returns a string representation of the file attributes
					*/
					virtual std::string toString() const;

					/*
						Returns the parent file or directory of this file
					*/
					virtual File getParentFile() const;

					/*
						Lists the sub files and folders of this file
						* @param[out] files The arraylist to place the files in
					*/
					virtual void listFiles(util::ArrayList<File>& files) const;

					/*
						Returns an arraylist with the with the sub files of this file listed
					*/
					virtual util::ArrayList<File> listFiles() const;

					/*
						Updates the file attributes
					*/
					virtual void update();

				};

			}

		}

	}

}