#include <org\segames\library\io\file.h>

#include <org\segames\library\util\string_util.h>

#include <iostream>
#include <fstream>

using namespace org::segames::library::util;

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace io
			{

				void FileAttributes::loadAttribWindows(const char* path)
				{
#ifdef _WIN32
					DWORD nameLen = GetFullPathNameA(path, 0, nullptr, nullptr);
					std::unique_ptr<char> strBuff(new char[nameLen]);
					GetFullPathNameA(path, nameLen, strBuff.get(), nullptr);
					this->pathAttr = std::string(strBuff.get());

					DWORD attrib = GetFileAttributesA(strBuff.get());
					if (attrib == INVALID_FILE_ATTRIBUTES)
					{
						this->existsAttr = false;
						this->dirAttr = false;
						this->lengthAttr = ZERO;
					}
					else
					{
						this->existsAttr = true;

						if (attrib & FILE_ATTRIBUTE_DIRECTORY)
						{
							this->dirAttr = true;
							this->lengthAttr = ZERO;
						}
						else
						{
							this->dirAttr = false;

							std::ifstream in(strBuff.get(), std::ifstream::ate | std::ifstream::binary);
							signed long long len = in.tellg();
							in.close();

							if (len == -1)
								this->lengthAttr = ZERO;
							else
								this->lengthAttr = (size_t)len;
						}

					}

					this->pathDissectedAttr = stringSplit(pathAttr, SEG_API_SYSTEM_DIR_SEPARATOR);
#endif
				}
				
				FileAttributes::FileAttributes() :
					existsAttr(false),
					dirAttr(false),
					lengthAttr(ZERO),
					pathAttr(""),
					pathDissectedAttr(ZERO)
				{}

				FileAttributes::FileAttributes(const char* path)
				{
#ifdef _WIN32
					if (*path == '\0')
						loadAttribWindows(".\\");
					else
						loadAttribWindows(path);
#endif
				}

				FileAttributes::FileAttributes(const std::string& path) :
					FileAttributes(path.c_str())
				{}

				bool FileAttributes::exists() const
				{
					return existsAttr;
				}

				bool FileAttributes::isDirectory() const
				{
					return dirAttr;
				}

				size_t FileAttributes::length() const
				{
					return lengthAttr;
				}

				size_t FileAttributes::hashCode() const
				{
					return stringHash(pathAttr);
				}

				std::string& FileAttributes::getPath() const
				{
					return (std::string&)pathAttr;
				}

				std::string FileAttributes::toString() const
				{
					return std::string("FileAttributes(") + (exists() ? "E" : "-") + (isDirectory() ? "D" : "F") + "): \"" + getPath() + "\"";
				}

				ArrayList<std::string>& FileAttributes::getPathDissection() const
				{
					return (ArrayList<std::string>&)pathDissectedAttr;
				}

				void FileAttributes::setExisting(const bool flag)
				{
					this->existsAttr = flag;
				}

				void FileAttributes::setDirectory(const bool flag)
				{
					this->dirAttr = flag;
				}

				void FileAttributes::setLength(const size_t length)
				{
					this->lengthAttr = length;
				}

				void FileAttributes::setPath(const std::string& path)
				{
					this->pathAttr = path;
					this->pathDissectedAttr = stringSplit(pathAttr, SEG_API_SYSTEM_DIR_SEPARATOR);
				}

				void FileAttributes::update()
				{
#ifdef _WIN32
					loadAttribWindows(pathAttr.c_str());
#endif
				}

				bool File::createNewFileWindows()
				{
#ifdef _WIN32
					bool retVal = false;
					if (attributes.get())
					{
						HANDLE hand = CreateFileA(getPath().c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
						if (hand != INVALID_HANDLE_VALUE)
						{
							attributes->setExisting(true);
							retVal = true;
						}
						CloseHandle(hand);
					}
					return retVal;
#else
					return false;
#endif
				}

				bool File::mkdirsWindows()
				{
#ifdef _WIN32
					bool retVal = false;
					if (attributes.get())
					{
						std::string tempPath = attributes->getPathDissection().get(0);
						for (size_t i = 1; i < attributes->getPathDissection().size(); i++)
						{
							tempPath += SEG_API_SYSTEM_DIR_SEPARATOR + attributes->getPathDissection().get(i);

							DWORD attrib = GetFileAttributesA(tempPath.c_str());
							if (attrib != INVALID_FILE_ATTRIBUTES)
							{
								retVal = (_mkdir(tempPath.c_str()) != -1);
								if (!retVal)
									break;
							}

						}

					}
					return retVal;
#else
					return false;
#endif
				}

				void File::listFilesWindows(ArrayList<File>& files) const
				{
#ifdef _WIN32
					HANDLE dir;
					WIN32_FIND_DATAA findData;
					if ((dir = FindFirstFileA((getPath() + SEG_API_SYSTEM_DIR_SEPARATOR + "*").c_str(), &findData)) != INVALID_HANDLE_VALUE)
					{
						while (FindNextFileA(dir, &findData))
						{
							std::string name = std::string(findData.cFileName);
							if(name != "..")
								files.add(File(getPath() + SEG_API_SYSTEM_DIR_SEPARATOR + findData.cFileName));
						}
						FindClose(dir);
					}
#endif
				}

				File::File() :
					attributes(nullptr)
				{}

				File::File(const char* path) :
					attributes(path ? new FileAttributes(path) : nullptr)
				{}

				File::File(const std::string& path) :
					File(path.c_str())
				{}

				File::File(const FileAttributes& attrib) :
					attributes(new FileAttributes(attrib))
				{}

				File::File(const File& obj) :
					attributes(obj.attributes)
				{}

				bool File::isNull() const
				{
					return !attributes.get();
				}

				bool File::exists() const
				{
					if (attributes.get())
						return attributes->exists();
					return false;
				}

				bool File::isDirectory() const
				{
					if (attributes.get())
						return attributes->isDirectory();
					return false;
				}

				bool File::createNewFile()
				{
#ifdef _WIN32
					return createNewFileWindows();
#else
					return false;
#endif
				}

				bool File::deleteFile()
				{
					if (attributes.get())
						if (std::remove(getPath().c_str()) == ZERO)
						{
							attributes->setExisting(false);
							return true;
						}
					return false;
				}

				bool File::mkdirs()
				{
#ifdef _WIN32
					return mkdirsWindows();
#else
					return false;
#endif
				}
				
				bool File::renameTo(const char* path)
				{
					if(attributes.get())
						if (std::rename(getPath().c_str(), path) == ZERO)
						{
							this->attributes = std::shared_ptr<FileAttributes>(new FileAttributes(path));
							return true;
						}
					return false;
				}

				bool File::renameTo(const std::string& path)
				{
					return renameTo(path.c_str());
				}

				bool File::renameTo(const FileAttributes& attrib)
				{
					return renameTo(attrib.getPath());
				}

				bool File::renameTo(const File& file)
				{
					return renameTo(file.getPath());
				}

				size_t File::length() const
				{
					if (attributes.get())
						return attributes->length();
					return false;
				}

				size_t File::hashCode() const
				{
					if (attributes.get())
						return attributes->hashCode();
					return 0;
				}

				std::string& File::getName() const
				{
					return attributes->getPathDissection().get(attributes->getPathDissection().size() - 1);
				}

				std::string& File::getPath() const
				{
					return attributes->getPath();
				}

				std::string File::getParent() const
				{
					if (attributes.get())
						return stringConcat(std::string("") + SEG_API_SYSTEM_DIR_SEPARATOR, attributes->getPathDissection().begin(), --attributes->getPathDissection().end());
					return "";
				}
				
				std::string File::toString() const
				{
					return std::string("File(") + (exists() ? "E" : "-") + (isDirectory() ? "D" : "F") + "): \"" + getPath() + "\"";
				}

				File File::getParentFile() const
				{
					return File(getParent());
				}

				void File::listFiles(ArrayList<File>& files) const
				{
#ifdef _WIN32
					listFilesWindows(files);
#endif
				}

				ArrayList<File> File::listFiles() const
				{
					ArrayList<File> list(1);
					listFiles(list);
					return list;
				}

				void File::update()
				{
					if (attributes.get())
						attributes->update();
				}

			}

		}

	}

}