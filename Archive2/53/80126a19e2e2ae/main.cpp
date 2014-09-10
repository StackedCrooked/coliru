#include <stdint.h>
#include <chrono>
#include <iostream>
#include <string>
#include <sstream>


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
    
    int64_t getNanoseconds() const
    {
        return mNanoseconds;
    }
    
    int64_t getMicroseconds() const
    {
        return int64_t(0.5 + getNanoseconds() / 1000.0);
    }
    
    int64_t getMilliseconds() const
    {
        return int64_t(0.5 + getMicroseconds() / 1000.0);
    }
    
    int64_t getSeconds() const
    {
        return int64_t(0.5 + getMilliseconds() / 1000.0);
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
        std::cout
            << Duration(x).getNanoseconds() << "ns "
            << Duration(x).getMicroseconds() << "us "
            << Duration(x).getMilliseconds() << "ms "
            <<  Duration(x) << std::endl;
        x = x * 1.3;
    }
}