#include <iostream>


struct test
{
    test() = default;
    int x;
};



int main() {
    {
        test t;
        std::cout << t.x << std::endl;
    }
    {
        test t;
        std::cout << t.x << std::endl;
    }
    {
        test t;
        std::cout << t.x << std::endl;
    }
}
    