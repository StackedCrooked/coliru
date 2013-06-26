#include <iostream>

struct Integer
{
    Integer(int n = 0) : obj(n) {}
    
    operator int() const { return obj; }
    int obj;
};

int main()
{
    Integer a{3};
    Integer b{4};
    std::cout << a + b;
}
