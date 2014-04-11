#include <iostream>

class B
{
  public:
    int m;
  public:
    B()
    {
        m = 17;
        std::cout << "B()" << std::endl;
    }
    ~B()
    {
        std::cout << "~B()" << std::endl;
    }
    B(const B & o)
    {
        m = o.m;
        std::cout << "B(const B& o)" << std::endl;
    }
    B & operator=(const B & o)
    {
        m = o.m;
        std::cout << "B & operator=(const B & o)" << std::endl;
        return *this;
    }
};

int main()
{
    B b = b;
    std::cout << b.m << std::endl;
    
    B b1;
    b1 = b1;
    std::cout << b1.m << std::endl;
    
}
