#include <iostream>
#include <vector>
#include <algorithm>

class Base
{
public:
    virtual void Print() = 0;
};

struct DeriveredStruct : public Base
{
    void Print() override
    {
        std::cout << "Struct" << std::endl;
    }
};

class DeriveredClass : public Base
{
public:
    void Print() override
    {
        std::cout << "Class" << std::endl;
    }
};

int main(int argc, char* argv[])
{
    std::vector<Base*> stuff;
    stuff.push_back(new DeriveredStruct());
    stuff.push_back(new DeriveredClass());

    std::for_each(stuff.begin(), stuff.end(), [](Base* base)
    {
        base->Print();
    });
    return 0;
}