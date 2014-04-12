#include <iostream>

class B
{
  public:
    B()
        : m(17)
    {
        std::cout << "B()" << std::endl;
    }

    B(const B & o)
        : m(o.m)
    {
        std::cout << "B(const B& o)" << std::endl;
    }
    B & operator=(const B & o)
    {
        std::cout << "B & operator=(const B & o)" << std::endl;
        m = o.m;
        return *this;
    }
    int m;
};

int main()
{
    B b  = b;
    std::cout << b.m << std::endl;
}
