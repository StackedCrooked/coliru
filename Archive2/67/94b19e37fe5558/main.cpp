#include <iostream>

class Base
{
public:

    friend bool operator< (Base const& lhs, Base const& rhs)
    {
       return lhs.str < rhs.str;
    }
  
private:
  std::string str;
};

struct Derived : Base {};

int main()
{
    Derived a, b;
    std::cout << (a < b);
}