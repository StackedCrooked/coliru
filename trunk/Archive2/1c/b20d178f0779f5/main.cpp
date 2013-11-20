#include <iostream>

class B
{
public:
    virtual const char* get_name() const = 0;
};

class A : public B
{
public:
    virtual int get_value() const = 0;
};

class Impl : public A
{
public:
    const char* get_name() const
    {
        return "impl";
    }
    
    const int get_value() const
    {
        return 1;
    }
};

int main()
{
    Impl impl;
    std::cout << sizeof(impl) << std::endl;
    
    return 0;
}
