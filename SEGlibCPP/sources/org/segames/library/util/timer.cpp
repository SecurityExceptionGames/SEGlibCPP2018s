#include <org\segames\library\util\timer.h>

#include <org\segames\library\invalid_value_exception.h>

#include <thread>

using namespace std::chrono;

namespace org
{

	namespace segames
	{

		namespace library
		{

			namespace util
			{

				size_t Timer::nanoTime()
				{
					return (size_t)duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
				}

				size_t Timer::microTime()
				{
					return (size_t)duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()).count();
				}

				size_t Timer::milliTime()
				{
					return (size_t)duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
				}

				Timer::Timer() :
					updateRate(ZERO),
					updateTime(ZERO),
					lastTime(-1)
				{}

				Timer::Timer(const double updateRate_) :
					updateRate(updateRate_),
					updateTime(updateRate_ != 0 ? 1.0 / updateRate_ : ZERO),
					lastTime(-1)
				{}

				bool Timer::time()
				{
					if (updateRate < 0)
						return false;
					else if (updateRate == 0)
						return true;
					else
					{
						const size_t time = nanoTime() - lastTime;

						if (time > 1000000000.0 * updateTime)
						{
							lastTime = time;
							return true;
						}
						else
							return false;
					}

				}

				double Timer::deltaTime()
				{
					double out = 1.0;
					if (lastTime == -1)
					{
						if (updateTime != 0)
							out = updateTime;
					}
					else
						out = (nanoTime() - lastTime) / 1000000000.0;
					
					lastTime = nanoTime();
					return out;
				}

				double Timer::getUpdateRate() const
				{
					return updateRate;
				}

				double Timer::getUpdateTime() const
				{
					return updateTime;
				}

				void Timer::setUpdateRate(const double updateRate_)
				{
					this->updateRate = updateRate_;
					this->updateTime = (updateRate_ != 0 ? 1.0 / updateRate_ : ZERO);
				}

				void Timer::sync()
				{
					if (lastTime == -1)
					{
						lastTime = nanoTime();
						return;
					}

#ifdef SEG_API_DEBUG_THROW
					if (updateTime <= 0.0)
						throw InvalidValueException("Cannot sync time for update rates less than or equal to zero.");
#endif

					size_t sleep = (size_t)(updateTime * 1000000000.0) - (nanoTime() - lastTime);
					if (sleep > 0)
						std::this_thread::sleep_for(nanoseconds(sleep));
					lastTime = nanoTime();
				}

			}

		}

	}

}