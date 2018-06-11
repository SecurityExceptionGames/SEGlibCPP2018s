#include <org\segames\library\util\thread.h>

#include <org\segames\library\util\array_list.h>

using namespace std;

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{

				ThreadException::ThreadException() :
					Exception()
				{}

				ThreadException::ThreadException(const string& message) :
					Exception(message)
				{}

				/*
					The list of depleted threads
				*/
				VolatileVar<ArrayList<thread*>> threadDeadThreads(ArrayList<thread*>(1));

				/*
					Method called by thread on start
					* @param[in] runnable The runnable instance to call, must not be nullptr
				*/
				void threadStartThread(Runnable* runnable, VolatileVar<thread*>& threadRef)
				{
					runnable->run();

					unique_ptr<thread> ptr(nullptr);
					{
						auto& volVar = threadRef;
						SyncLock<thread*> lock(volVar);
						ptr.swap(unique_ptr<thread>(*volVar));
						*volVar = nullptr;
					}

					if (ptr.get())
					{
						SyncLock<ArrayList<thread*>> lock(threadDeadThreads);
						(*threadDeadThreads).add(ptr.release());
					}

				}

				Thread::Thread() :
					Thread(nullptr)
				{}

				Thread::Thread(Runnable* runnable_) :
					runnable(runnable_),
					nativeThread(nullptr)
				{}

				Thread::Thread(const Thread& obj) :
					Thread(obj.runnable)
				{}

				Thread::~Thread()
				{
					SyncLock<ArrayList<thread*>> lock(threadDeadThreads);

					ArrayList<thread*>& list = *threadDeadThreads;
					for (size_t i = 0; i < list.size(); i++)
					{
						thread* ptr = list.get(i);
						ptr->join();
						delete ptr;
					}
					list.clear();
				}

				bool Thread::isRunning() const noexcept
				{
					return (*nativeThread) != nullptr;
				}

				void Thread::start()
				{
#ifdef SEG_API_DEBUG_THROW
					if (!runnable)
						throw ThreadException("Cannot start thread without a runnable.");
					if (isRunning())
						throw ThreadException("Cannot start thread twice.");
#endif
					{
						SyncLock<thread*> lock(nativeThread);
						*nativeThread = new std::thread();
						(**nativeThread) = std::thread(threadStartThread, runnable, nativeThread);
					}

				}

				Thread& Thread::operator=(const Thread& obj)
				{
					if (isRunning())
						throw ThreadException("Cannot copy to a started thread.");
					runnable = obj.runnable;
					nativeThread = VolatileVar<thread*>(nullptr);
					return *this;
				}

			}

		}

	}

}