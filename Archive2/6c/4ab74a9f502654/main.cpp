


struct Benchmark
{
    template<typename T>
    Benchmark(T&, const char* function, const char* file, int line) :
        mClassName(GetTypeNameWithoutNamespaces<T>()),
        function(function),
        file(file),
        line(line),
        start(Clock::now())
    {
    }

    ~Benchmark()
    {
        static std::atomic<unsigned> counter_;
        counter_++;
        if (counter_++ >= 1000 && counter_++ < 2000)
        {
            auto ns = std::chrono::duration_cast<Nanoseconds>(Clock::now() - start);
            EXCENTIS_LOG(Critical) << mClassName << "::" << function << " duration=" << ns;
        }
    }

    std::string mClassName;
    const char* function;
    const char* file;
    int line;
    Clock::time_point start;
};

#define BENCHMARK(thisPtr) Benchmark benchmark_(thisPtr, __FUNCTION__, __FILE__, __LINE__)