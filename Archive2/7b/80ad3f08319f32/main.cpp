#include <iostream>

template<class T> class A
{
public: 
    virtual T doStuff() = 0;
    virtual void doOther(T a) = 0;
protected:
    A() {}
};

class B : public A<int>
{
public:
    B() {}
    virtual int doStuff() { return 0; }
    virtual void doOther(int a) {}

};

int main() {
    std::cout << "Works\n";
}