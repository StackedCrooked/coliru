#include <iostream>

class B
{
  public:
    B()
    {
        std::cout << "B()" << std::endl;
    }
    ~B()
    {
        std::cout << "~B()" << std::endl;
    }
    B(const B & o)
    {
        std::cout << "B(const B& o)" << std::endl;
    }
    B & operator=(const B & o)
    {
        std::cout << "B & operator=(const B & o)" << std::endl;
        return *this;
    }
};

int main()
{
    B b = b;
}