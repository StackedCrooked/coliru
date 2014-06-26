#include <iostream>
#include <memory>
#include <typeinfo>

class Base
{
public:
    virtual void* allocate(){ return nullptr; }
    ~Base() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

template <class T> class BaseTemplate : public Base
{
public:
    void* allocate() override { return new T(); }
};

class IntSpecialization : public BaseTemplate<int>
{
public:
    ~IntSpecialization() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

std::unique_ptr<Base> GetSpecialization(const int&)
{ 
    return std::unique_ptr<IntSpecialization>(new IntSpecialization());
}

int main()
{
    {
        auto sp = GetSpecialization(10);
    }
}
