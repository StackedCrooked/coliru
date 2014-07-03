#include <iostream>
#include <limits>




// Maximum for storing maximum
template<typename T>
struct Maximum
{
    Maximum(const T& tt = T()) : t(tt) {}
    operator T() const { return t; }
    void update(const T& tt) { if (tt > t) t = tt; }
    T t;
};


// Minimum for storing minimum
template<typename T>
struct Minimum
{
    Minimum(const T& tt = T()) : t(tt) {}
    operator T() const { return t; }
    void update(const T& tt) { if (tt < t) t = tt; }
    T t;
};


// Average for storing a (weighted) average
// alpha=0.1 (should be configurable)
template<typename T>
struct Average
{
    Average(const T& tt = T()) : t(tt) {}
    operator T() const { return T(0.5 + t); }
    void update(const T& tt) { t = (0.9 * t) + (0.1 * tt); } // weighted average
    double t;
};


int main()
{
    Maximum<int> max;
    Minimum<int> min;
    Average<int> avg;
    
    bool first_time = true;
    for (auto&& i : { 100, 40, 160, -90, 200, -10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 })
    {
        if (first_time)
        {
            // initialize the values
            max = decltype(max)(i);
            min = decltype(min)(i);
            avg = decltype(avg)(i);
            first_time = false;
            goto print;
        }
        
        // update the values        
        max.update(i);
        min.update(i);
        avg.update(i);
        
    print:
        std::cout << "min=" << min << " max=" << max << " avg=" << avg << '\n';
    }
}
