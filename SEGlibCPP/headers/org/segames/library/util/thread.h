#pragma once
#include <org\segames\library\object.h>
#include <org\segames\library\exception.h>

#ifdef _WIN32
#ifndef ZeroMemory
#include <Windows.h>
#endif
#else
#include <mutex>
#endif

#include <thread>

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{

				/*
					A thread-wise lockable variable to ensure thread safety

					Usage:
					VolatileVar<int> var(123); //Variable somewhere

					{ //Piece of code changing the volatile variable
						var.lock();

						int& v = var.var();
						v ++;

						var.unlock();
					}

					* @author	Philip Rosberg
					* @since	2018-06-11
					* @edited	2018-06-11
				*/
				template<class T> class VolatileVar
				{
				private:

					/*
						The stored value
					*/
					T value;

#ifdef _WIN32
					/*
						Critical section for windows, faster
					*/
					CRITICAL_SECTION criticalSection;
#else
					/*
						Mutex for non-windows systems, slower
					*/
					std::mutex mutexVar;
#endif // _WIN32

				public:

					/*
						Creates a volatile var without a internal variable
					*/
					VolatileVar()
					{}

					/*
						Creates a volatile var from the given variable
						* @param[in] var The variable to wrap
					*/
					VolatileVar(const T& var) :
						value(var)
					{
#ifdef _WIN32
						InitializeCriticalSection((LPCRITICAL_SECTION)&criticalSection);
#endif // _WIN32
					}

					/*
						Destructor
					*/
					~VolatileVar()
					{
#ifdef _WIN32
						DeleteCriticalSection((LPCRITICAL_SECTION)&criticalSection);
#endif // _WIN32
					}

					/*
						Returns a reference to the stored variable
					*/
					virtual T& var() const noexcept
					{
						return (T&)value;
					}

					/*
						Locks the volatile variable so only one thread can use it at the same time
					*/
					virtual void lock()
					{
#ifdef _WIN32
						EnterCriticalSection((LPCRITICAL_SECTION)&criticalSection);
#else
						mutexVar.lock();
#endif // _WIN32
					}

					/*
						Unlocks the volatile variable
					*/
					virtual void unlock()
					{
#ifdef _WIN32
						LeaveCriticalSection((LPCRITICAL_SECTION)&criticalSection);
#else
						mutexVar.unlock();
#endif // _WIN32
					}

					/*
						Returns a reference to the stored variable, same as var()
					*/
					virtual T& operator*() const noexcept
					{
						return var();
					}

				};

				/*
					A more exception safe variant of VolatileVar<T>::lock() and VolatileVar<T>::unlock()

					Usage:
					VolatileVar<int> var(123); //Variable somewhere

					{ //Piece of code changing the volatile variable
						SyncLock<int> lock(var);

						int& v = var.var();
						v ++;
					}

					* @author	Philip Rosberg
					* @since	2018-06-11
					* @edited	2018-06-11
				*/
				template<class T> class SyncLock
				{
				private:

					/*
						The volatile var to lock and unlock
					*/
					VolatileVar<T>& volatileVar;

				public:

					/*
						Creates a thread-synchronization lock on the given volatle var
						* @param[in] var The volatile variable to lock
					*/
					SyncLock(const VolatileVar<T>& var) :
						volatileVar((VolatileVar<T>&)var)
					{
						volatileVar.lock();
					}

					/*
						Destructor
					*/
					~SyncLock()
					{
						volatileVar.unlock();
					}

				};

				/*
					Exception class for threading related exceptions

					* @author	Philip Rosberg
					* @since	2018-06-11
					* @edited	2018-06-11
				*/
				class SEG_API ThreadException :
					public Exception
				{
				public:

					/*
						Creates a thread exception with no message
					*/
					ThreadException();

					/*
						Creates a thread exception with the given message
						* @param[in] message The exception message
					*/
					ThreadException(const std::string& message);

				};

				/*
					Runnable interface, used to setup a Thread instance

					* @author	Philip Rosberg
					* @since	2018-06-11
					* @edited	2018-06-11
				*/
				class SEG_API Runnable
				{
				public:

					/*
						Run-method, called when a new thread is started
					*/
					virtual void run() = 0;

				};
				
				/*
					A class for housing a thread.
					WARNING! Does not terminate alive threads!
					Cleanup happends for all dead threads on destruction of one Thread instance

					* @author	Philip Rosberg
					* @since	2018-06-11
					* @edited	2018-06-11
				*/
				class SEG_API Thread :
					public Object
				{
				private:

					/*
						The runnable instance
					*/
					Runnable* runnable;

					/*
						The std::thread housed in a volatile var
					*/
					VolatileVar<std::thread*> nativeThread;

				public:

					/*
						The thread empty constructor, thread cannot be started if this is used
					*/
					Thread();

					/*
						The thread constructor
						* @param[in] runnable The runnable instance, is not freed on destruction
					*/
					Thread(Runnable* runnable);

					/*
						The thread copy constructor, basically same as doing: Thread t = Thread(obj.runnable);
						* @param[in] obj The thread to copy, does not copy the std::thread nor its' state
					*/
					Thread(const Thread& obj);

					/*
						Destructor, cleans globally stored dead threads
					*/
					~Thread();

					/*
						Returns true if the thread is running
					*/
					bool isRunning() const noexcept;

					/*
						Starts the thread
					*/
					void start();

					/*
						Set operator override, only copies the runnable
					*/
					Thread& operator=(const Thread& obj);

				};

			}

		}

	}

}