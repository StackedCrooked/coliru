#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

class A {
    public:
    A()
    {
        std::cout << "A ctor" << std::endl;
    }
};

class B : virtual public A {
};

class C : public B{
    public:
    C() {}  // OK with virtual inheritance
};

int main()
{
    C c;
}
