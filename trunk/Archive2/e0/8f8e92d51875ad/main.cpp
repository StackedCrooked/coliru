#include <cstdint>
#include <iostream>
#include <limits>


template<typename T, T InitialValue = std::numeric_limits<T>::max()>
struct Minimum
{   
    Minimum() : value_(InitialValue) { }
    
    void operator=(T value)
    {
        if (value < value_) value_ = value;
    }
    
    operator T() const { return value_; }
    
private:
    T value_;
};


template<typename T, T Initial = std::numeric_limits<T>::min()>
struct Maximum
{    
    Maximum() : value_(Initial) { }
    
    void operator=(T value)
    {
        if (value > value_) value_ = value;
    }
    
    operator T() const { return value_; }
    
private:
    T value_;
};


int main()
{
    Minimum<int, 0> min;
    Maximum<int, 0> max;
    
    srand(time(0));
    
    for (int i = 0; i != 10 ; ++i)
    {
        int r = 10 + rand() % 90;
        min = r;
        max = r;        
        std::cout << "rand=" << r << " min=" << min << " max=" << max << std::endl;
    }
}
