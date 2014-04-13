#include <iostream>

class B
{
  public:
    B()
    {
        std::cout << "B()" << std::endl;
        m = 17;
    }

    B(const B & o)
    {
        std::cout << "B(const B& o)" << std::endl;
        m = o.m;
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
