#include <iostream>
#include <stdint.h>
#include <sys/time.h>


// The general-purpose GeneralTimestamp. It does not know about Napatech etc..
struct GeneralTimestamp
{
    // explicit!
    explicit GeneralTimestamp(int64_t ns) : ns(ns) {}

    // explicit!
    explicit GeneralTimestamp(uint64_t ns) : ns(static_cast<int64_t>(ns)) {}

    // store signed value (negative is possible)
    int64_t ns; // 1 ns
};


inline bool operator==(const GeneralTimestamp& lhs, const GeneralTimestamp& rhs)
{
    return lhs.ns == rhs.ns;
}

// difference type is integer 
inline int64_t operator-(const GeneralTimestamp& lhs, const GeneralTimestamp& rhs)
{
    return lhs.ns - rhs.ns;
}


inline bool operator<(const GeneralTimestamp& lhs, const GeneralTimestamp& rhs)
{
    return lhs.ns < rhs.ns;
}


struct NapatechTimestamp
{
    // explicit!
    explicit NapatechTimestamp(uint64_t ts) : ts(ts) {}

    // implicit (non-lossy conversion to the general type)
    operator GeneralTimestamp() const { return GeneralTimestamp(10 * ts); }

    uint64_t ts; // 10 ns units
};


struct LinuxTimestamp
{
    // default constructor (no CPU cost, apart from zero-initialization)
    LinuxTimestamp() : tv() {}

    // explicit!
    explicit LinuxTimestamp(timeval tv) : tv(tv) {}

    // named constructor enables a convenient syntax:
    //  auto ts = LinuxTimestamp::now();
    static LinuxTimestamp now()
    {
        timeval tv;
        gettimeofday(&tv, 0);
        return LinuxTimestamp(tv);
    }

    // implicit conversion to the general type
    operator GeneralTimestamp() const { return GeneralTimestamp(1000000000ul * tv.tv_sec + 1000ul * tv.tv_usec); }

    timeval tv;
};


int main()
{
    // static polymorphism! :D    
    
    // compare different types (but it's correct, non-lossy and convenient)
    if (NapatechTimestamp(123) < LinuxTimestamp::now())
    {        
        std::cout << "less than" << std::endl;
    }    
    
    auto latency = LinuxTimestamp::now() - NapatechTimestamp(139471884053976277);
    std::cout << "latency: " << latency << std::endl;
}

