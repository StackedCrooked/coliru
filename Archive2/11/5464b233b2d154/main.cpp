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




class Duration
{
public:
    Duration(double inNanosconds) : mNanoseconds(0.5 + inNanosconds) {}
    Duration(std::chrono::nanoseconds inNanosconds) : mNanoseconds(inNanosconds.count()) {}

    std::string toString() const
    {
        enum : int64_t { thousand = 1000, million = 1000 * thousand, billion = 1000 * million };
        
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
    
    friend std::ostream& operator<<(std::ostream& os, const Duration& duration)
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
            << " " << Duration(x).getNanoseconds()
            << " " << Duration(x)
            << std::endl;
        x = x * 1.3;
    }
}