#include <iostream>

template <typename T> class MyBaseClass
{
public:
    virtual ~MyBaseClass() = default;

    void DoSomething(const T& myClass) 
    { std::cout << "DoSomething(T)\n"; }  

    virtual void DoSomething(int n, const T& myClass) 
    { std::cout << "virtual DoSomething(int, T)\n"; }
};

class MyDerivedClass : public MyBaseClass<int>
{
public:
    virtual void DoSomething(int n, const int& myInt)
    { std::cout << "virtual DoSomething(int, int)\n"; }
};

int main() 
{
    MyDerivedClass<int>* d = new MyDerivedClass;
    d->DoSomething(0); // "virtual DoSomething(int, int)";
}
