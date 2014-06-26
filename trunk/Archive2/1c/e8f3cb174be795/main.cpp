#include <iostream>
#include <memory>

class Base
{
public:
    virtual void* allocate(){ return nullptr; }
};

template <class T> class BaseTemplate : public Base
{
public:
    void* allocate() override { return new T(); }
};

class IntSpecialization : public BaseTemplate<int>
{
};

std::unique_ptr<Base> GetSpecialization(const int&)
{ 
    return std::unique_ptr<IntSpecialization>(new IntSpecialization()); 
}

int main()
{
    auto sp = GetSpecialization(10);
    if(sp->allocate() == nullptr) {
        std::cout << "nullptr!\n";
    }
}
