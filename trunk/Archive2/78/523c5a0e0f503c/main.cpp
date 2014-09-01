#include <cstdint>
#include <iostream>
#include <limits>


template<typename T>
struct Minimum
{   
    Minimum() : value_(std::numeric_limits<T>::max()) { }
    
    void operator=(const T& value)
    {
        if (is_uninitialized() || value < value_)
        {
            value_ = value;
        }
    }
    
    operator const T&() const
    {
        return value_;
    }
    
    
    bool is_uninitialized() const
    {
        return value_ == std::numeric_limits<T>::max();
    }
    
private:
    T value_;
};


template<typename T>
struct Maximum
{    
    Maximum() : value_(std::numeric_limits<T>::min()) { }
    
    void operator=(const T& value)
    {
        if (is_uninitialized() || value > value_)
        {
            value_ = value;
        }
    }
    
    operator const T&() const
    {
        return value_;
    }
    
    bool is_uninitialized() const
    {
        return value_ == std::numeric_limits<T>::min();
    }
    
private:
    T value_;
};


int main()
{
    Minimum<int> min;
    Maximum<int> max;
    
    
    for (int i = 0; i != 10 ; ++i)
    {
        int r = rand() % 100;
        min = r;
        max = r;
        
        std::cout << "rand=" << r << " min=" << min << " max=" << max << std::endl;
    }
}
