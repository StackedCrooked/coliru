#include <stdint.h>
#include <chrono>
#include <iostream>
#include <string>
#include <sstream>


using Nanoseconds = std::chrono::nanoseconds;
using Microseconds = std::chrono::microseconds;
using Milliseconds = std::chrono::milliseconds;
using Seconds = std::chrono::seconds;

std::ostream& operator<<(std::ostream& os, const Nanoseconds& ns) { return os << ns.count() << "ns"; }
std::ostream& operator<<(std::ostream& os, const Microseconds& us) { return os << us.count() << "us"; }
std::ostream& operator<<(std::ostream& os, const Milliseconds& ms) { return os << ms.count() << "ms"; }
std::ostream& operator<<(std::ostream& os, const Seconds& s) { return os << s.count() << "s"; }


 
class FriendlyDuration
{
public:
    explicit FriendlyDuration(int64_t inNanoseconds) : mNanoseconds(inNanoseconds) {}
    /*implicit*/ FriendlyDuration(Nanoseconds inNanoseconds) : mNanoseconds(inNanoseconds.count()) {}
    /*implicit*/ FriendlyDuration(Microseconds inMicroseconds) : mNanoseconds(1000L * inMicroseconds.count()) {}
    /*implicit*/ FriendlyDuration(Milliseconds inMilliseconds) : mNanoseconds(1000L * 1000L * inMilliseconds.count()) {}
    /*implicit*/ FriendlyDuration(Seconds inSeconds) : mNanoseconds(1000L * 1000L * 1000L * inSeconds.count()) {}

    std::string toString() const
    {
        enum : int64_t
        {
            thousand = 1000L,
            million  = 1000L * thousand,
            billion  = 1000L * million
        };
        
        const double rounding = 1.0;
        
        std::stringstream ss;

        if (mNanoseconds < thousand)
        {
            ss << mNanoseconds << "ns";
        }
        else if (mNanoseconds < million)
        {
            ss << int64_t(0.5 + rounding * mNanoseconds / thousand) / rounding << "us";
        }
        else if (mNanoseconds < billion)
        {
            ss << int64_t(0.5 + rounding * mNanoseconds / million) / rounding << "ms";
        }
        else
        {
            ss << int64_t(0.5 + 1.0 * mNanoseconds / billion) << "s";
        }
        return ss.str();
    }
    
    Nanoseconds getNanoseconds() const
    {
        return Nanoseconds{mNanoseconds};
    }
    
    Microseconds getMicroseconds() const
    {
        return std::chrono::duration_cast<Microseconds>(getNanoseconds());
    }
    
    Milliseconds getMilliseconds() const
    {
        return std::chrono::duration_cast<Milliseconds>(getNanoseconds());
    }
    
    Seconds getSeconds() const
    {
        return std::chrono::duration_cast<Seconds>(getNanoseconds());
    }
    
    friend std::ostream& operator<<(std::ostream& os, const FriendlyDuration& duration)
    {
        return os << duration.toString();
    }
    
private:
    int64_t mNanoseconds;
};


int main()
{
    double x = 1;
    for (int i = 0; i != 100; ++i)
    {
        std::cout << x
            << " " << FriendlyDuration(x).getNanoseconds()
            << " " << FriendlyDuration(x)
            << std::endl;
        x = x * 1.3;
    }
}