#include <cstdint>
#include <iostream>
#include <limits>


template<typename T>
struct Minimum
{   
    Minimum() : value_(std::numeric_limits<T>::max()) { }
    
    void operator=(const T& value)
    {
        if (value_ == std::numeric_limits<T>::max() || value < value_)
        {
            value_ = value;
        }
    }
    
    operator const T&() const { return value_; }
    
private:
    T value_;
};


template<typename T>
struct Maximum
{    
    Maximum() : value_(std::numeric_limits<T>::min()) { }
    
    void operator=(const T& value)
    {
        if (value_ == std::numeric_limits<T>::min() || value > value_)
        {
            value_ = value;
        }
    }
    
    operator const T&() const { return value_; }
    
private:
    T value_;
};


int main()
{
    Minimum<int> min;
    Maximum<int> max;
    
    srand(time(0));
    
    for (int i = 0; i != 10 ; ++i)
    {
        int r = 10 + rand() % 90;
        min = r;
        max = r;        
        std::cout << "rand=" << r << " min=" << min << " max=" << max << std::endl;
    }
}
