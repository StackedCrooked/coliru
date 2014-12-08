#include <iostream>
#include <iomanip>
#include <vector>

class C
{
public:
    int m() { return 1; }
    int m() const { return 2; }
    
    int test1()
    {
        return [this]() -> int {
            return m();
        }();
    }
    
    int test2() const
    {
        return [this]() -> int {
            return m();
        }();
    }
    
    int test3()
    {
        return [this]() mutable -> int {
            return m();
        }();
    }
    
    int test4() const
    {
        return [this]() mutable -> int {
            return m();
        }();
    }
};

int main()
{
    C c;
    std::cout << c.test1() << std::endl;
    std::cout << c.test2() << std::endl;
    std::cout << c.test3() << std::endl;
    std::cout << c.test4() << std::endl;
}
