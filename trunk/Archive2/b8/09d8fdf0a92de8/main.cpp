#include <iostream>
#include <limits>
#include <stdint.h>
#include <boost/optional.hpp>


template<typename T>
using Optional = boost::optional<T>;


template<typename T>
struct Maximum
{   
    void set(T inValue)
    {
        if (!mValue || *mValue < inValue)
        {
            mValue = inValue;
        }
    }
    
    T get_or(T t) const
    {
        return mValue ? *mValue : t;
    }
    
private:
    Optional<T> mValue;
};


template<typename T>
struct Minimum
{
    void set(T inValue)
    {
        if (!mValue || inValue < mValue)
        {
            mValue = inValue;
        }
    }
    
    T get_or(T t) const
    {
        return mValue ? *mValue : t;
    }
    
private:
    Optional<T> mValue;
};


template<typename T>
struct Current
{
    void set(T inValue)
    {
        mValue = inValue;
    }
    
    T get_or(T t) const
    {
        return mValue ? *mValue : t;
    }
    
private:
    Optional<T> mValue;
};



struct RoundTripTime
{   
    void set(int64_t n)
    {
        mMaximum.set(n);
        mMinimum.set(n);
        mCurrent.set((9 * mCurrent.get_or(n) + n) / 10);
        
        std::cout << n << " => " << (*this) << std::endl;
    }
    
    int64_t minimum() const { return mMinimum.get_or(current()); }
    int64_t maximum() const { return mMaximum.get_or(current()); }
    int64_t current() const { return mCurrent.get_or(0); }
    
private:
    friend std::ostream& operator<<(std::ostream& os, const RoundTripTime& rtt)
    {
        return os << "current=" << rtt.current()
                  << " minimum=" << rtt.minimum()
                  << " maximum=" << rtt.maximum();
    }
    
    Maximum<int64_t> mMaximum;
    Minimum<int64_t> mMinimum;
    Current<int64_t> mCurrent;
};


int main()
{
    // normal values are in [40, 60] range
    RoundTripTime rtt;
    rtt.set(41);
    rtt.set(56);
    rtt.set(53);
    rtt.set(51);  
    rtt.set(10); // outlier
    rtt.set(46);
    rtt.set(52);
    rtt.set(59);
    rtt.set(49);
    rtt.set(90); // outlier
    rtt.set(55);
    rtt.set(53);
    rtt.set(45);
    rtt.set(49);
}