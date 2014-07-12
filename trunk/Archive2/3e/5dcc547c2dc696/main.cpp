#include <iostream>
#include <memory>

template<int n>
struct Vec
{
};

template<int n>
struct Module
{
    virtual double value(const Vec<n>& point) const = 0;
    
    virtual void setScale(double)
    {
    }
    
    virtual double getScale() const
    {
        return 0;
    }
};

template<int n>
struct TestModule
{
    TestModule() : scale(1) {}

    double value(const Vec<n>&) const
    {
        return scale / double(n);
    }
    
    virtual void setScale(double s)
    {
        scale = s;
    }
    
    virtual double getScale() const
    {
        return scale;
    }
    
    double scale;
};

int main()
{
    TestModule<1> t1;
    TestModule<2> t2;
    TestModule<3> t3;
    
    std::cout << "t1: " << t1.value() << "\n";
    std::cout << "t2: " << t2.value() << "\n";
    std::cout << "t3: " << t3.value() << "\n";
}

