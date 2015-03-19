#include <functional>

struct A
{
    int value = 42;

    //Error: a nonstatic reference must be relative to a specific object
    std::function<void()> l1 = [this]() { value++; };

    //Error: 'this' cannot be used in the body of this lamda
    std::function<void()> l2 = [this]() { this->value++; }; 

    A()
    {
        //No problem here
        std::function<void()> l3 = [this]() { value++; };
    }
};

int main()
{
    
}