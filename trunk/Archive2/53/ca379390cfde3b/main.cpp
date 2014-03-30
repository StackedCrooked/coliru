
template<typename T>
struct BenchmarkTimer
{
    struct Info
    {
        Info() : mFunctionName(), mCount(), mTotalTime()
        {
        }

        ~Info()
        {
            if (mFunctionName)
            {
                log(Critical)
                    << (mTotalTime.count() / 1000)
                    << " " << mCount
                    << " " << int(0.5 + 1.0 * mTotalTime.count() / mCount)
                    << " " << GetTypeNameWithoutNamespaces<T>() << "::" << mFunctionName
                       ;
            }

        }

        void increment(const Clock::time_point& start_time)
        {
            mCount++;
            if (mCount % 10 == 0)
            {
                auto ns = duration_cast<nanoseconds>(Clock::now() - start_time);
                mTotalTime += 10 * ns;
            }
        }

        const char* mFunctionName;
        long mCount;
        nanoseconds mTotalTime;
    };

    struct Timer
    {
        Timer(const char* function_name, Info& info) :
            mStartTime(Clock::now()),
            mInfo(info)
        {
            mInfo.mFunctionName = function_name;
        }

        Timer(Timer&&) = default;
        Timer& operator=(Timer&&) = default;

        Timer(const Timer&) = delete;
        Timer& operator=(const Timer&) = delete;

        ~Timer()
        {
            mInfo.increment(mStartTime);
        }

        Clock::time_point mStartTime;
        Info& mInfo;
    };

    Timer start(int index, const char* name)
    {
        return Timer(name, mArray[index]);
    }


    std::array<Info, 10> mArray;
};

